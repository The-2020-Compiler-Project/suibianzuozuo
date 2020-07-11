#pragma once
#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H


#include "quaternion.h"
#include<iostream>
#include<stack>	
#include<iomanip>
using namespace std;

int t_number = 0;
int QT_number = 0;
string T[20] = { "t1","t2","t3","t4","t5","t6","t7","t8","t9","t10","t11","t12","t13","t14","t15","t16","t17","t18","t19","t20" };

int abc;

struct wordinfo  //token结构 
{
	int code;
	int	value;
};


struct quaNode  //四元式数据结构 
{
	string ope;   //第一个元素 
	string ele1;  //第二个元素 
	string ele2;  //第三个元素 
	string res;   ///第四个元素 

	int out_port = 0;
	quaNode* next;
};


stack <string> SEM;  //语义栈
quaNode QT[40];   //存放四元式 


void GEQ(string c)    //表达式四元式生成函数 
{

	quaNode q;
	q.ope = c;
	q.ele2 = SEM.top();
	SEM.pop();
	q.ele1 = SEM.top();
	SEM.pop();
	q.res = T[t_number]  /*eval(q.ele1,q.ele2,q.ope)*/;
	SEM.push(q.res);
	QT[QT_number] = q;
	QT_number = QT_number + 1;
	t_number = t_number + 1;
}




void ASSI()    //赋值函数 
{
	quaNode q;
	q.ope = '=';
	q.ele1 = SEM.top();
	SEM.pop();
	q.res = SEM.top();
	SEM.pop();
	QT[QT_number] = q;
	QT_number = QT_number + 1;
}

void IF()   //if函数 
{
	quaNode q;
	q.ope = "if";
	q.ele1 = SEM.top();
	SEM.pop();
	QT[QT_number] = q;
	QT_number = QT_number + 1;
}

void EL()			//else函数 
{
	quaNode q;
	q.ope = "el";
	QT[QT_number] = q;
	QT_number = QT_number + 1;
}

void IE()				//ifend  函数 
{
	quaNode q;
	q.ope = "ie";
	QT[QT_number] = q;
	QT_number = QT_number + 1;
}


void WH()  		//循环头 函数 
{
	quaNode q;
	q.ope = "wh";
	QT[QT_number] = q;
	QT_number = QT_number + 1;
}

void DO()			//DO函数
{
	quaNode q;
	q.ope = "do";
	q.ele1 = SEM.top();
	SEM.pop();
	QT[QT_number] = q;
	QT_number = QT_number + 1;
}

void WE()			//循环尾  函数 
{
	quaNode q;
	q.ope = "we";
	QT[QT_number] = q;
	QT_number = QT_number + 1;
}


void print_quaternion()
{
	cout << "\n\n\n" << "四元式：\n" << endl;
	for (int i = 0; i < QT_number; i++)	//转换成目标代码需要的结构
	{
		quaNode q1;
		q1 = QT[i];
		cout << "(" << q1.ope << " , " << q1.ele1 << " , " << q1.ele2 << " , " << q1.res << ")" << endl;
	}
	cout << "\n共" << QT_number << "组四元式\n\n\n\n\n" << endl;
}


void change()
{
	quaNode q;
/*	for (int i = 0; i < 23; i++)
	{
		QT[i] = q;
	}

	QT[0].ope = "="; QT[0].ele1 = "5"; QT[0].ele2 = ""; QT[0].res = "b";
	QT[1].ope = "="; QT[1].ele1 = "1"; QT[1].ele2 = ""; QT[1].res = "a";
	QT[2].ope = "-"; QT[2].ele1 = "b"; QT[2].ele2 = "1"; QT[2].res = "t1";
	QT[3].ope = "="; QT[3].ele1 = "t1"; QT[3].ele2 = ""; QT[3].res = "c";
	QT[4].ope = "-"; QT[4].ele1 = "b"; QT[4].ele2 = "a"; QT[4].res = "t2";
	QT[5].ope = "*"; QT[5].ele1 = "t2"; QT[5].ele2 = "2"; QT[5].res = "t3";
	QT[6].ope = "="; QT[6].ele1 = "t3"; QT[6].ele2 = ""; QT[6].res = "d";
	QT[7].ope = "wh";QT[7].ele1 = ""; QT[7].ele2 = ""; QT[7].res = "";
	QT[8].ope = "<"; QT[8].ele1 = "c"; QT[8].ele2 = "d"; QT[8].res = "t4";
	QT[9].ope = "do"; QT[9].ele1 = "t4"; QT[9].ele2 = ""; QT[9].res = "";
	QT[10].ope = "<"; QT[10].ele1 = "c"; QT[10].ele2 = "5"; QT[10].res = "t5";
	QT[11].ope = "if"; QT[11].ele1 = "t5"; QT[11].ele2 = ""; QT[11].res = "";
	QT[12].ope = "-"; QT[12].ele1 = "b"; QT[12].ele2 = "c"; QT[12].res = "t6";
	QT[13].ope = "="; QT[13].ele1 = "t6"; QT[13].ele2 = ""; QT[13].res = "a";
	QT[14].ope = "+"; QT[14].ele1 = "c"; QT[14].ele2 = "1"; QT[14].res = "t7";
	QT[15].ope = "="; QT[15].ele1 = "t7"; QT[15].ele2 = ""; QT[15].res = "c";
	QT[16].ope = "el"; QT[16].ele1 = ""; QT[16].ele2 = ""; QT[16].res = "";
	QT[17].ope = "-"; QT[17].ele1 = "c"; QT[17].ele2 = "b"; QT[17].res = "t8";
	QT[18].ope = "="; QT[18].ele1 = "t8"; QT[18].ele2 = ""; QT[18].res = "a";
	QT[19].ope = "+"; QT[219].ele1 = "c"; QT[19].ele2 = "1"; QT[19].res = "t9";
	QT[20].ope = "="; QT[20].ele1 = "t10"; QT[20].ele2 = ""; QT[20].res = "c";
	QT[21].ope = "ie"; QT[21].ele1 = ""; QT[21].ele2 = ""; QT[21].res = "";
	QT[22].ope = "we"; QT[22].ele1 = ""; QT[22].ele2 = ""; QT[22].res = "";*/


	for (int i = 0; i < QT_number; i++)	//转换成目标代码需要的结构
	{
		quaNode q1;
		q1 = QT[i];
		CreateQ(q1.ope, q1.ele1, q1.ele2, q1.res);
		//	cout << "(" << q1.ope << " , " << q1.ele1 << " , " << q1.ele2 << " , " << q1.res << ")" << endl;
	}

	for (int i = 0; i < QT_number; i++)		//输出转换完的结构
	{
		Quaternion q1;
		q1 = Quaternions[i];
	//	cout << std::left << setw(3) << q1.label << "(" << q1.op << " , " << q1.addr1 << " , " << q1.addr2 << " , " << q1.result << ")" << endl;
	}
}













#endif