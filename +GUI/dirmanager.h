#include <string>
#include<string.h>
#include<ctime>
#include<iostream>
#include<map>
#include<sstream>
#include "diskmanager.h"
#include "memmanager.h"
//#include "memmanager.h"
using namespace std;


class Dir{
public:
    Dir(){
      FileName="NULL";
      FileOwner="NULL";
      Date="NULL";
      FileStructure="NULL";
    }
    string FileName; //�ļ���
    string FileOwner ;//�ļ�������
    string Date;//����ʱ��
    string  FileStructure;//�ļ��ṹ
    void setFileName(string a);
    void setFileOwner(string b);
    void setDate(string c);
    void setFileStructure(string x);
    void show();
};
void Dir::setFileName(string a){
  FileName=a;
}
void Dir::setFileOwner(string b){
  FileOwner=b;
}
void Dir::setDate(string c){
  Date=c;
}
void Dir::setFileStructure(string x){
  FileStructure=x;
}
void Dir::show(){
  cout<<FileName<<endl;
}


class DirMan{
public:
    map<string,Dir> DirMap;
    void CreatNullDir(string x);//������Ŀ¼��
    void DelNullDir();//ɾ����Ŀ¼��
    string TimeGen();
    bool check(string x);
    void DelFile(string x);//ɾ���ļ�
    void CreatDir(string owner,string filename,string structer);//Ϊ�ļ�����Ŀ¼��
    void ShowDirMan();//������ʾ��ǰ������Ŀ¼��
};
string DirMan::TimeGen()
{
  time_t timer;
  time(&timer);
  tm *t_tm = localtime(&timer);

  int year = t_tm->tm_year + 1900;//��
  int month = t_tm->tm_mon + 1;//��
  int day = t_tm->tm_mday;//��
  int hour = t_tm->tm_hour;//ʱ
  int minute = t_tm->tm_min;//��
  int second = t_tm->tm_sec;//��

  stringstream y;
  y<<year;
  stringstream m;
  m<<month;
  stringstream d;
  d<<day;
  stringstream h;
  h<<hour;
  stringstream mi;
  mi<<minute;
  stringstream s;
  s<<second;
  string s1=y.str();
  string s2=m.str();
  string s3=d.str();
  string s4=h.str();
  string s5=mi.str();
  string s6=s.str();
  string s7=s1+" "+s2+"/"+s3+" "+s4+":"+s5+":"+s6;
  return s7;
}
void DirMan::CreatNullDir(string x){ //x�� �ļ�ӵ���ߣ�
  //��Ŀ¼��ʱ��
  Dir dir;
  dir.Dir::setDate(TimeGen());
  dir.Dir::setFileOwner(x);
  //��Ŀ¼���ļ���
  dir.Dir::setFileName("NULLFILE");
  //�ļ��ṹ
  dir.Dir::setFileStructure("NULL");
  DirMap.insert(map<string, Dir>::value_type(dir.FileName, dir));
}

void DirMan::DelNullDir(){
  DirMap.erase("NULL");
}

bool DirMan::check(string x){
  map<string,Dir>::iterator iter=DirMap.find(x);
  if(iter!=DirMap.end()){
    return 1;
  }
  else return 0;
}
void DirMan::DelFile(string x){
  int t= Mems.InMem(x);
  if(!t){
    DirMap.erase(x); //ɾ��Ŀ¼
    A_Disk.DeleteFile(x); //�˴���Ҫɾ���ļ��ڴ����ж�Ӧ�����ݣ�
  }
  else
  {
    cout<<"\n ���ļ����ڴ��У�����ɾ����\n"<<endl;
  }

}
void DirMan::CreatDir(string owner,string filename,string structer){
  Dir dir;
  //ʱ�� kk4
  dir.Dir::setDate(TimeGen());
  //ӵ����
  dir.Dir::setFileOwner(owner);
  //�ļ���
  dir.Dir::setFileName(filename);
  //�ļ��ṹ
  dir.Dir::setFileStructure(structer);
  //����Ŀ¼
  DirMap.insert(map<string, Dir>::value_type(dir.FileName, dir));
  cout<<dir.FileName<<" is Created"<<endl;
}
void DirMan::ShowDirMan(){
  map<string,Dir>::iterator it;
  for(it=DirMap.begin();it!=DirMap.end();it++){
    pair<string,Dir> item=*it;
    cout<<item.second.FileName << "\t-" <<item.second.Date << endl;
  }
}

DirMan Dirs;
