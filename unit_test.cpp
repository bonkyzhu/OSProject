#include <iostream>
#include "diskmanager.h"
using namespace std;

int main(){
  diskmanager test;
  test.initiate();
  test.CreateFile("test1", "sdfsdfdsgsdfdsfhadhgdskgjhfiadku");
  cout << "Data is " << test.ReadFile("test1") << endl;
  test.DeleteFile("test1");
  cout << "After Delete " << test.ReadFile("test1") << endl;
  return 0;
}