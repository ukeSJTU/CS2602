#include "seqList.h"
#include <iostream>

int main() {
  SeqList<int> list1(20), list2(20), list3(20);
  int i, j, x;
  int len1, len3;

  // input the elements in the first set, ends with 0
  i = 1;
  std::cout << "输入第一个正整数集合，以零为结束标志：";
  std::cin >> x;

  while (x != 0) {
    list1.insert(i, x);
    i++;
    std::cin >> x;
  }
}
