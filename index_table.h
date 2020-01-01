#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "define.h"
using namespace std;

// direct_index_table 类
class direct_index_table{
  public:
    vector<int> get_elem(); //返回所有的 block 索引
    bool write(int blocknum);
  private:
    int length=0;
    int blockindex[INDEX_TABLE_SIZE] = {-1};
};
vector<int> direct_index_table::get_elem(){
  vector<int> tmp;
  for (int i = 0; i < INDEX_TABLE_SIZE; i++) {
    if (this->blockindex[i] != -1){
      tmp.push_back(this->blockindex[i]);
    }
  }
  return tmp;
}
bool direct_index_table::write(int blocknum){
  if (length < INDEX_TABLE_SIZE){
    this->blockindex[this->length] = blocknum;
    this->length ++;
    return true;
  }
  return false;
}

// index_table_one 类
class index_table_one{
  public:
    vector<int> get_all_block_index();
    bool write(int blocknum);
  private:
    direct_index_table index_table_first[INDEX_TABLE_SIZE];
};
vector<int> index_table_one::get_all_block_index(){
  vector<int> tmp;
  for (int i = 0; i < INDEX_TABLE_SIZE; i++) {
    vector<int> elems = this->index_table_first[i].get_elem();
    int length = elems.size();
    for (int j = 0; j < length; j++) {
      tmp.push_back(elems[j]);
    }
  }
  return tmp;
}
bool index_table_one::write(int blocknum){
  for (int i = 0; i < INDEX_TABLE_SIZE; i++) {
    if (this->index_table_first[i].write(blocknum)) {
      return true;
    }
  }
  return false;
}

// index_table_two 类
class index_table_two{
  public:
    vector<int> get_all_block_index();
    bool write(int blocknum);
  private:
    index_table_one index_table_second[INDEX_TABLE_SIZE];
};
vector<int> index_table_two::get_all_block_index(){
  vector<int> tmp;
  for (int i = 0; i < INDEX_TABLE_SIZE; i++) {
    vector<int> elems = this->index_table_second[i].get_all_block_index();
    int length = elems.size();
    for (int j = 0; j < length; j++) {
      tmp.push_back(elems[j]);
    }
  }
  return tmp;
}
bool index_table_two::write(int blocknum){
  for (int i = 0; i < INDEX_TABLE_SIZE; i++) {
    if (this->index_table_second[i].write(blocknum)) {
      return true;
    }
  }
  return false;
}

// index_table_three 类
class index_table_three{
  public:
    vector<int> get_all_block_index();
    bool write(int blocknum);
  private:
    index_table_two index_table_third[INDEX_TABLE_SIZE];
};
vector<int> index_table_three::get_all_block_index(){
  vector<int> tmp;
  for (int i = 0; i < INDEX_TABLE_SIZE; i++) {
    vector<int> elems = this->index_table_third[i].get_all_block_index();
    int length = elems.size();
    for (int j = 0; j < length; j++) {
      tmp.push_back(elems[j]);
    }
  }
  return tmp;
}
bool index_table_three::write(int blocknum){
  for (int i = 0; i < INDEX_TABLE_SIZE; i++) {
    if (this->index_table_third[i].write(blocknum)) {
      return true;
    }
  }
  return false;
}
