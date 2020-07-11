#include "semantic_analysis.h"
#include "quaternion.h"
#include "code.h"
#include "cifa.h"
#include "yufa.h"
#include <iostream>
#include<stack>	
#include <vector>
#include <sstream>
#include<iomanip>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



//int main()     //目标代码生成
//{
//	change();
//	codeTable ct;
//	ct.printcodes();
//}

//
//int main()				//词法分析调试
//{
//
//
//	init_();
//	string m;
//	string token;
//	m = read_file(m);
//	scanner(m, token);              //string类型的token存放token
//	cout << token;
//	return 0;
//}



int main()
{
    init_();
    string s, token;         //token存放整个token序列
    string tk_id, tk_num;    //token的类型和在数组中的位置
    s = read_file(s);
    scanner(s, token);       //扫描目标文件，查填表并把token序列送入token  string
    cout << "token: " << token << endl << endl << endl;
    program(token);
    erase_tk(token);
    next_tk(token, tk_id, tk_num, 1);
    print_quaternion();
    change();
	codeTable ct;
	ct.printcodes();
}



//int main()
//{
//	cout << QT_number << endl;
//	for (int i = 0; i < QT_number; i++)	//转换成目标代码需要的结构
//	{
//		quaNode q1;
//		q1 = QT[i];
//		cout << "(" << q1.ope << " , " << q1.ele1 << " , " << q1.ele2 << " , " << q1.res << ")" << endl;
//	}
//}



