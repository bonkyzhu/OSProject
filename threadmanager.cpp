#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <vector>

#include"diskmanager.h"
#include"dirmanager.h"
#include"memmanager.h"

using namespace std; 
class ThreadMan{
    public:
    int thread_id;
    string randst(int n);   //生成长度为n的随机字符串
    void Generate(int Thread_id);  //数据生成线程
    void Delete(int Thread_id);    //删除数据线程
    void Execute(int Thread_id);    //执行线程
    string name;
};
string ThreadMan::randst(int n)
{
    srand((unsigned)time(NULL));
    string s;
    for(int i=0;i<n;i++)
    {
        s+=(rand()%26+'a');
    }
    return s;
}
void ThreadMan::Generate(int Thread_id)  //数据生成函数
{
    //(*pmt).lock();
    cout<<"请输入数据大小（按字节计算）、文件名，中间以空格分开，回车以结束"<<endl;
    int data_length;
    string file_name;
    cin>>data_length;
    cin>>file_name;
    string content;
    content=randst(data_length);
    //cout<<content<<endl;
    A_Disk.CreateFile(file_name,content);
    Dirs.CreatDir("admin",file_name,"");
    cout<<"当前目录内容"<<endl;
    Dirs.ShowDirMan();
    //(*pmt).unlock();
    return;
}
void ThreadMan::Delete(int Thread_id)    //删除数据线程
{
    //(*pmt).lock();
    string temp;
    cout<<"当前目录内容"<<endl;
    Dirs.ShowDirMan();
    cout<<"请输入删除文件名字，回车以结束"<<endl;
    cin>>temp;
    if(Dirs.check(temp))
        Dirs.DelFile(temp);
    else 
        cout<<"错误，无此文件！"<<endl;
    cout<<"当前目录内容"<<endl;
    Dirs.ShowDirMan();
    //(*pmt).unlock();
    return;
}
void ThreadMan::Execute(int Thread_id)    //执行线程
{
    string file_name;
    cout<<"当前目录内容"<<endl;
    Dirs.ShowDirMan();
    cout<<"请输入要执行的文件名"<<endl;
    cin>>file_name;
    Mems.Alloc(thread_id,file_name);
    Mems.show();
    return ;
}
int main()
{
    int op;
    int id=0;
    ThreadMan TA;
    //mutex mt;
    do{
        cout<<"1.数据生成线程 2.删除数据线程 3.执行线程 0.退出"<<endl;
        cout<<"请输入要执行的线程"<<endl;
        cin>>op;
        switch(op){
            case 1:
            {
                thread gen(&ThreadMan::Generate,&TA,++id);
                gen.join();
                break;
            }
            case 2:
            {
                thread del(&ThreadMan::Delete,&TA,++id);
                del.join();
                break;
            }
            case 3:
            {
                thread exe(&ThreadMan::Execute,&TA,++id);
                exe.join();
                break;
            }
            default:
            cout<<"不存在该指令"<<endl;
            break;
        }
    }
    while(op!=0);
    return 0;
}