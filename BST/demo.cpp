/*************************************************************************
  > File Name: data.c
  > Author: Wang Di
  > Mail: w826581298@163.com
  > Created Time: Sun 08 Dec 2019 01:30:46 PM CST
 ************************************************************************/
#include <iostream>
#include "_bst.h"
#include "_data.h"

 //The test data
data arr[11]{
  2,"Wang Er",
  3,"Zhang san",
  1,"Li Si",
  5,"Ma Zi",
  4,"Zhang Yide",
  4,"Guan Yunchang",
  7,"Zhao Ziong",
  5,"Liu Xuande",
  9,"Cao Mengde",
  0,"Lv Fengxian",
  1,"Diao Chan"
};
int main() {
  BST<data> bst;
  //Test the init() and put()
  bst.init(&cmp);
  std::cout << "Init the bst and put the original data.Visit it with inOrder function:\n";
  for (int i = 0; i < 8; i++) {
    bst.put(arr[i]);
  }

  //Test the getSize()
  std::cout << "The size of the bst is:" << bst.getSize() << "\n";
  data* b = bst.inOrder();
  for (int i = 0; i < bst.getSize(); i++) {
    print(b[i]);
    std::cout << "\n";
  }
  delete b; b = nullptr;
  std::cout << "Put data {9,\"Cao Mengde\"} to the bst and visit it with inOrder function:\n";
  bst.put(arr[8]);
  std::cout << "The size of the bst is:" << bst.getSize() << "\n";
  b = bst.inOrder();
  for (int i = 0; i < bst.getSize(); i++) {
    print(b[i]);
    std::cout << "\n";
  }
  delete b; b = nullptr;
  std::cout << "Put data {0,\"Lv Fengxian\"} and {1,\"Diao Chan\"} to the bst and visit it with inOrder function:\n";
  bst.put(arr[9]);
  bst.put(arr[10]);
  std::cout << "The size of the bst is:" << bst.getSize() << "\n";
  b = bst.inOrder();
  for (int i = 0; i < bst.getSize(); i++) {
    print(b[i]);
    std::cout << "\n";
  }
  delete b; b = nullptr;

  //Test the 3 different travesal
  std::cout << "Visit the bst with preOrder function:\n";
  b = bst.preOrder();
  for (int i = 0; i < bst.getSize(); i++) {
    print(b[i]);
    std::cout << "\n";
  }
  delete b; b = nullptr;
  std::cout << "Visit the bst with postOrder function:\n";
  b = bst.postOrder();
  for (int i = 0; i < bst.getSize(); i++) {
    print(b[i]);
    std::cout << "\n";
  }
  delete b; b = nullptr;

  //Test the get()
  std::vector<data> v;
  data d{ 4 };
  std::cout << "Search the element whose key equals 4:\n";
  bst.get(d, v);
  for (data tmp : v) {
    print(tmp);
    std::cout << "\n";
  }

  //Test the remove()
  for (int i = 0; i < 3; i++) {
    int num = bst.remove(arr[10 - i]);
    b = bst.inOrder();
    std::cout << "After remove key " << arr[10 - i].key << " and inOrder the bst:(" << num << " elements has been removed)\n";
    std::cout << "The size of the bst is:" << bst.getSize() << "\n";
    for (int i = 0; i < bst.getSize(); i++) {
      print(b[i]);
      std::cout << "\n";
    }
  }
  delete b; b = nullptr;
  return 0;
}
