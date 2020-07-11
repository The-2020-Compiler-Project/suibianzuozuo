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
                    "for","printf","scanf","return" };//�ؼ���
string  symbol[22] = { "=","+","-","*","/",
                         "<","<=",">",">=","!=",
                         "==","(",")","[","]",
                         "{","}",",",":",";"
                         "'","\"" };//���
string iT[30];//��ʶ��
double CT[30];//����
string cT[30];//�ַ�
string sT[30];//�ַ���


//�ж��ǲ�����ĸ
bool isChar(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || ch >= 'A' && ch <= 'Z')
        return true;
    else return false;
}


//�ж��ǲ������� 
bool isNum(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

//�ж��ǲ��ǹؼ���
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

//��ʼ��������
void init_()
{
    int i;
    for (i = 0; i < max_num; i++)
    {
        iT[i] = "";//��ʶ��
    }
    for (i = 0; i < max_num; i++)
    {
        CT[i] = -3333;//����
    }
    for (i = 0; i < max_num; i++)
    {
        cT[i] = "";//�ַ�
    }
    for (i = 0; i < max_num; i++)
    {
        sT[i] = "";//�ַ���
    }
}

//�顢д���ʶ����
void write_iT(string a, string& z)
{
    int i, flag = 0;
    string c;//��iתΪstring����
    for (i = 0; i < max_num; i++)//���
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
    if (!flag)//���ڱ��ڣ����
    {
        for (; i < max_num; i++)//i����ָ��ĩβ
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

//�顢д�볣����
void write_CT(double a, string& z)
{
    int i, flag = 0;
    string c;
    for (i = 0; i < max_num; i++)//���
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

    if (!flag)//���
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

//�顢д���ַ���
void write_cT(char a, string& z)
{
    int i, flag = 0;
    string c;
    string b;
    b = a;
    for (i = 0; i < max_num; i++)//���
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

    if (!flag)//���
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

//�顢д���ַ�����
void write_sT(string a, string& z)
{
    int i, flag = 0;
    string c;
    for (i = 0; i < max_num; i++)//���
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

    if (!flag)//���
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

//������token����
void token_symbol(int i, string& z)
{
    string c;
    z.append("<symbol ");
    c = to_string(i);
    c = to_string(i);
    z.append(c);
    z.append(">");
}

//ɨ��Ŀ���ļ�����������token����
void scanner(string a, string& token)
{
    int i, size = a.size();

    for (i = 0; i < size; i++)
    {
        string word;//��¼����
        if (isChar(a[i]))//��ͷ����ĸ���жϹؼ��֡���ʶ��
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

        else if (isNum(a[i]))//��ͷ�����֣�������
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
            double c = stod(word);//��stringתΪdouble
            write_CT(c, token);//����������token
        }

        else if (a[i] == '"')//��ͷ�ǡ��������ַ�����
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

        else if (a[i] == '\'')//��ͷ��'�������ַ���
        {
            token_symbol(18, token);
            i++;
            char b = a[i];
            i++;
            write_cT(b, token);
            token_symbol(18, token);
        }

        else//�����
        {
            switch (a[i])//��������ֱ�����
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

            if (a[i] == '<')//����������������
            {
                i++;//����һ���ַ�
                if (a[i] == '=')
                    token_symbol(6, token);
                else
                {
                    token_symbol(5, token);
                    i--;//�˻��ϸ��ַ�����ֹ�¸�ѭ������һ���ַ�
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
                    i--;//�˻��ϸ��ַ�����ֹ�¸�ѭ������һ���ַ�
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
                    i--;//�˻��ϸ��ַ�����ֹ�¸�ѭ������һ���ַ�
                }
            }
        }
    }
}

//���ļ����ݶ���string��
string read_file(string m)
{
    ifstream infile;
    string file;
    cout << "�����ļ�·��\n";
    cin >> file;
    infile.open(file, ios::in);//���ļ�
    if (!infile.is_open())
        cout << "file open error";

    string c;
    char a;
    infile >> noskipws;//����ո��\n
    while (infile >> a)
    {
        c = a;
        m.append(c);
    }
    infile.close();
    return m;
}








#endif#pragma once
