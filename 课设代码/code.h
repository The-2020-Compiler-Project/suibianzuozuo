#pragma once
#ifndef CODE_H_INCLUDED
#define CODE_H_INCLUDED
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "registers.h"
#include "Quaternion.h"
#include "semantic_analysis.h"
using namespace std;
//定义基本块的数据结构，定义代码表的基本结构，找到四元式的入口，划分基本块，遍历基本块进行代码生成

static int labelNum;
struct basicBlock//基本块
{
	string name;
	vector<Quaternion> qs;
	vector <string> codes;

	void add(Quaternion q)
	{
		qs.push_back(q);
	}
};

class codeTable
{
public:
	vector<basicBlock> block; //基本块数组

	void initblock();  //初始化基本块
	vector<string> createcode(Quaternion);//根据四元式生成目标代码
	void initblockcodes();//调用 根据四元式生成目标代码函数，向生成的对象的每个基本块的codes里写入代码

	codeTable()//构造函数
	{
		initblock();
		initblockcodes();
	}

	void printcodes();//打印目标代码
};

void codeTable::initblock()//把四元式划分成几个基本块
{
	for (int i = 0; i < Quaternions.size() - 1; i++)//确定入口语句
	{
		if (i == 0) {   //程序第一条为入口
			changeOut_port(0);
			continue;
		}
		//跳转到的语句为入口语句
		//跳转语句的下一行,为入口语句
		if (Quaternions[i - 1].op == "wh")//while跳转到的语句
		{
			changeOut_port(i);
		}
		if (Quaternions[i - 1].op == "we")//while 跳转到的语句和跳转语句的下一句都符合
		{
			changeOut_port(i);
		}
		if (Quaternions[i - 1].op == "do")//while 跳转语句的下一句
		{
			changeOut_port(i);
		}

		if (Quaternions[i - 1].op == "if")//if 跳转语句的下一句
		{
			changeOut_port(i);
		}
		if (Quaternions[i - 1].op == "el")//if 跳转到的语句和跳转语句的下一句都符合
		{
			changeOut_port(i);
		}
		if (Quaternions[i].op == "ie")//if 跳转到的语句
		{
			changeOut_port(i);
		}
	}

	for (int i = 0; i < Quaternions.size(); ) //把入口语句加入到基本块
	{
		basicBlock bl;
		bl.add(Quaternions[i]);
		i++;
		for (; i < Quaternions.size(); i++)
		{
			if (Quaternions[i].out_port == 1)
			{
				block.push_back(bl);
				break;
			}
			else
				bl.add(Quaternions[i]);
		}
		if (i == Quaternions.size())
			block.push_back(bl);
	}
}



void codeTable::initblockcodes()//向基本块的codes内容末尾写入代码
{
	for (int blockindex = 0; blockindex < block.size(); blockindex++)
	{
		for (int i = 0; i < block[blockindex].qs.size(); i++)
		{
			block[blockindex].codes = merge(block[blockindex].codes, createcode(block[blockindex].qs[i]));
		}
	}
}

void codeTable::printcodes()//输出目标代码
{
	cout << "目标代码：\n" << endl;
	for (int blockindex = 0; blockindex < block.size(); blockindex++)
	{
		for (int i = 0; i < block[blockindex].codes.size(); i++)
		{
			cout << "   " << block[blockindex].codes[i] << endl;
		}
	}
}

vector<string> judge_stack;//用于while语句目标代码生成
vector<string> label_stack;//用于while语句目标代码生成，存储跳转到的label
vector<string> label_stack2;//用于if语句目标代码生成，存储跳转到的label
vector<string> codeTable::createcode(Quaternion q)
{
	vector<string> codes;
	int code = q.code;
	string s;
	switch (code)
	{
	case 1://op = "*";
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("MUL R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("MUL R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 2://op = "+";

		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("ADD R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("ADD R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 3://op = "-";
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("SUB R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("SUB R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 4://op = "/";
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("DIV R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("DIV R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 5://op = "=";
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 6://op = ">"
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("GT R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("GT R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 7://op = "<"
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("LT R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("LT R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 8://op = ">="
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("GE R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("GE R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 9://op = "<="
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("LE R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("LE R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 10://op = "=="
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("EQ R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("EQ R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 11://op = "!="
		if (!inReg(q.addr1))
		{
			codes.push_back("LD R," + q.addr1);
			codes.push_back("NE R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		else
		{
			codes.push_back("NE R," + q.addr2);
			codes.push_back("ST R," + q.result);
		}
		regR.clearPush(q.result);
		break;

	case 12://op = "wh";
		int2str(labelNum, s);
		codes.push_back("LABEL" + s + ":");
		label_stack.push_back("LABEL" + s);
		labelNum++;
		break;

	case 13://op = "do";
		s = label_stack[label_stack.size() - 1];
		judge_stack.push_back("LD R," + q.addr1);
		judge_stack.push_back("TJ R," + s);
		break;

	case 14://op = "we";
		s = judge_stack[judge_stack.size() - 1];
		judge_stack.pop_back();
		codes.push_back(judge_stack.back());
		codes.push_back(s);
		break;

	case 15://op = "if";
		int2str(labelNum, s);
		label_stack2.push_back("LABEL" + s);
		codes.push_back("LD R," + q.addr1);
		codes.push_back("FJ R,LABEL" + s);
		labelNum++;
		break;

	case 16://op = "el";
		s = label_stack2.back();
		label_stack2.pop_back();
		label_stack2.push_back("else");
		codes.push_back(s + ":");
		break;

	case 17://op = "ie";
		s = label_stack2.back();
		if (s != "else")
		{
			codes.push_back(s + ":");
		}
		label_stack2.pop_back();
		break;

	default:
		break;
	}
	return codes;
}


#endif // CODE_H_INCLUDED