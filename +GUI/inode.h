#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "disk.h"
#include "define.h"
#include "index_table.h"
using namespace std;

// inode 类
class inode{
  public:
    int datasize;
    int block;
    int initiate_inode(string data, int datasize, disk& thedisk);
    vector<int> get_index();
    void to_index_table(vector<int> addresses, int blocknum);
    int direct[DIRECT_NUM] = {-1};
    index_table_one table_one;
    index_table_two table_two;
    index_table_three table_three;
};
int inode::initiate_inode(string data, int datasize, disk &thedisk) {
  //如果磁盘空间不够的话返回 0
  int block_num = ceil(datasize / BLOCK_SIZE);
  vector<int> addresses = thedisk.write(data, block_num);
  if (addresses.empty()){
      cout << "ERROR with disk." << endl;
      return 0;
  }
  this->datasize = datasize;
  this->to_index_table(addresses, block_num);
  return 1;
}
vector<int> inode::get_index() { // 得到所有的 index
  int blocknum = ceil(this->datasize / BLOCK_SIZE);
  vector<int> tmp; // 记录所有的 index

  int length = blocknum;

  for (int i = 0; i < min(length, 10); i++) {
    tmp.push_back(direct[i]); //如果小于10的话就直接用直接表
  }
  if (length > 10) {
    // 10~22 都是一级索引
    vector<int> table_one_index;
    table_one_index = this->table_one.get_all_block_index();
    for (int i = 0; i < table_one_index.size(); ++i) {
      tmp.push_back((table_one_index[i]));
    }
  }
  if (length > 23) {
    // 23~191 都是二级索引
    vector<int> table_two_index;
    table_two_index = this->table_two.get_all_block_index();
    for (int i = 0; i < table_two_index.size(); ++i) {
      tmp.push_back((table_two_index[i]));
    }
  }
  if (length > 192) {
    // 192~ 都是一级索引
    vector<int> table_three_index;
    table_three_index = this->table_three.get_all_block_index();
    for (int i = 0; i < table_three_index.size(); ++i) {
      tmp.push_back((table_three_index[i]));
    }
  }
  return tmp;
}
//把他放到 index——table 里面
void inode::to_index_table(vector<int> addresses, int blocknum){
  int length = blocknum;
  for (int i = 0; i < min(length, 10); i++) {
      this->direct[i] = addresses[i];
  }
  if (length > 10){
    for (int i = 10; i < min(23, length); i++) {
      this->table_one.write(addresses[i]);
    }
  }
  if (length > 23){
    for (int i = 23; i < min(192, length); i++) {
      this->table_two.write(addresses[i]);
    }
  }
  if (length > 192){
    for (int i = 192; i < min(BLOCKNUM, length); i++) {
      this->table_three.write(addresses[i]);
    }
  }
}
