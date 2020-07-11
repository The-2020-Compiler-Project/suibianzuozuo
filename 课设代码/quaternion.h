#pragma once
#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include "semantic_analysis.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
void int2str(const int& int_temp, string& string_temp);

struct Quaternion
{
	int label;
	string op;      //第一元素
	int code;     //第一元素的code形式
	string addr1 = "0"; //第二元素
	string addr2 = "0"; //第三元素
	string result = "0";//第四元素
	int out_port = 0;  //记录该四元式是否为一个基本块的入口，是则为1，否则为0。

	void ConvertOpToCode(string);

	Quaternion() {}
	Quaternion(int l) { label = l; }
	Quaternion(int l, string op, string a1, string a2, string res)//构造函数
	{
		label = l, this->op = op, ConvertOpToCode(op), addr1 = a1, addr2 = a2, result = res;
	}
};

vector<Quaternion> Quaternions;  //四元式集合

vector<string> merge(vector<string> vec1, vector<string>vec2)//把两个字符串数组的内容合并
{
	vector<string>vec3;
	vec3.insert(vec3.end(), vec1.begin(), vec1.end());
	vec3.insert(vec3.end(), vec2.begin(), vec2.end());
	return vec3;
}


void CreateQ(string op, string al, string a2, string res)  //把四元式存入Quaternions准备用于目标代码生成
{
	Quaternion t(Quaternions.size(), op, al, a2, res);
	Quaternions.push_back(t);
}


void Quaternion::ConvertOpToCode(string op)
{
	if (op == "*") code = 1;
	else if (op == "+") code = 2;
	else if (op == "-") code = 3;
	else if (op == "/") code = 4;
	else if (op == "=") code = 5;

	else if (op == ">") code = 6;
	else if (op == "<") code = 7;
	else if (op == ">=") code = 8;
	else if (op == "<=") code = 9;
	else if (op == "==") code = 10;
	else if (op == "!=") code = 11;

	else if (op == "wh") code = 12;
	else if (op == "do") code = 13;
	else if (op == "we") code = 14;
	else if (op == "if") code = 15;
	else if (op == "el") code = 16;
	else if (op == "ie") code = 17;

	else
		code = 0;
}


void int2str(const int& int_temp, string& string_temp)   //int 转string
{
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();   //此处也可以用 stream>>string_temp

}

void changeOut_port(int index) //设置四元式入口
{
	if (index >= Quaternions.size()) return;
	Quaternions[index].out_port = 1;
}



#endif // QUATERNION_H_INCLUDED#pragma once
