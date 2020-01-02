#include <string>
#include<string.h>
#include<ctime>
#include<iostream>
#include<map>
#include "diskmanager.h"
#include "memmanager.h"
//#include "memmanager.h"
using namespace std;


class Dir{
public:
    Dir(){
      FileName="NULL";
      FileOwner="NULL";
      Date=NULL;
      FileStructure="NULL";
    }
    string FileName; //文件名
    string FileOwner ;//文件所有者
    char *Date;//创建时间
    string  FileStructure;//文件结构
    void setFileName(string a);
    void setFileOwner(string b);
    void setDate(char *c);
    void setFileStructure(string x);
    void show();
};
void Dir::setFileName(string a){
  FileName=a;
}
void Dir::setFileOwner(string b){
  FileOwner=b;
}
void Dir::setDate(char *c){
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
    void CreatNullDir(string x);//创建空目录项
    void DelNullDir();//删除空目录项
    bool check(string x);
    void DelFile(string x);//删除文件
    void CreatDir(string owner,string filename,string structer);//为文件创建目录项
    void ShowDirMan();//遍历显示当前的所有目录项
};
void DirMan::CreatNullDir(string x){ //x是 文件拥有者；
  //空目录项时间
  Dir dir;
  time_t now=time(0);
  char*dt=ctime(&now);
  dir.Dir::setDate(dt);
  dir.Dir::setFileOwner(x);
  //空目录的文件名
  dir.Dir::setFileName("NULLFILE");
  //文件结构
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
    DirMap.erase(x); //删除目录
    A_Disk.DeleteFile(x); //此处需要删除文件在磁盘中对应的数据；
  }
}
void DirMan::CreatDir(string owner,string filename,string structer){
  Dir dir;
  //时间 kk4
  time_t now=time(0);
  char*dt=ctime(&now);
  dir.Dir::setDate(dt);
  //拥有者
  dir.Dir::setFileOwner(owner);
  //文件名
  dir.Dir::setFileName(filename);
  //文件结构
  dir.Dir::setFileStructure(structer);
  //加入目录
  DirMap.insert(map<string, Dir>::value_type(dir.FileName, dir));
  cout<<dir.FileName<<" is Created."<<endl;
}
void DirMan::ShowDirMan(){
  map<string,Dir>::iterator it;
  for(it=DirMap.begin();it!=DirMap.end();it++){
    pair<string,Dir> item=*it;
    cout<<item.second.FileName << "\t-" <<item.second.Date << endl;
  }
}

DirMan Dirs;