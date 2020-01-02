#include <iostream>
#include "diskmanager.h"
using namespace std;

int main(){
  A_Disk.CreateFile("test1", "sdfsdfdsgsdfdsfhadhgdskgjhfiadku");
  cout << "Data is " << A_Disk.ReadFile("test1") << endl;
  A_Disk.DeleteFile("test1");
  cout << "After Delete " << A_Disk.ReadFile("test1") << endl;
  return 0;
}