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

string tk_num_1;                //判断if条件语句的结束位置


void item(string& token);

void next_tk(string& token, string& tk_id, string& tk_num, int k)
{
    tk_id.clear();
    tk_num.clear();
    int i = 0, j;
    //i=1越过<
    if (token.size() == 0)
    {
        cout << "token已读完,语法正确" << endl;
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
        //当j=k时读第k个token
        for (; token[i] != ' '; i++)
        {
            tk_id.push_back(token[i]);
        }
        for (i++; token[i] != '>'; i++) tk_num.push_back(token[i]);
    }

}

void erase_tk(string& token)        //删除string中已经分析过的token
{
    int i;
    int size = token.size();
    if (size == 0);
    else {
        for (i = 0; token[i] != '>'; i++);
        token.erase(0, i + 1);
    }
}

//<程序>   <类型> main() <分程序>
void program(string& token)
{
    void type(string & token);   //类型
    void sub_program(string & token);    //分程序
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

//<类型>  int | float  | char
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


//<分程序>->复合语句' 返回 
void sub_program(string& token)
{
    void com_sentence1(string & token);       //复合语句' 
    void back(string & token);               //返回
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    com_sentence1(token);
    next_tk(token, tk_id, tk_num, 1);
    back(token);
}

//复合语句' -> {复合语句}|空
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


//<复合语句> -> <语句表> | <选择语句> | <循环语句> |空 
void com_sentence(string& token)
{
    void sentence_table(string & token);         //语句表
    void select_sentence(string & token);        //选择语句
    void loop_sentence(string & token);          //循环语句
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "symbol" && tk_num == "15")
    {
        erase_tk(token);
    }
    if (tk_id == "iT" || (tk_id == "key" && (tk_num == "1" || tk_num == "2" || tk_num == "3")))      //语句表
    {
        sentence_table(token);
    }
    else if (tk_id == "key" && (tk_num == "6" || tk_num == "7"))                        //选择语句
    {
        select_sentence(token);
    }
    else if (tk_id == "key" && tk_num == "8")                                   //循环语句
    {
        loop_sentence(token);
    }
}

//<语句表>  <赋值语句> ;<语句表> | <变量说明><语句表> | ω
void sentence_table(string& token)
{
    void assign_sentence(string & token);        //赋值语句
    void variable(string & token);               //变量说明
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
    else if (tk_id == "key" && (tk_num == "1" || tk_num == "2" || tk_num == "3"))         //变量说明
    {
        variable(token);
    }
}

//<赋值语句>  <标识符> = <算术表达式>
void assign_sentence(string& token)
{
    void id(string & token);         //标识符
    void ari_expression(string & token);     //算术表达式
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

//<标识符>
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

//算术表达式-> <项>{ω0<项>}|ω 

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

//<项>  ->   <因子>{w1<因子>}
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


//因子  -> <标识符>|<常量>|<(算术表达式)>
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


//<变量说明> -> <类型><标识符>{,<标识符>}; 
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


//<选择语句> -> <选择条件><选择主体>
void select_sentence(string& token)
{
    void select_condition(string & token);           //选择条件
    void select_subject(string & token);             //选择主体
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    select_condition(token);
    next_tk(token, tk_id, tk_num, 1);
    select_subject(token);
}


//<选择条件> -> if (<逻辑表达式>) |else <else分支>
void select_condition(string& token)
{
    void logic_expression(string & token);           //逻辑表达式
    void else_branch(string & token);                //else分支
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

//<逻辑表达式> -> <算术表达式>{w4 <算术表达式>}         //这里不是循环，是可有可无的意思，不支持多次比较
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

// <else分支> -> if (<逻辑表达式>) | ω
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

//<选择主体> -> ; | <复合语句> | {<复合语句>}
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


//<循环语句> -> <循环条件> <循环主体>
void loop_sentence(string& token)
{
    void loop_condition(string & token);         //循环条件
    void loop_subject(string & token);           //循环主体
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    loop_condition(token);
    next_tk(token, tk_id, tk_num, 1);
    loop_subject(token);
}
//<循环条件> -> while (<逻辑表达式>)
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

//<循环主体> -> {{<复合语句>}}
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

//<返回> ->return <常数> | <标识符>; 
void back(string& token)
{
    string tk_id, tk_num;
    next_tk(token, tk_id, tk_num, 1);
    if (tk_id == "key" && tk_num == "15")        //return
    {
        erase_tk(token);
        next_tk(token, tk_id, tk_num, 1);
        if (tk_id == "CT" || tk_id == "iT")      //常数或标识符
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
