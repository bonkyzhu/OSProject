#ifndef _A_H_
#define _A_H_
#include<iostream>
#include<vector>
#include<cstring>
#include "define.h"
using namespace std;

class disk{
  //混合索引, 0-9是直接索引, 10是一级索引, 11是二级索引，12是三级索引
  public:
    vector<int> write(int datablocknum);
    int read(int blockindex);
    bool enough_block(int datablocknum);
    bool delete_block(int blockindex);
    void initiate();
  private:
    int sparedatadisk[DATA_BLOCK_NUM]; // 用位示图表示空余磁盘块
    int spareswapdisk[SWAP_BLOCK_NUM]; // 用位示图表示空余磁盘块
    int sparedatablock;
    int spareswapblock;
};
// 初始话 disk
void disk::initiate(){
  memset(this->sparedatadisk, 0, sizeof(this->sparedatadisk));
  memset(this->spareswapdisk, 0, sizeof(this->spareswapdisk));
  sparedatablock = DATA_BLOCK_NUM;
  spareswapblock = SWAP_BLOCK_NUM;
}
// 检查是否有足够的空间
bool disk::enough_block(int datablocknum){
  if (datablocknum <= sparedatablock) {
    return true;
  }
  return false;
}
// TODO:写入数据
vector<int> disk::write(int datablocknum){
  // cout << "写之前" << this->spareblock << endl;
  // 如果空间不够返回 ERROR
  cout << this->sparedatablock << endl;
  cout << datablocknum << endl;
  vector<int> tmp;
  if (this->enough_block(datablocknum) == false) {
    return tmp;
  }

  for (int i=0; i < BLOCKNUM ; i++){
    if (this->sparedatadisk[i] == 0) {
      this->sparedatadisk[i] = 1;
      tmp.push_back(i);
      //TODO: 写入数据代码
      this->sparedatablock = this->sparedatablock - 1;
      datablocknum --;
    }
    if (datablocknum == 0)  break; 
  }

  //返回分配的 block 的序号列表
  return tmp;
}

bool disk::delete_block(int blockindex){
  if (sparedatadisk[blockindex] == 1){
    this->sparedatadisk[blockindex] = 0;
    this->sparedatablock ++;
    return true;
  }
  // 如果删除了本来就为空的块，返回 false
  return false;
}

#endif
