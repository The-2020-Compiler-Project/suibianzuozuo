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
//�������������ݽṹ����������Ļ����ṹ���ҵ���Ԫʽ����ڣ����ֻ����飬������������д�������

static int labelNum;
struct basicBlock//������
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
	vector<basicBlock> block; //����������

	void initblock();  //��ʼ��������
	vector<string> createcode(Quaternion);//������Ԫʽ����Ŀ�����
	void initblockcodes();//���� ������Ԫʽ����Ŀ����뺯���������ɵĶ����ÿ���������codes��д�����

	codeTable()//���캯��
	{
		initblock();
		initblockcodes();
	}

	void printcodes();//��ӡĿ�����
};

void codeTable::initblock()//����Ԫʽ���ֳɼ���������
{
	for (int i = 0; i < Quaternions.size() - 1; i++)//ȷ��������
	{
		if (i == 0) {   //�����һ��Ϊ���
			changeOut_port(0);
			continue;
		}
		//��ת�������Ϊ������
		//��ת������һ��,Ϊ������
		if (Quaternions[i - 1].op == "wh")//while��ת�������
		{
			changeOut_port(i);
		}
		if (Quaternions[i - 1].op == "we")//while ��ת����������ת������һ�䶼����
		{
			changeOut_port(i);
		}
		if (Quaternions[i - 1].op == "do")//while ��ת������һ��
		{
			changeOut_port(i);
		}

		if (Quaternions[i - 1].op == "if")//if ��ת������һ��
		{
			changeOut_port(i);
		}
		if (Quaternions[i - 1].op == "el")//if ��ת����������ת������һ�䶼����
		{
			changeOut_port(i);
		}
		if (Quaternions[i].op == "ie")//if ��ת�������
		{
			changeOut_port(i);
		}
	}

	for (int i = 0; i < Quaternions.size(); ) //����������뵽������
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



void codeTable::initblockcodes()//��������codes����ĩβд�����
{
	for (int blockindex = 0; blockindex < block.size(); blockindex++)
	{
		for (int i = 0; i < block[blockindex].qs.size(); i++)
		{
			block[blockindex].codes = merge(block[blockindex].codes, createcode(block[blockindex].qs[i]));
		}
	}
}

void codeTable::printcodes()//���Ŀ�����
{
	cout << "Ŀ����룺\n" << endl;
	for (int blockindex = 0; blockindex < block.size(); blockindex++)
	{
		for (int i = 0; i < block[blockindex].codes.size(); i++)
		{
			cout << "   " << block[blockindex].codes[i] << endl;
		}
	}
}

vector<string> judge_stack;//����while���Ŀ���������
vector<string> label_stack;//����while���Ŀ��������ɣ��洢��ת����label
vector<string> label_stack2;//����if���Ŀ��������ɣ��洢��ת����label
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