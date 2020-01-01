#include<iostream>
#include<thread>
#include<string>
#include <thread>
#include <chrono>

#include"disk.h"
#include"dirmanager.h"
#include"memmanager.h"

using namespace std;
class Thread{
    public:
    void Generate();  //数据生成线程
    void Delete();    //删除数据线程
    void Excute();    //执行线程
    void Mutex();     //线程互斥
}
void Thread::Generate()  //数据生成线程
{
    cout<<"请输入数据大小（按字节计算）、数据信息（英文字母）、存储目录、文件名，中间以空格分开，回车以结束"<<endl;
    Data temp;
    string dir;
    string storage_dir;
    cin>>temp.datasize;
    cin>>temp.message;
    cin>>dir;
    cin>>temp.name;
    if(temp.datasize>4*Memory::free)
    {
        cout<<"盘块不够"<<endl;
        return;
    }
    /*
    * 按照要求的数据组织方式，将数据存入磁盘块（按块分配磁盘）（待完成）
    */
    CreatDir("admin",temp.name,/*/???*/);
    return;
}
void Thread::Delete()    //删除数据线程
{
    Data temp;
    cout<<"请输入删除文件名字，回车以结束"<<endl;
    cin>>temp.name;
    Dirman::DelFile(temp.name);
    /*
    * 回收外存空间，更新空闲盘块信息(待完成)
    */
    return;
}
void Thread::Excute()    //执行线程
{
    /*
    * 外存调入内存(待完成)
    * (1)内存管理->空闲空间管理，申请4块空闲内存
    */
    if(/*内存不足*/)
    {
        cout<<"内存不足"<<endl;
        /*
        * 根据目录中文件存储信息将文件数据从外存读入内存
        * 如果4块内存不够存放文件信息，需要进行换页（选择的换页策略见分组要求），换出的页面存放到磁盘兑换区
        */
    }
    return ;
}
void Thread::Mutex()     //线程互斥
{
    return ;
}
