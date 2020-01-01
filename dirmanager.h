#include <string>
#include<string.h>
#include<ctime>
#include<iostream>
#include<map>
#include "memmanager.h"
using namespace std;

//目录 
class Dir{
	public:
		Dir(){
			FileName="NULL";
			FileOwner="NULL";
			Date=NULL;
			FileStructure="NULL";
			adr=0; 
		}
	 string FileName; //文件名
	 string FileOwner ;//文件所有者
	 char *Date;//创建时间 
	 string  FileStructure;//文件结构 
	 int adr;//再磁盘中存放的地址信息 
	 void setFileName(string a);
	 void setFileOwner(string b);
	 void setDate(char *c);
	 void setFileStructure(string x);
	 void setadr(int y);
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
	void Dir::setadr(int y){
	 	adr=y;
	 }
	void Dir::show(){
	 	cout<<FileName<<endl;
	 }
	 
	 
class DirMan{
	public:
	map<string,Dir> DirMap;
	void CreatNullDir(string x);//创建空目录项 
	void DelNullDir();//删除空目录项 
	void DelFile(string x);//删除文件 
	void CreatDir(string owner,string filename,int address,string structer);//为文件创建目录项 
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
		//空目录的地址
		dir.Dir::setadr(0); 
		//文件结构
		dir.Dir::setFileStructure("NULL"); 
		DirMap.insert(map<string, Dir>::value_type(dir.FileName, dir));
	}

	void DirMan::DelNullDir(){
		DirMap.erase("NULL");
	}
	void DirMan::DelFile(string x){
		int t=Memory::InMem(x);//内存管理中的函数，根据文件名判断是否在内存中 
		if(!t){
			DirMap.erase(x); //删除目录 
			//此处需要删除文件在磁盘中对应的数据； 
		}
	}
	void DirMan::CreatDir(string owner,string filename,int address,string structer){
		Dir dir;
		//时间 
		time_t now=time(0);
		char*dt=ctime(&now);
		dir.Dir::setDate(dt);
		//拥有者 
		dir.Dir::setFileOwner(owner);
		//文件名 
		dir.Dir::setFileName(filename);
		//地址
		dir.Dir::setadr(address);
		//文件结构
		dir.Dir::setFileStructure(structer);
		//加入目录
		DirMap.insert(map<string, Dir>::value_type(dir.FileName, dir));
		cout<<dir.FileName<<"已创建成功"<<endl; 
	}
	void DirMan::ShowDirMan(){
		map<string,Dir>::iterator it;
		for(it=DirMap.begin();it!=DirMap.end();it++){
			pair<string,Dir> item=*it;
			cout<<item.second.FileName<<endl;
		}
	} 



