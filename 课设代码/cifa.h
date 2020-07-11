#pragma once
#ifndef CIFA_H_INCLUDED
#define CIFA_H_INCLUDED

#include <iostream>
#include <vector> 
#include <string> 
#include <fstream> 
using namespace std;
#define max_num 30

string  key[16] = { "main","int","float","char","const","void",
                    "if","else","while","switch","case","default",
                    "for","printf","scanf","return" };//关键字
string  symbol[22] = { "=","+","-","*","/",
                         "<","<=",">",">=","!=",
                         "==","(",")","[","]",
                         "{","}",",",":",";"
                         "'","\"" };//界符
string iT[30];//标识符
double CT[30];//常数
string cT[30];//字符
string sT[30];//字符串


//判断是不是字母
bool isChar(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || ch >= 'A' && ch <= 'Z')
        return true;
    else return false;
}


//判断是不是数字 
bool isNum(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

//判断是不是关键字
int isKey(string a, string& z)
{
    int flag = -1;
    string c;
    for (int i = 0; i < 20; i++)
    {
        if (a == key[i])
        {
            z.append("<key ");
            c = to_string(i);
            c = to_string(i);
            z.append(c);
            z.append(">");
            return i;
        }

    }
    return flag;
}

//初始化各个表
void init_()
{
    int i;
    for (i = 0; i < max_num; i++)
    {
        iT[i] = "";//标识符
    }
    for (i = 0; i < max_num; i++)
    {
        CT[i] = -3333;//常数
    }
    for (i = 0; i < max_num; i++)
    {
        cT[i] = "";//字符
    }
    for (i = 0; i < max_num; i++)
    {
        sT[i] = "";//字符串
    }
}

//查、写入标识符表
void write_iT(string a, string& z)
{
    int i, flag = 0;
    string c;//将i转为string类型
    for (i = 0; i < max_num; i++)//查表
    {
        if (iT[i] != "")
        {
            if (iT[i] == a)
            {
                flag = 1;
                break;
            }
        }
        else break;
    }
    if (!flag)//不在表内，填表
    {
        for (; i < max_num; i++)//i正好指向末尾
        {
            if (iT[i] == "")
            {
                iT[i] = a;
                break;
            }
        }
    }
    z.append("<iT ");
    c = to_string(i);
    z.append(c);
    z.append(">");
}

//查、写入常数表
void write_CT(double a, string& z)
{
    int i, flag = 0;
    string c;
    for (i = 0; i < max_num; i++)//查表
    {
        if (CT[i] != -3333)
        {
            if (CT[i] == a)
            {
                flag = 1;
                break;
            }
        }
        else break;
    }

    if (!flag)//填表
        for (; i < max_num; i++)
        {
            if (CT[i] == -3333)
            {
                CT[i] = a;
                break;
            }
        }
    z.append("<CT ");
    c = to_string(i);
    z.append(c);
    z.append(">");
}

//查、写入字符表
void write_cT(char a, string& z)
{
    int i, flag = 0;
    string c;
    string b;
    b = a;
    for (i = 0; i < max_num; i++)//查表
    {
        if (cT[i] != "")
        {
            if (cT[i] == b)
            {
                flag = 1;
                break;
            }
        }
        else break;
    }

    if (!flag)//填表
        for (; i < max_num; i++)
        {
            if (cT[i] == "")
            {
                cT[i] = a;
                break;
            }
        }
    z.append("<cT ");
    c = to_string(i);
    z.append(c);
    z.append(">");
}

//查、写入字符串表
void write_sT(string a, string& z)
{
    int i, flag = 0;
    string c;
    for (i = 0; i < max_num; i++)//查表
    {
        if (sT[i] != "")
        {
            if (sT[i] == a)
            {
                flag = 1;
                break;
            }
        }
        else break;
    }

    if (!flag)//填表
        for (; i < max_num; i++)
        {
            if (sT[i] == "")
            {
                sT[i] = a;
                break;
            }
        }
    z.append("<sT ");
    c = to_string(i);
    z.append(c);
    z.append(">");
}

//输出界符token序列
void token_symbol(int i, string& z)
{
    string c;
    z.append("<symbol ");
    c = to_string(i);
    c = to_string(i);
    z.append(c);
    z.append(">");
}

//扫描目标文件，查填表并输出token序列
void scanner(string a, string& token)
{
    int i, size = a.size();

    for (i = 0; i < size; i++)
    {
        string word;//记录单词
        if (isChar(a[i]))//开头是字母，判断关键字、标识符
        {
            while ((isChar(a[i])) || (isNum(a[i])))
            {
                word += a[i];
                i++;
            }
            int flag;
            flag = isKey(word, token);

            if (flag == -1)
            {
                write_iT(word, token);
            }
            i--;
        }

        else if (isNum(a[i]))//开头是数字，常数表
        {
            while (isNum(a[i]))
            {
                word += a[i];
                i++;
            }
            if (a[i] == '.')
            {
                word += a[i];
                i++;
                while (isNum(a[i]))
                {
                    word += a[i];
                    i++;
                }
            }
            i--;
            double c = stod(word);//将string转为double
            write_CT(c, token);//查填常数表并输出token
        }

        else if (a[i] == '"')//开头是“，查填字符串表
        {
            token_symbol(21, token);
            i++;
            while (a[i] != '"')
            {
                word += a[i];
                i++;
            }
            write_sT(word, token);
            token_symbol(21, token);
        }

        else if (a[i] == '\'')//开头是'，查填字符表
        {
            token_symbol(18, token);
            i++;
            char b = a[i];
            i++;
            write_cT(b, token);
            token_symbol(18, token);
        }

        else//界符表
        {
            switch (a[i])//无争议界符直接输出
            {
            case '+': token_symbol(1, token); break;
            case '-': token_symbol(2, token); break;
            case '*': token_symbol(3, token); break;
            case '/': token_symbol(4, token); break;
            case '(': token_symbol(11, token); break;
            case ')': token_symbol(12, token); break;
            case '[': token_symbol(13, token); break;
            case ']': token_symbol(14, token); break;
            case '{': token_symbol(15, token); break;
            case '}': token_symbol(16, token); break;
            case ',': token_symbol(17, token); break;
            case ':': token_symbol(18, token); break;
            case ';': token_symbol(19, token); break;
            }

            if (a[i] == '<')//有争议界符进行讨论
            {
                i++;//读下一个字符
                if (a[i] == '=')
                    token_symbol(6, token);
                else
                {
                    token_symbol(5, token);
                    i--;//退回上个字符，防止下个循环跳过一个字符
                }
            }
            else if (a[i] == '>')
            {
                i++;
                if (a[i] == '=')
                    token_symbol(8, token);
                else
                {
                    token_symbol(7, token);
                    i--;//退回上个字符，防止下个循环跳过一个字符
                }
            }
            else if (a[i] == '=')
            {
                i++;
                if (a[i] == '=')
                    token_symbol(10, token);
                else
                {
                    token_symbol(0, token);
                    i--;//退回上个字符，防止下个循环跳过一个字符
                }
            }
        }
    }
}

//将文件内容读到string中
string read_file(string m)
{
    ifstream infile;
    string file;
    cout << "输入文件路径\n";
    cin >> file;
    infile.open(file, ios::in);//打开文件
    if (!infile.is_open())
        cout << "file open error";

    string c;
    char a;
    infile >> noskipws;//读入空格和\n
    while (infile >> a)
    {
        c = a;
        m.append(c);
    }
    infile.close();
    return m;
}








#endif#pragma once
