#include <iostream>
#include "define.h"
#include "diskmanager.h"
#include "dirmanager.h"
#include "memmanager.h"
using namespace std;

int main(){
  // 目录管理和磁盘管理测试
  Dirs.CreatDir("admin", "test1", "1");
  A_Disk.CreateFile("test1", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  Dirs.CreatDir("admin", "test2", "1");
  A_Disk.CreateFile("test2", "dsfasdf");
  Dirs.ShowDirMan();
  cout << "Data is " << A_Disk.ReadFile("test1") << endl;
  cout << "Data is " << A_Disk.ReadFile("test2") << endl;
//  Dirs.DelFile("test1");
  cout << "After Delete " << A_Disk.ReadFile("test1") << endl;

  //
  cout << "--------------" << endl;
  Mems.Alloc(3, "test2");
  Mems.show();
  cout << "--------------" << endl;
  Mems.Alloc(5, "test1");
  Mems.show();
  return 0;
}