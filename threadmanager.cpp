#include <iostream>
#include <thread>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <vector>

#include"disk.h"
#include"dirmanager.h"
#include"memmanager.h"

using namespace std; 
class Thread{
    public:
    int thread_id;
    string randst(int n);   //生成长度为n的随机字符串
    void Generate();  //数据生成线程
    void Delete();    //删除数据线程
    void Excute();    //执行线程
}
string Thread::randst(int n)
{
    srand((unsigned)time(NULL));
    string s;
    for(int i=0;i<n;i++)
    {
        s+=rand()%26+'a';
    }
    cout<<s<<endl;
    return ;
}
void Thread::Generate(mutex* pmt)  //数据生成线程
{
    (*pmt).lock();
    cout<<"请输入数据大小（按字节计算）、文件名，中间以空格分开，回车以结束"<<endl;
    Data temp;
    string dir;
    string storage_dir;
    cin>>temp.datasize;
    cin>>temp.message;
    cin>>dir;
    cin>>temp.name;
    /*
    * 申请所需大小的外存块，如果盘块不够给出提示（待完成？）
    */
    disk::write(/*不知要写如磁盘块号*/);
    /* 
    * 按照要求的数据组织方式，将数据存入磁盘块（按块分配磁盘）（待完成）
    */
    DirMan::CreatDir("admin",temp.name,/*不知地址是什么,不知结构是什么*/);
    /*更改空闲盘块信息（待完成）*/
    (*pmt).unlock();
    return;
}
void Thread::Delete(mutex* pmt)    //删除数据线程
{
    (*pmt).lock();
    string temp;
    cout<<"请输入删除文件名字，回车以结束"<<endl;
    cin>>temp;
    Dirman::DelFile(temp);
    /*
    * 回收外存空间，更新空闲盘块信息(待完成)
    * 若在dirmanager中实现的话此函数完成
    */
    (*pmt).unlock();
    return;
}
void Thread::Excute(int Thread_id,mutex* pmt)    //执行线程
{
    (*pmt).lock();
    /*
    * 外存调入内存(待完成)
    * (1)内存管理->空闲空间管理，申请4块空闲内存
    */
    vector<int> loc;
    loc=Memory::Alloc(4,thread_id);
    for(vector<int>::iterator it=loc.begin();it!=loc.end();it++)
        Memory::Write(Thread_id,*it,4,);
    if(/*内存不足*/)
    {
        cout<<"内存不足"<<endl;
        return ;
    }
    /*
    * 根据目录中文件存储信息将文件数据从外存读入内存 (待完成)
    * 如果4块内存不够存放文件信息，需要进行换页（选择的换页策略见分组要求），换出的页面存放到磁盘兑换区 (待完成)
    */
    (*pmt).unlock();
    return ;
}
