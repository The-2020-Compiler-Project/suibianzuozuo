#ifndef STABLE_H_INCLUDED
#define STABLE_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

typedef struct snode snode;
typedef struct tnode tnode;
typedef struct arrnode arrnode;
typedef struct strunode strunode;
typedef struct fnode fnode;
typedef struct cnode cnode;
typedef struct lnode lnode;

void addnode(string name, string cat, char tval);

//符号总表SYNBL结点
struct snode
{
	string name;  //名字
	tnode* typel; //类型 指向类型表
	string cat;  //种类
	int addr;//地址(类型不确定的指针，定为int,在用到时会强制转换为想要的类型)
	snode* next = NULL;  //指向下一个节点
};

//类型表TAPEL结点
struct tnode
{
	char tval;//类码
	//i（整型)，r(实型)，c(字符型)，b(布尔型)，
	//a(数组型)，d(结构型)

	int* tpoint;//(类型不确定的指针，定为int,在用到时会强制转换为想要的类型)
	// 基本数据类型(i,r,c,b)– nul(空指针)；
	// 数组类型(a) – 指向数组表;
	// 结构类型(d) – 指向结构表;
	tnode* next;
};


//信息表节点（数组和结构体）
struct arrnode
{
	int low;//数组下界
	int up;//数组上界
	tnode* ctp;//指向该数组成分类型（类型表中信息）
	int clen;//成分类型的数据所占值单元个数

	arrnode* next = NULL;
};

struct strunode
{
	string id;//结构体域名
	int off;//区距
	tnode* tp;//指针，指向域成分类型(在类型表中的信息);

	strunode* next = NULL;
};

//函数表
struct fnode
{
	int level;//层次号
	int off;//区距
	int fn;//参数个数
	string entry;//入口地址
	fnode* next = NULL;
};

//常量表
struct cnode
{
	int consl;//常量的初值
	cnode* next = NULL;
};

//长度表
struct lnode
{
	int lenl;//数据类型所占值单元个数
	lnode* next = NULL;
};


//各表的头和尾
snode* shead = new snode;
tnode* thead = new tnode;

arrnode* arrhead = new arrnode;
strunode* struhead = new strunode;
fnode* fhead = new fnode;
cnode* chead = new cnode;
lnode* lhead = new lnode;

snode* stail = shead;
tnode* ttail = thead;
arrnode* arrtail = arrhead;
strunode* strutail = struhead;
fnode* ftail = fhead;
cnode* ctail = chead;
lnode* ltail = lhead;


#endif // STABLE_H_INCLUDED#pragma once
