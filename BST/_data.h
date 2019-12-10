/*************************************************************************
  > File Name: data.h
  > Author: anthony
  > Mail: w826581298@163.com
  > Created Time: Sun 08 Dec 2019 01:28:54 PM CST
 ************************************************************************/

#ifndef _DATA_H
#define _DATA_H
#include "_bst.h"
struct data {
  int key;
  char value[20];
};
E_CMP_VALUE cmp(const data& d1, const data& d2);
void print(const data& d);
#endif

