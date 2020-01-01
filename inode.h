#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sys/malloc.h>
#include "disk.h"
#include "define.h"
#include "index_table.h"
using namespace std;

// inode 类
class inode{
  public:
    int datasize;
    int block;
    void initiate_inode(int datasize, disk& thedisk);
    void get_index(int datasize, disk thedisk);
    void to_index_table(vector<int> addresses, int blocknum);
    int direct[DIRECT_NUM] = {-1};
    index_table_one table_one;
    index_table_two table_two;
    index_table_three table_three;
};
void inode::initiate_inode(int datasize, disk &thedisk) {
  int block_num = ceil(datasize / BLOCK_SIZE);
  this->datasize = datasize;
  vector<int> addresses = thedisk.write(block_num);
  if (addresses.empty()){
      cout << "ERROR with disk." << endl;
      return;
  }
  this->to_index_table(addresses, block_num);
}
void inode::get_index(int datasize, disk thedisk){ //文件大小为byte
  int block_num = ceil(datasize / BLOCK_SIZE);
  this->datasize = datasize;
}
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
