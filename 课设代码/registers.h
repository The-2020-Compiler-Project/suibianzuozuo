#pragma once
#ifndef REGISTERS_H_INCLUDED
#define REGISTERS_H_INCLUDED

#include <iostream>
#include <vector>
#include "registers.h"

using namespace std;
struct registers
{
    string	name;
    vector<string> Rvalue;

    registers(string n) { name = n; }
    void clearPush(string n)
    {
        Rvalue.clear();
        Rvalue.push_back(n);
    }

};
registers regR("R");

bool inReg(string n)
{
    bool flag = false;
    for (int i = 0; i < regR.Rvalue.size(); i++)
    {
        if (regR.Rvalue[i] == n)
            flag = true;
    }
    return flag;
}




#endif // REGISTERS_H_INCLUDED#pragma once
