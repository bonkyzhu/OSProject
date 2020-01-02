#include <iostream>
#include <vector>
#include <map>
#include "inode.h"
#include "disk.h"

using namespace std;

class diskmanager {
  public:
    void initiate();
    int CreateFile(string filename, string data); // 写入数据区，满了的话就返回0，成功写入返回1
    string ReadFile(string filename); // 不确定需要 message 吗
    int DeleteFile(string filename); // 删除数据，
//    int swap(int thread_id, int datasize, string message, string name);
//    int DelSwap(int thread_id);
  private:
    disk thedisk; // 代表disk
    map<string, inode> inodes; // string = 文件夹+文件名
};
void diskmanager::initiate() {
  this->thedisk.initiate();
}

int diskmanager::CreateFile(string filename, string data) {
  // 创建一个文件, data是文件的数据，filename 是文件的绝对路径
  inode File;
  // 如果磁盘空间足够
  if (File.initiate_inode(data, data.size(), this->thedisk) == 1){
    this->inodes.insert(pair<string, inode>(filename, File));
    return 1; // 说明创建完成
  }
  return 0;
}

string diskmanager::ReadFile(string filename) {
  inode File;
  string data = "";
  File = this->inodes[filename];
  vector<int> all_block_index = File.get_index(); //获取文件所有区块的地址
  for (int i = 0; i < all_block_index.size(); ++i) {
    data += this->thedisk.read(all_block_index[i]);
  }
  return data;
}
int diskmanager::DeleteFile(string filename) {
  if (this->inodes.find(filename) == inodes.end()){
    return 0;   // 如果不存在这个文件返回0
  }
  inode File;
  string data = "";
  File = this->inodes[filename];
  vector<int> all_block_index = File.get_index(); //获取文件所有区块的地址
  for (int i = 0; i < all_block_index.size(); ++i) {
    data += this->thedisk.delete_block(all_block_index[i]); //删除对应区块
  }
  this->inodes.erase(filename); //删除对应 inode
  return 1;
}



