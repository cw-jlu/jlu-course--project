#include<iostream>
#include "System.h"
#include "Useful_Tools.h"
using namespace std;
int main()
{
	SystemLXY system;
	while (true)
	{
		system.start();
		delaycoutline();
		cout << "继续登录......1" << endl
			 << "退出系统......0" << endl;
		delaycout("请选择");
		int judge = readIntOnly("");
		if (judge == 0)
		{
			break;
		}
		else if (judge == 1)
		{
			continue;
		}
		else
		{
			delaycout("输入不合法请重新输入");
		}
	}
	return 0;
}
