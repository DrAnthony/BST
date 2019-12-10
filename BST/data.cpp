/*************************************************************************
  > File Name: data.c
  > Author: Wang Di
  > Mail: w826581298@163.com
  > Created Time: Sun 08 Dec 2019 01:30:46 PM CST
 ************************************************************************/

#include <iostream>
#include "_data.h"

 //Init how to compare two data nodes
E_CMP_VALUE cmp(const data& d1, const data& d2) {
  if (d2.key < d1.key) {
    return SMALLER;
  }
  if (d2.key > d1.key) {
    return BIGGER;
  }
  return EQUAL;
}
//Init how to print the data node
void print(const data& d) {
  std::cout << d.key << "\t" << d.value;
}
