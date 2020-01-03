#ifndef _M_H_
#define _M_H_
#include <iostream>
#include <queue>

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
    int datasize;//数据大小，多少字节
    string message;//数据信息
    string name;//文件名
    int sign;//标志位
    int thread_id;//所属线程id
    void set() {
      datasize=0;
      message="NULL";
      name="NULL";
      sign=0;
      thread_id=0;
    }
};

class Memory { //内存
	public:
		Data Mem [16];

		Memory() {
			pos=0;
			free=16;
			u=0;
		}
		int pos;
		
		int Ex_i[500]; //用于存地址 
		int u;
		int free;//空闲块数
		queue<int> q;//符合FIFO算法的调出队列
		int Alloc(int thread_id,string name) { //申请内存块，从空闲块中找或者对换
			//Mb_num 申请的内存块数    thread_id  线程id
			string str;
			int Mb_num;//申请的内存块数
			str=A_Disk.ReadFile(name);
			if(str.length()>64) {
				cout<<"文件过大，内存不足";
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
				} else { //需要置换
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
						int z=q.front();//要置换出去的块号
						Ex_i[u]=A_Disk.swap(Mem[z].message);//换到置换区
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

		int Delete(int thread_id) { //释放内存
			//  (int thread_id)
			//thread_id  线程id   将所有与threadid一样的块删了回收，通知磁盘删了对换区
			int F=q.front();
			int G=free;
			for(int i=0; i<16-G; i++) { //删除回收，修改free、队列q
				int a=q.front();
				q.pop();
				if(Mem[a].thread_id==thread_id) {
					Mem[a].set();
					free++;
				} else q.push(a);
			}

			for(int i=1; i<u; i+=2) { //调用磁盘管理的函数删除兑换区对应的文件
				if(Ex_i[i]==thread_id) {
					A_Disk.DelSwap(Ex_i[i-1]);
					Ex_i[i]=0;
					Ex_i[i-1]=0;
				}
			}

			return 1;
		}
		int InMem(string name) { //判断文件是否在内存
			for(int i=0; i<16; i++) {
				if(Mem[i].name==name)
					return 1;
			}
			return 0;
		}
		void show() { //显示内存数据
			for(int i=0; i<16; i++) {
				cout<<i<<" "<<Mem[i].sign<<" "<<Mem[i].thread_id<<" "<<Mem[i].name<<" "<<Mem[i].datasize<<" "<<Mem[i].message<<endl;
			}
		}

};
Memory Mems;

#endif
