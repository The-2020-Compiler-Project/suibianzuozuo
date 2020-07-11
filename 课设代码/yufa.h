#pragma once
#ifndef YUFA_H_INCLUDE
#define YUFA_H_INCLUDE


#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

#include "semantic_analysis.h"
#include "cifa.h"

using namespace std;


string DoubleToString(double d)
{
    //Need #include <sstream>
    using namespace std;
    string str;
    stringstream ss;
    ss << d;
    ss >> str;
    return str;
}

string tk_num_1;                //�ж�if�������Ľ���λ��


void item(string& token);

void next_tk(string& token, string& tk_id, string& tk_num, int k)
{
    tk_id.clear();
    tk_num.clear();
    int i = 0, j;
    //i=1Խ��<
    if (token.size() == 0)
    {
        cout << "token�Ѷ���,�﷨��ȷ" << endl;
    }
    else
    {
        for (j = 1; j != k; )
        {
            for (; token[i] != '>'; i++);
            i++;
            j++;
        }
        i++;
        //��j=kʱ����k��token
        for (; token[i] != ' '; i++)
        {
            tk_id.push_back(token[i]);
        }
        for (i++; token[i] != '>'; i++) tk_num.push_back(token[i]);
    }

}

void erase_tk(string& token)        //ɾ��string���Ѿ���������token
{
    int i;
    int size = token.size();
    if (size == 0);
    else {
        for (i = 0; token[i] != '>'; i++);
        token.erase(0, i + 1);
    }
}

//<����>   <����> main() <�ֳ���>
void program(string& token)
{
    void type(string & token);   //����
    void sub_program(string & token);    //�ֳ���
    string tk_id, tk_num;
    type(token);
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "key" && tk_num == "0")		//main 
    {
        erase_tk(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "11")		//(
        {
            erase_tk(token);
            next_tk(token, tk_id, tk_num, 1);
            if (tk_id == "symbol" && tk_num == "12")		//)
            {
                erase_tk(token);
                sub_program(token);
            }
            else
                cout << "program_wrong1";
        }
        else
            cout << "program_wrong2";
    }
    else
        cout << "program_wrong3";
}

//<����>  int | float  | char
void type(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "key" && (tk_num == "1" || tk_num == "2" || tk_num == "3"))
    {
        erase_tk(token);
    }
    else
        cout << "type_wrong";
}


//<�ֳ���>->�������' ���� 
void sub_program(string& token)
{
    void com_sentence1(string & token);       //�������' 
    void back(string & token);               //����
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    com_sentence1(token);
    next_tk(token, tk_id, tk_num, 1);
    back(token);
}

//�������' -> {�������}|��
void com_sentence1(string& token)
{
    void com_sentence(string & token);
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    while (!(tk_id == "key" && tk_num == "15"))
    {
        com_sentence(token);
        next_tk(token, tk_id, tk_num, 1);
    }
}


//<�������> -> <����> | <ѡ�����> | <ѭ�����> |�� 
void com_sentence(string& token)
{
    void sentence_table(string & token);         //����
    void select_sentence(string & token);        //ѡ�����
    void loop_sentence(string & token);          //ѭ�����
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "symbol" && tk_num == "15")
    {
        erase_tk(token);
    }
    if (tk_id == "iT" || (tk_id == "key" && (tk_num == "1" || tk_num == "2" || tk_num == "3")))      //����
    {
        sentence_table(token);
    }
    else if (tk_id == "key" && (tk_num == "6" || tk_num == "7"))                        //ѡ�����
    {
        select_sentence(token);
    }
    else if (tk_id == "key" && tk_num == "8")                                   //ѭ�����
    {
        loop_sentence(token);
    }
}

//<����>  <��ֵ���> ;<����> | <����˵��><����> | ��
void sentence_table(string& token)
{
    void assign_sentence(string & token);        //��ֵ���
    void variable(string & token);               //����˵��
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "iT")
    {
        assign_sentence(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "19")     //;
        {
            sentence_table(token);
        }
    }
    else if (tk_id == "key" && (tk_num == "1" || tk_num == "2" || tk_num == "3"))         //����˵��
    {
        variable(token);
    }
}

//<��ֵ���>  <��ʶ��> = <�������ʽ>
void assign_sentence(string& token)
{
    void id(string & token);         //��ʶ��
    void ari_expression(string & token);     //�������ʽ
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    id(token);

    SEM.push(iT[atoi(tk_num.c_str())]);

    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "symbol" && tk_num == "0")      //=
    {
        erase_tk(token);
        ari_expression(token);

        ASSI();
    }
    else
    {
        cout << "assign_sentence_wrong";
    }
}

//<��ʶ��>
void id(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "iT")
    {
        erase_tk(token);
    }
    else
        cout << "wrong4";
}

//�������ʽ-> <��>{��0<��>}|�� 

void ari_expression(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    item(token);
    next_tk(token, tk_id, tk_num, 1);
    while (tk_id == "symbol" && (tk_num == "1" || tk_num == "2"))         //+   -
    {
        erase_tk(token);
        item(token);
        if (tk_num == "1")
            GEQ("+");
        else
            GEQ("-");
        next_tk(token, tk_id, tk_num, 1);
    }
}

//<��>  ->   <����>{w1<����>}
void item(string& token)
{
    void factor(string & token);
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    factor(token);
    next_tk(token, tk_id, tk_num, 1);
    while (tk_id == "symbol" && (tk_num == "3" || tk_num == "4"))    //* /
    {
        erase_tk(token);
        item(token);
        if (tk_num == "3")
            GEQ("*");
        else
            GEQ("/");

        next_tk(token, tk_id, tk_num, 1);
    }
}


//����  -> <��ʶ��>|<����>|<(�������ʽ)>
void factor(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "iT")
    {
        erase_tk(token);
        SEM.push(iT[atoi(tk_num.c_str())]);
    }
    else if (tk_id == "CT")
    {
        erase_tk(token);
        /*  CT[30] = 1;
          cout << "tk_num::" << tk_num << endl;
          int b;
          b = atoi(tk_num.c_str());
         cout << "atoi(tk_num.c_str())::" << b << endl;
          double a;
          a = CT[30];
          cout << "CT[30]::" << a << endl;
          string c;
          c = DoubleToString(a);
          cout << "DoubleToString(a)::" << c << endl;*/
        SEM.push(DoubleToString(CT[atoi(tk_num.c_str())]));
    }
    else if (tk_id == "symbol" && tk_num == "11")    //   (
    {
        erase_tk(token);
        ari_expression(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "12")     //   )
        {
            erase_tk(token);
        }
        else
            cout << "factor_wrong1";
    }
    else
        cout << "factor_wrong2";
}


//<����˵��> -> <����><��ʶ��>{,<��ʶ��>}; 
void variable(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    type(token);
    next_tk(token, tk_id, tk_num, 1);
    id(token);
    next_tk(token, tk_id, tk_num, 1);
    while (tk_id == "symbol" && tk_num == "17")     //   ,
    {
        erase_tk(token);
        id(token);
        next_tk(token, tk_id, tk_num, 1);
    }
    if (tk_id == "symbol" && tk_num == "19")         //    ;
    {
        erase_tk(token);
    }
    else
        cout << "variable_wrong";
}


//<ѡ�����> -> <ѡ������><ѡ������>
void select_sentence(string& token)
{
    void select_condition(string & token);           //ѡ������
    void select_subject(string & token);             //ѡ������
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    select_condition(token);
    next_tk(token, tk_id, tk_num, 1);
    select_subject(token);
}


//<ѡ������> -> if (<�߼����ʽ>) |else <else��֧>
void select_condition(string& token)
{
    void logic_expression(string & token);           //�߼����ʽ
    void else_branch(string & token);                //else��֧
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "key" && tk_num == "6")             //if
    {
        tk_num_1 = tk_num;
        erase_tk(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "11")             //(
        {
            erase_tk(token);
            logic_expression(token);

            next_tk(token, tk_id, tk_num, 1);
            if (tk_id == "symbol" && tk_num == "12")        //)
            {
                erase_tk(token);
                IF();
            }
            else
                cout << "select_condition_wrong1";
        }
        else
            cout << "select_condition_wrong2";
    }
    else if (tk_id == "key" && tk_num == "7")           //else
    {
        tk_num_1 = tk_num;
        erase_tk(token);
        EL();
        next_tk(token, tk_id, tk_num, 1);
        else_branch(token);
    }
    else
        cout << "select_condition_wrong3";
}

//<�߼����ʽ> -> <�������ʽ>{w4 <�������ʽ>}         //���ﲻ��ѭ�����ǿ��п��޵���˼����֧�ֶ�αȽ�
void logic_expression(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    ari_expression(token);
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "symbol" && (tk_num == "5" || tk_num == "6" || tk_num == "7" || tk_num == "8" || tk_num == "9" || tk_num == "10"))// < <= > >= != ==
    {
        string tk_num1;
        tk_num1 = tk_num;
        erase_tk(token);
        ari_expression(token);

        if (tk_num1 == "5")
            GEQ("<");
        else if (tk_num1 == "6")
            GEQ("<=");
        else if (tk_num1 == "7")
            GEQ(">");
        else if (tk_num1 == "8")
            GEQ(">=");
        else if (tk_num1 == "9")
            GEQ("!=");
        else
            GEQ("==");

    }
}

// <else��֧> -> if (<�߼����ʽ>) | ��
void else_branch(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);

    if (tk_id == "key" && tk_num == "6")            //if
    {

        erase_tk(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "11")             //(
        {
            erase_tk(token);
            logic_expression(token);
            next_tk(token, tk_id, tk_num, 1);
            if (tk_id == "symbol" && tk_num == "12")        //)
            {
                erase_tk(token);
            }
            else
                cout << "else_branch_wrong1";
        }
        else
            cout << "else_branch_wrong2";
    }
}

//<ѡ������> -> ; | <�������> | {<�������>}
void select_subject(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "symbol" && tk_num == "19")            //;
    {
        erase_tk(token);
    }
    else if ((tk_id == "iT" || (tk_id == "key" && (tk_num == "1" || tk_num == "2" || tk_num == "3"))) || (tk_id == "key" && (tk_num == "7" || tk_num == "8")) || (tk_id == "key" && tk_num == "9"))
    {
        erase_tk(token);
        com_sentence(token);
    }
    else if (tk_id == "symbol" && tk_num == "15")      //{
    {
        erase_tk(token);
        com_sentence(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "16")      //}
        {
            if (tk_num_1 != "6")
            {
                IE();
            }

            erase_tk(token);
        }
        else
        {
            cout << "elect_subject_wrong1";
        }
    }
    else
        cout << "elect_subject_wrong2";
}


//<ѭ�����> -> <ѭ������> <ѭ������>
void loop_sentence(string& token)
{
    void loop_condition(string & token);         //ѭ������
    void loop_subject(string & token);           //ѭ������
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    loop_condition(token);
    next_tk(token, tk_id, tk_num, 1);
    loop_subject(token);
}
//<ѭ������> -> while (<�߼����ʽ>)
void loop_condition(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "key" && tk_num == "8")            //while
    {
        WH();
        erase_tk(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "11")             //(
        {
            erase_tk(token);
            logic_expression(token);
            next_tk(token, tk_id, tk_num, 1);
            if (tk_id == "symbol" && tk_num == "12")             //)
            {
                DO();
                erase_tk(token);
            }
            else
                cout << "loop_condition_wrong1";
        }
        else
            cout << "loop_condition_wrong2";
    }
    else
        cout << "loop_condition_wrong3";
}

//<ѭ������> -> {{<�������>}}
void loop_subject(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "symbol" && tk_num == "15")      //{
    {
        erase_tk(token);
        next_tk(token, tk_id, tk_num, 1);
        while ((tk_id == "iT" || (tk_id == "key" && (tk_num == "1" || tk_num == "2" || tk_num == "3"))) || (tk_id == "key" && (tk_num == "6" || tk_num == "7")) || (tk_id == "key" && tk_num == "8"))
        {
            com_sentence(token);
            next_tk(token, tk_id, tk_num, 1);
        }
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "symbol" && tk_num == "16")      //}
        {
            WE();
            erase_tk(token);
        }
        else
        {
            cout << "loop_subject_worng1";

        }
    }
    else
        cout << "loop_subject_worng2";
}

//<����> ->return <����> | <��ʶ��>; 
void back(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "key" && tk_num == "15")        //return
    {
        erase_tk(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "CT" || tk_id == "iT")      //�������ʶ��
        {
            erase_tk(token);
            next_tk(token, tk_id, tk_num, 1);
            if (tk_id == "symbol" && tk_num == "19")     //;
            {
                erase_tk(token);
            }
            else
                cout << "back_wrong1";
        }
        else
            cout << "back_wrong2";
    }
    else
    {
        cout << "back_wrong3";
    }
}







#endif // !YUFA_H_INCLUDE
