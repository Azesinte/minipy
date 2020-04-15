#ifndef MAINHEAD_H
#define MAINHEAD_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define ERROR_type -1
#define INT_type 0
#define REAL_type 1
#define STRING_type 2
#define LIST_type 3
#define ID_type 4
//#define SUBLIST_type 5
#define ArgLIST_type 9
#define FUNC_APPEND 10
#define FUNC_RANGE 11
#define FUNC_PRINT 12
#define FUNC_LEN 13
#define FUNC_LIST 14
#define FUNC_QUIT 15
#define FUNC_TUPLE 16

typedef struct VarNode{
   int _type;
   int _INT;
   double _REAL;
   int _ID_defined;// 这是否是一个已经赋值的ID :0 未赋值 或不是id 1： 已赋值
   int _iteration;//  list是否是一个迭代的数组  0：非迭代  >0：已迭代
   int _TUPLE;// 0:list; 1:tuple
   string _STRING;
   string _ID;
   vector<VarNode> _LIST;
   vector<VarNode> _List_Arg; 
}VarNode;

//#define YYSTYPE VarNode

//vector<VarNode> VARS;


#endif /* MAIN_H */
