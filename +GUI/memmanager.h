#ifndef _M_H_
#define _M_H_
#include <iostream>
#include <queue>
#include "diskmanager.h"

using namespace std;

class Data {
public:
    Data() {
      datasize=0;
      message="NULL";
      name="NULL";
      sign=0;
      thread_id=0;
    }
    int datasize;//���ݴ�С�������ֽ�
    string message;//������Ϣ
    string name;//�ļ���
    int sign;//��־λ
    int thread_id;//�����߳�id
    void set() {
      datasize=0;
      message="NULL";
      name="NULL";
      sign=0;
      thread_id=0;
    }
};

class Memory { //�ڴ�
public:
    Data Mem [16];

    Memory() {
      pos=0;
      free=16;
      u=0;
    }
    int pos;

    int Ex_i[500]; //���ڴ��ַ
    int u;
    int free;//���п���
    queue<int> q;//����FIFO�㷨�ĵ�������
    int Alloc(int thread_id,string name) { //�����ڴ�飬�ӿ��п����һ��߶Ի�
      //Mb_num ������ڴ����    thread_id  �߳�id
      string str;
      int Mb_num;//������ڴ����
      str=A_Disk.ReadFile(name);
      if(str.length()>64) {
        cout<<"�ļ������ڴ治��";
        return 0;
      } else {
        if(str.length()%4==0) {
          Mb_num=str.length()/4;
        } else Mb_num=str.length()/4+1;
        if(Mb_num<=free) {
          for(int i=0; i<Mb_num; i++) {
            for(int j=0; j<16; j++) {
              if(Mem[j].sign==0) {
                Mem[j].thread_id=thread_id;
                Mem[j].name=name;
                Mem[j].sign=1;
                if(i!=Mb_num-1) {
                  Mem[j].datasize=4;
                  Mem[j].message=str.substr(pos,4);
                  pos+=4;
                } else {
                  Mem[j].datasize=str.length()-(Mb_num-1)*4;
                  Mem[j].message=str.substr(pos);
                  pos=0;
                }
                q.push(j);
                break;
              }
            }
          }
          free=free-Mb_num;
        } else { //��Ҫ�û�
          for(int i=0; i<free; i++) {
            for(int j=0; j<16; j++) {
              if(Mem[j].sign==0) {
                Mem[j].thread_id=thread_id;
                Mem[j].name=name;
                Mem[j].sign=1;
                Mem[j].datasize=4;
                Mem[j].message=str.substr(pos,4);
                pos+=4;
                q.push(j);
                break;
              }
            }
          }
          for(int j=0; j<Mb_num-free; j++) {
            int z=q.front();//Ҫ�û���ȥ�Ŀ��
            Ex_i[u]=A_Disk.swap(Mem[z].message);//�����û���
            Ex_i[u+1]=Mem[z].thread_id;
            u+=2;
            q.pop();
            Mem[z].set();
            Mem[z].thread_id=thread_id;
            Mem[z].name=name;
            Mem[z].sign=1;
            if(j!=Mb_num-free-1) {
              Mem[z].datasize=4;
              Mem[z].message=str.substr(pos,4);
              pos+=4;
            } else {
              Mem[z].datasize=str.length()-(Mb_num-1)*4;
              Mem[z].message=str.substr(pos);
              pos=0;
            }
            q.push(z);
          }
          free=0;
        }

        return 1;
      }

    }

    int Delete(int thread_id) { //�ͷ��ڴ�
      //  (int thread_id)
      //thread_id  �߳�id   ��������threadidһ���Ŀ�ɾ�˻��գ�֪ͨ����ɾ�˶Ի���
      int F=q.front();
      int G=free;
      for(int i=0; i<16-G; i++) { //ɾ�����գ��޸�free������q
        int a=q.front();
        q.pop();
        if(Mem[a].thread_id==thread_id) {
          Mem[a].set();
          free++;
        } else q.push(a);
      }

      for(int i=1; i<u; i+=2) { //���ô��̹���ĺ���ɾ���һ�����Ӧ���ļ�
        if(Ex_i[i]==thread_id) {
          A_Disk.DelSwap(Ex_i[i-1]);
          Ex_i[i]=0;
          Ex_i[i-1]=0;
        }
      }

      return 1;
    }
    int InMem(string name) { //�ж��ļ��Ƿ����ڴ�
      for(int i=0; i<16; i++) {
        if(Mem[i].name==name)
          return 1;
      }
      return 0;
    }
    void show() { //��ʾ�ڴ�����
      for(int i=0; i<16; i++) {
        cout<<i<<" "<<Mem[i].sign<<" "<<Mem[i].thread_id<<" "<<Mem[i].name<<" "<<Mem[i].datasize<<" "<<Mem[i].message<<endl;
      }
    }

};
Memory Mems;

#endif
