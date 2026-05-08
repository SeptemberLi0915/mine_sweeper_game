/* 2551382 李佳仪 卓08 */

/* 空文件，给出的目的是为了防止把文件名弄错 */
#include<iostream>
#include <conio.h>
using namespace std;

int mine_menu()
{
	cout << "--------------------------------------------" << endl;
	cout << "1.选择模式，显示内部数组" << endl;
	cout << "2.输入一个位置，显示打开区域" << endl;
	cout << "3.内部数组基础版" << endl;
	cout << "4.内部数组完整版（标记、运行时间）" << endl;
	cout << "5.画出框架，显示内部数据" << endl;
	cout << "6.检测鼠标位置和合法性，以及左键点击" << endl;
	cout << "7.鼠标点击一次，显示打开区域" << endl;
	cout << "8.允许连续游戏，支持右键标记，判断游戏结束" << endl;
	cout << "9.完整游戏，标明雷数，空格、结束显示时间" << endl;
	cout << "0.退出游戏" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择]: ";
	char choice;
	while (1)
	{
		choice = _getch();
		int x = choice - '0';
		if (x >= 0 && x < 10)
		{
			cout << x << endl;
			cout << endl;
			return x;
		}
	}
}
