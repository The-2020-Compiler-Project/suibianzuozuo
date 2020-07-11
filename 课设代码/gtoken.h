#pragma once

#ifndef GTOKEN_H
#define GTOKEN_H




#include<fstream>
#include"stable.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define KEY 10
#define MUTP 7
#include<iomanip>
//using namespace std;
/**全局变量全部复制**/
struct gwordinfo
{
    char word[30];///程序里单词本身
    char wordtype;///单词类型，i为标识符，p为界符，c为常数，k为关键字
};

//gwordinfo->wordtype=4:i,p,c,k;
int gmemory = 4, l = 0;
int gpword, gm, gtest;
char gpw, gkword[KEY][7] = { "int","float","char","main","return","if","else","while","for","do" };
struct tnode itnode;//先创建一些固定内容
struct tnode rtnode;
struct tnode ctnode;
/**函数全部复制，只调用这一个：gToken();**/
void fillstable();
void gtestable();
void stable()
{
    itnode.tval = 'i';
    itnode.tpoint = NULL;
    itnode.next = &rtnode;

    rtnode.tval = 'r';
    rtnode.tpoint = NULL;
    rtnode.next = &ctnode;

    ctnode.tval = 'c';
    ctnode.tpoint = NULL;
    ctnode.next = NULL;

    thead->next = &itnode;//对已有类型表的固定内容连接
    tnode* ttail = &ctnode;//对已有类型表的固定内容连接
}
int gToken(string name)
{
    stable();
    gpword = 0;
    int ii;
    char gcy[100];
    for (ii = 0; name[ii] != '\0'; ii++)
        gcy[ii] = name[ii];
    gcy[ii] = '\0';
    FILE* fp;
    snode* p, * q = shead;
    //ifstream fp;
    //fp.open(name,ios::in);
    if (!(fp = fopen(gcy, "r")))
    {
        cout << "can not open the file" << endl;
        return 1;
    }
    char a = '1', b = '1', id[3] = { 'i','c','k' }, gpword2[MUTP][30] = { "&&","||","==",">=","<=","++","--" };
    int i = 0, j = 0, k = 0, n = 0;//k为0，界符直接送出
    struct gwordinfo* thisword[50];

    for (gtest = 0; a != EOF; gtest++)
    {
        thisword[gtest] = (struct gwordinfo*)malloc(sizeof(struct gwordinfo));
        if (gpword)
        {
            if (gpword == 1)
            {
                thisword[gtest]->word[0] = gpw;
                thisword[gtest]->word[1] = '\0';
                thisword[gtest]->wordtype = 'p';
                p = new snode;
                p->name = thisword[gtest]->word;
                stail->next = p;
                stail = p;
                gpword = 0;
            }
            else
            {
                strcpy(thisword[gtest]->word, gpword2[l]);
                thisword[gtest]->wordtype = 'p';
                p = new snode;
                p->name = thisword[gtest]->word;
                stail->next = p;
                stail = p;
                gpword = 0;
            }
        }
        else
        {

            a = fgetc(fp);
            while (a == ' ' || a == '\n' || a == '\r' || a == '\t')
                a = fgetc(fp);
            if (a == EOF) { cout << endl; fillstable(); fclose(fp); return 0; }
            while (a != ' ' && a != '\n' && a != '\r' && a != '\t' && a != EOF)
            {
                if (!k && (a == '{' || a == '}' || a == ';' || a == ',' || a == '=' || a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')' || a == '!' || a == '&' || a == '|' || a == '>' || a == '<'))
                {
                    if (a == '&' || a == '|' || a == '=' || a == '>' || a == '<')
                    {
                        n = 1;
                        if (a == '&')
                        {
                            a = getc(fp);
                            if (a != '&')
                            {
                                cout << "词法错误3！";
                                gpword = 0;//还原外层变量
                                stail = shead;//删去已填的符号表
                                return 0;
                            }
                            strcpy(thisword[gtest]->word, gpword2[0]);
                            thisword[gtest]->wordtype = 'p';
                            p = new snode;
                            p->name = thisword[gtest]->word;
                            stail->next = p;
                            stail = p;
                        }
                        else if (a == '|')
                        {
                            a = getc(fp);
                            if (a != '|')
                            {
                                cout << "词法错误3！";
                                gpword = 0;//还原外层变量
                                stail = shead;//删去已填的符号表
                                return 0;
                            }
                            strcpy(thisword[gtest]->word, gpword2[1]);
                            thisword[gtest]->wordtype = 'p';
                            p = new snode;
                            p->name = thisword[gtest]->word;
                            stail->next = p;
                            stail = p;
                        }
                        else if (a == '+')
                        {
                            b = getc(fp);
                            if (b != '+')
                            {
                                fseek(fp, -1, 1);
                                n = 0;
                            }
                            else
                            {
                                strcpy(thisword[gtest]->word, gpword2[5]);
                                thisword[gtest]->wordtype = 'p';
                                p = new snode;
                                p->name = thisword[gtest]->word;
                                stail->next = p;
                                stail = p;
                            }
                        }
                        else if (a == '-')
                        {
                            b = getc(fp);
                            if (b != '-')
                            {
                                fseek(fp, -1, 1);
                                n = 0;
                            }
                            else
                            {
                                strcpy(thisword[gtest]->word, gpword2[6]);
                                thisword[gtest]->wordtype = 'p';
                                p = new snode;
                                p->name = thisword[gtest]->word;
                                stail->next = p;
                                stail = p;
                            }
                        }
                        else
                        {
                            b = getc(fp);
                            if (b != '=')
                            {
                                fseek(fp, -1, 1);
                                n = 0;
                            }
                            else
                            {
                                if (a == '=')strcpy(thisword[gtest]->word, gpword2[2]);
                                if (a == '>')strcpy(thisword[gtest]->word, gpword2[3]);
                                if (a == '<')strcpy(thisword[gtest]->word, gpword2[4]);
                                thisword[gtest]->wordtype = 'p';
                                p = new snode;
                                p->name = thisword[gtest]->word;
                                stail->next = p;
                                stail = p;
                            }
                        }
                    }
                    if (!n)
                    {
                        thisword[gtest]->word[0] = a;
                        thisword[gtest]->word[1] = '\0';
                        thisword[gtest]->wordtype = 'p';
                        p = new snode;
                        p->name = thisword[gtest]->word;
                        stail->next = p;
                        stail = p;
                    }
                    n = 0;
                    break;
                }
                else if (k && (a == '{' || a == '}' || a == ';' || a == ',' || a == '=' || a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')' || a == '!' || a == '&' || a == '|' || a == '>' || a == '<'))
                {
                    if (a == '&' || a == '|' || a == '=' || a == '>' || a == '<')
                    {
                        n = 1;
                        if (a == '&')
                        {
                            a = getc(fp);
                            if (a != '&')
                            {
                                cout << "词法错误3！";
                                gpword = 0;//还原外层变量
                                stail = shead;//删去已填的符号表
                                return 0;
                            }
                            l = 0;
                            gpword = 2;
                        }
                        else if (a == '|')
                        {
                            a = getc(fp);
                            if (a != '|')
                            {
                                cout << "词法错误3！";
                                gpword = 0;//还原外层变量
                                stail = shead;//删去已填的符号表
                                return 0;
                            }
                            l = 1;
                            gpword = 2;
                        }
                        else if (a == '+')
                        {
                            b = getc(fp);
                            if (b != '+')
                            {
                                fseek(fp, -1, 1);
                                n = 0;
                            }
                            else
                            {
                                l = 5;
                                gpword = 2;
                            }
                        }
                        else if (a == '-')
                        {
                            b = getc(fp);
                            if (b != '-')
                            {
                                fseek(fp, -1, 1);
                                n = 0;
                            }
                            else
                            {
                                l = 6;
                                gpword = 2;
                            }
                        }
                        else
                        {
                            b = getc(fp);
                            if (b != '=')
                            {
                                fseek(fp, -1, 1);
                                n = 0;
                            }
                            else
                            {
                                if (a == '=')l = 2;
                                if (a == '>')l = 3;
                                if (a == '<')l = 4;
                                gpword = 2;
                            }
                        }
                    }
                    if (!n)
                    {
                        gpw = a;
                        gpword = 1;
                    }
                    n = 0;
                    thisword[gtest]->word[i] = '\0';

                    for (gm = 0; gm < KEY; gm++)
                        if (strcmp(thisword[gtest]->word, gkword[gm]) == 0)
                        {
                            j = 2;
                            break;
                        }

                    thisword[gtest]->wordtype = id[j];
                    if (!j)
                    {

                        while (q->next != NULL)
                        {

                            q = q->next;
                            if (q->name == thisword[gtest]->word)
                            {

                                j = 3;
                                break;
                            }
                        }
                        q = shead;
                    }
                    if (j == 3) break;
                    p = new snode;
                    p->name = thisword[gtest]->word;
                    stail->next = p;
                    stail = p;
                    break;
                }
                else if (j || (!i && (a <= '9' && a >= '0')))
                {
                    if (a < '0' || a>'9')
                    {
                        printf("词法错误2！");
                        gpword = 0;//还原外层变量
                        stail = shead;//删去已填的符号表
                        return 0;
                    }
                    thisword[gtest]->word[i] = a;
                    j = 1;//表明为常数
                    k = 1;//界符放入外层变量
                    i++;
                }
                else if ((a >= '0' && a <= '9') || (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
                {
                    thisword[gtest]->word[i] = a;
                    k = 1;
                    i++;
                }

                else
                {
                    printf("词法错误1！");
                    gpword = 0;
                    stail = shead;
                    return 0;
                }
                a = fgetc(fp);
            }
            if (a == ' ' || a == '\n' || a == '\r' || a == '\t')
            {
                thisword[gtest]->word[i] == '\0';
                for (gm = 0; gm < KEY; gm++)
                {
                    if (strcmp(thisword[gtest]->word, gkword[gm]) == 0)
                    {
                        j = 2;
                        break;
                    }
                }
                thisword[gtest]->wordtype = id[j];
                if (!j)
                {

                    while (q->next != NULL)
                    {

                        q = q->next;
                        if (q->name == thisword[gtest]->word)
                        {

                            j = 3;
                            break;
                        }
                    }
                    q = shead;
                }
                if (j != 3)
                {
                    p = new snode;
                    p->name = thisword[gtest]->word;
                    stail->next = p;
                    stail = p;
                }
            }
        }
        i = 0;
        j = 0;
        k = 0;
        cout << "<" << thisword[gtest]->word << "," << thisword[gtest]->wordtype << ">  ";
    }

    fclose(fp);
    cout << endl;
    fillstable();
    return 0;
}
void fillstable()
{
    cout << " _________ _________ _________ _________" << endl;
    cout << "|   NAME  |   TYPE  |   CAT   |   ADDR  |" << endl;
    cout << "|_________|_________|_________|_________|" << endl;
    int j = 0;
    snode* p = shead;
    snode* q = shead, * q1 = shead;
    while (p->next != NULL)
    {
        //snode* p1=p;//这便于从当前指针获取某些信息后，修改前一指针的信息
        p = p->next;

        if (p->name == "{" || p->name == "}" || p->name == ";" || p->name == "+" || p->name == "-" || p->name == "*" || p->name == "/" || p->name == "<" || p->name == ">" || p->name == "==" || p->name == ">=" || p->name == "<=" || p->name == "&&" || p->name == "||" || p->name == "!" || p->name == "," || p->name == "(" || p->name == ")" || p->name == "++" || p->name == "--" || p->name == "=")
        {
            p->cat = "p";
            //cout<<"p ";
            cout << setiosflags(ios_base::left) << setw(11) << p->name;
            printf("    NULL   ");
            cout << setiosflags(ios_base::left) << setw(11) << p->cat;
            printf("NULL  ");
            cout << endl;
            p->typel = NULL;
            p->addr = -1;
        }
        else if (p->name.at(0) < '0' || p->name.at(0) > '9')
        {
            for (gm = 0; gm < 3; gm++)
            {
                if (p->name == gkword[gm])
                {
                    j = 1;
                    break;
                }
            }
            if (j)
            {
                p->cat = "k";
                //cout<<"k ";
                cout << setiosflags(ios_base::left) << setw(11) << p->name;
                printf("    NULL   ");
                cout << setiosflags(ios_base::left) << setw(11) << p->cat;
                printf("NULL  ");
                cout << endl;
                p->typel = NULL;
                p->addr = -1;
                q1 = q;
                q = p;
            }
            for (gm = 3; gm < KEY; gm++)
            {
                if (p->name == gkword[gm])
                {
                    j = 2;
                    break;
                }
            }
            if (j == 2)
            {
                p->cat = "k";
                //cout<<"k ";
                p->typel = NULL;
                p->addr = -1;
                cout << setiosflags(ios_base::left) << setw(11) << p->name;
                printf("    NULL   ");
                cout << setiosflags(ios_base::left) << setw(11) << p->cat;
                printf("NULL  ");
                cout << endl;
                if (p->name == "main")
                    q = q1;
            }
            if (!j)
            {
                if (q == shead)///如果是没有给出类型的标识符
                {
                    p->cat = "v";///错误类型
                    //cout<<"x ";
                    p->typel = NULL;
                    cout << setiosflags(ios_base::left) << setw(11) << p->name;
                    printf("    NULL   ");
                    cout << setiosflags(ios_base::left) << setw(11) << p->cat;
                    printf("NULL  ");
                    cout << endl;
                    p->addr = -1;
                }
                else
                {
                    p->cat = "v";
                    if (q->name == "int")
                    {
                        p->typel = &itnode;
                        p->addr = gmemory;
                        gmemory += 4;
                        cout << setiosflags(ios_base::left) << setw(11) << p->name;
                        printf("  &itnode  ");
                        cout << setiosflags(ios_base::left) << setw(11) << p->cat;
                        cout << setiosflags(ios_base::left) << setw(11) << p->addr;
                        cout << endl;
                    }
                    if (q->name == "char")
                    {
                        p->typel = &ctnode;
                        p->addr = gmemory;
                        gmemory += 1;
                        cout << setiosflags(ios_base::left) << setw(11) << p->name;
                        printf("   &ctnode  ");
                        cout << setiosflags(ios_base::left) << setw(11) << p->cat;
                        cout << setiosflags(ios_base::left) << setw(11) << p->addr;
                        cout << endl;
                    }
                    if (q->name == "float")
                    {
                        p->typel = &rtnode;
                        p->addr = gmemory;
                        gmemory += 8;
                        cout << setw(10) << p->name;
                        printf("   &rtnode  ");
                        cout << setiosflags(ios_base::left) << setw(11) << p->cat;
                        cout << setiosflags(ios_base::left) << setw(11) << p->addr;
                        cout << setiosflags(ios_base::left) << endl;
                    }
                }
            }
        }
        j = 0;
    }
    return;
}

#endif // !1