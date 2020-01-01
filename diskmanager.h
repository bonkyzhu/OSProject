/*
 * z作用
 */
#include <iostream>
#include <vector>
#include "inode.h"
#include "disk.h"
using namespace std;

class diskmanager {
  public:
    int WriteData(string data); // 写入数据区，满了的话就返回0，成功写入返回1
    string Read(int tread_id); // 不确定需要 message 吗
    int DeleteData(int tread_id); // 删除数据，
    int swap(int thread_id, int datasize, string message, string name);
    int DelSwap(int thread_id);
  private:
    disk thedisk; // 代表disk
    vector<inode> inodes; // tread_id 就是序号
};


