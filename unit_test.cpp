#include <iostream>
#include "inode.h"
#include "disk.h"
using namespace std;

void line_print(){
  for (int i = 0; i < 80; i++)
  {
    cout << "-";
  }
  cout << endl;
}

int main(){
  line_print();
  disk d;
  d.initiate();
  inode i;
  i.initiate_inode(99, d); //注意这里是 byte
  vector<int> b;
  b = d.write(1020); //注意这里是 block
  if (b.empty()){
    cout << "Write Is OK" << endl;
  }
  if (d.read(100) == 1){
    d.delete_block(100);
    if (d.read(100) == 0)
      cout << "Delete Is OK" << endl;
    else
      cout << "Delete Wrong" << endl;
  }
  if (i.direct[8] == 8 and i.table_three.get_all_block_index()[2]==0){
      cout << "inode is OK" << endl;
  }
  return 0;
}