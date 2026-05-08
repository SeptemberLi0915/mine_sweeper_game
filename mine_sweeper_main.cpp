/* 2551382 李佳仪 卓08 */

/* 空文件，给出的目的是为了防止把文件名弄错 */
#include<iostream>
#include<conio.h>
#include"cmd_console_tools.h"
#include"mine_sweeper.h"
using namespace std;
int main()
{

	/* 这是一段用于验证cmd_console_tools.cpp版本是否正确的代码，判断正确的具体标准在作业文档中 */
	cct_showstr(10, 2, "请输出雪花的大小", COLOR_BLACK, COLOR_WHITE, 2);
	cout << endl << endl;
	cct_showstr(10, 4, "╔═══汉诺塔═══╗", COLOR_BLACK, COLOR_WHITE, 1);
	cct_showstr(10, 5, "╔═══汉诺塔 ═══╗", COLOR_WHITE, COLOR_BLACK, 1);
	cct_showstr(10, 6, "╔═══H汉诺塔 ═══╗", COLOR_RED, COLOR_HYELLOW, 1);

	cct_showstr(10, 8,  "**╔═╦═╗中", COLOR_CYAN, COLOR_YELLOW, 1);
	cct_showstr(10, 9,  "中║测║试║**", COLOR_HBLUE, COLOR_HPINK, 1);
	cct_showstr(10, 10, "**╠═╬═╣**", COLOR_YELLOW, COLOR_HGREEN, 1);
	cct_showstr(10, 11, "中║ab║12║中", COLOR_HPINK, COLOR_HCYAN, 1);
	cct_showstr(10, 12, "**╚═╩═╝中", COLOR_GREEN, COLOR_HBLUE, 1);

    /* 本函数位于 mine_sweeper_tools.cpp 中 */
	to_be_continued("请确认上面的输出没有乱码/字符相互重叠现象，如果有，说明cmd_console_tools.cpp不对");

    //给出后续的正常内容
	while (1)
	{
		cct_cls();
		cct_setconsoleborder(100,30, 100, 30);
		int x = mine_menu();
		int cols, lines, buffer_cols, buffer_lines;

		cout << endl;
		/* 从这里继续你的程序 */
		if (x == 1)
		{
			base_inner();
			to_be_continued("", 0, 23);
		}
		else if (x == 2)
		{
			open_init();
			to_be_continued("", 0, 41);
		}
		else if (x == 3)
		{
			open_game();
			cout << "按回车键继续..." << endl;
			while (_getch() != '\r');
			continue;
		}
		else if (x == 4)
		{
			open_game_able_to_flag();
			cout << "按回车键继续..." << endl;
			while (_getch() != '\r');
			continue;
		}
		else if (x == 5)
		{
			draw_graph();
			cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
			cct_gotoxy(0, lines - 1);
			cout << "按回车键继续..." << endl;
			while (_getch() != '\r');
			continue;
		}
		else if (x == 6)
		{
			read_mouse();
			cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
			cct_gotoxy(0, lines - 1);
			cout << "按回车键继续..." << endl;
			while (_getch() != '\r');
			continue;
		}
		else if (x == 7)
		{
			open_mine_graph();
			cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
			cct_gotoxy(0, lines - 1);
			cout << "按回车键继续..." << endl;
			while (_getch() != '\r');
			continue;
		}
		else if (x == 8)
		{
			basic_game_graph();
			cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
			cct_gotoxy(0, lines - 1);
			cout << "按回车键继续..." << endl;
			while (_getch() != '\r');
			continue;

		}
		else if (x == 9)
		{
			game_graph();
			cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
			cct_gotoxy(0, lines-1);
			cout << "按回车键继续..." << endl;
			while (_getch() != '\r');
			continue;
		}
		else if (x == 0)
			break;
	}
    return 0;
}