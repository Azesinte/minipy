#ifndef H_INTERPRETER
#define H_INTERPRETER

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <stack>
#include <vector>
#include <list>
#include <stdlib.h>
#include <math.h>
#include "mainhead.hpp"
using namespace std;

extern vector<VarNode> VARS;
//VarNode gen_int(int val);
//VarNode gen_real(double val);
//VarNode gen_id(string val);
//VarNode gen_string(string val);


VarNode add(VarNode a,VarNode b);
VarNode sub(VarNode a,VarNode b);
void out_assignExpr(VarNode a);
VarNode mul(VarNode a,VarNode b);
VarNode div(VarNode a,VarNode b);
VarNode mod(VarNode a,VarNode b);
VarNode CreateList(VarNode a);
VarNode AddListMember(VarNode a,VarNode b);
void printLIST(vector<VarNode> LP,VarNode a);
void printTUPLE(vector<VarNode> LP);
VarNode Call_CreateEmptyList(void);
VarNode Call_Assign(VarNode leftval, VarNode rightval);
VarNode search_table(VarNode a);
VarNode CreateArgList(VarNode a);
VarNode AddArgListMember(VarNode a,VarNode b);
VarNode LEN(VarNode a);
VarNode PRINT(VarNode a);
VarNode RANGE(VarNode a);
VarNode APPEND(VarNode a,VarNode b);
VarNode EmptyVarNode(void);
void out_VarNode(VarNode a);
VarNode LIST_CUT(VarNode a,VarNode b,VarNode c,VarNode d);
VarNode LIST_SUB(VarNode a,VarNode b);
VarNode RANGE(VarNode a);
VarNode APPEND(VarNode a,VarNode b);
VarNode TUPLE(VarNode a);
void Tuple_Turn(VarNode *a);
VarNode LIST(VarNode a);
void List_Turn(VarNode *a);

#endif /* H_INTERPRETER */



