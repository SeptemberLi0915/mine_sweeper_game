/* 2551382 李佳仪 卓08 */

/* 空文件，给出的目的是为了防止把文件名弄错 */
#include<iostream>
#include <conio.h>
#include <Windows.h>
#include"mine_sweeper.h"
#include"cmd_console_tools.h"
using namespace std;



/***************************************************************************
  函数名称：输入处理函数1
  功    能：选择难度，返回选择值
  输入参数：难度
  返 回 值：输入值
***************************************************************************/
int input_dif()
{
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）" ;
    char dif;
    while (1)
    {
        dif = _getch();
        int x = dif - '0';
        if (x >= 1 && x < 4)
        {
            cout << x << endl;
            return x;
        }
    }
}

class Timer {
private:
    LARGE_INTEGER tick, begin, end;
    bool is_paused;
    LARGE_INTEGER pause_time;
    double total_paused_time;

public:
    Timer() : is_paused(false), total_paused_time(0) {}
    void start()
    {
        QueryPerformanceFrequency(&tick);
        QueryPerformanceCounter(&begin);
        is_paused = false;
        total_paused_time = 0;
    }
    void pause()
    {
        if (!is_paused)
        {
            QueryPerformanceCounter(&pause_time);
            is_paused = true;
        }
    }
    void resume()
    {
        if (is_paused)
        {
            LARGE_INTEGER resume_time;
            QueryPerformanceCounter(&resume_time);
            total_paused_time += double(resume_time.QuadPart - pause_time.QuadPart) / tick.QuadPart;
            is_paused = false;
        }
    }
    void stop()
    {
        QueryPerformanceCounter(&end);
    }

    double getElapsedTime()
    {
        if (is_paused)
            return double(pause_time.QuadPart - begin.QuadPart) / tick.QuadPart - total_paused_time;
        else
        {
            LARGE_INTEGER current;
            QueryPerformanceCounter(&current);
            return double(current.QuadPart - begin.QuadPart) / tick.QuadPart - total_paused_time;
        }
    }
    void printElapsedTime()
    {
        cout << endl;
        cout << "用时: " << getElapsedTime() << "秒" << endl;
    }
    bool isPaused()
    {
        return is_paused;
    }
    bool isRunning()
    {
        return true;
    }
};


/***************************************************************************
  函数名称：输入处理函数2
  功    能：显示提示信息，处理坐标输入
  输入参数：坐标
  返 回 值：无
  说    明：用指针得到输入值
***************************************************************************/
void sub_input(int dif, int& row, int& col, char first_char = '\0')
{
    char r, c;
    if (first_char == '\0')
    {
        r = _getch();  // 如果没有传入第一个字符，就获取
    }
    else
        r = first_char;  // 使用传入的第一个字符
    if (r >= 'A' && r <= 'I')
        cout << r;
    else if (r > 'I' && r <= 'P')
    {
        if (dif == 2 || dif == 3)
            cout << r;
    }
    else
    {
        while (1)
        {
            r = _getch();
            if (r >= 'A' && r <= 'I')
            {
                cout << r;
                break;
            }
            else if (r > 'I' && r <= 'P')
            {
                if (dif == 2 || dif == 3)
                {
                    cout << r;
                    break;
                }
            }
        }
    }
    while (1)
    {
        c = _getch();
        row = r - 'A' + 1;
        if (c >= '1' && c <= '9')
        {
            cout << c << endl;
            col = c - '0';
            break;
        }
        else if (c >= 'a' && c <= 'u')
        {
            if (dif == 2)
            {
                if (c >= 'a' && c <= 'g')
                {
                    cout << c << endl;
                    col = c - 'a' + 1 + 9;
                    break;
                }
                else
                    continue;   
            }
            else if (dif == 3)
            {
                if (c >= 'a' && c <= 'u')
                {
                    cout << c << endl;
                    col = c - 'a' + 1 + 9;
                    break;
                }
                else
                    continue;   
            }
        }
    }
}

void input_open(int dif, int& row, int& col,int &x,bool able_to_flag)
{
    x = -1;
    cout << "输入横纵坐标（如Gf,A1，按q退出";
    if (able_to_flag)
        cout << ",&显示时间，@A3为标记A3为雷，#A3为取消A3标记";
    cout << "）：";
    while (1)
    {
        char t = _getch();
        if (t == 'q')
        {
            x = -2;
            cout << t << endl;
            return;
        }
        if (able_to_flag)
        {
            if (t == '@' || t == '#' || t == '&')
            {
                cout << t;

                if (t == '@')
                {
                    x = 1;  
                    sub_input(dif, row, col);
                }
                else if (t == '#')
                {
                    x = 0;  
                    sub_input(dif, row, col);
                }
                else if (t == '&')
                {
                    x = 2; 
                }
                return;
            }
        }
        if ((t >= 'A' && t <= 'Z'))
        {
            sub_input(dif, row, col, t);  
            return;
        }
    }
}
/***************************************************************************
  函数名称：难度设置
  功    能：设置棋盘大小
  输入参数：难度选择
***************************************************************************/
void set_dif(MineSweeperGame& game, int dif) 
{
    switch (dif)
    {
    case 1:
        game.rows = 9;
        game.cols = 9;
        game.mines = 10;
        break;
    case 2:
        game.rows = 16;
        game.cols = 16;
        game.mines = 40;
        break;
    case 3:
        game.rows = 16;
        game.cols = 30;
        game.mines = 100;
        break;
    }
}

/***************************************************************************
  函数名称：初始化雷函数
  功    能：初始化，把所有都标记为0
***************************************************************************/
void zero_init(MineSweeperGame& game)
{
    for (int r = 0; r < MAX_ROWS; r++)
    {
        for (int c = 0; c < MAX_COLUMS; c++) 
        {
            game.board[r][c].mine = 0;
            game.board[r][c].open = 0;
            game.board[r][c].flag = 0;
            game.board[r][c].around = 0;
        }
    }
    game.flag_marked = 0;
}

/***************************************************************************
  函数名称：基础的雷生成函数
  功    能：随机布雷
  输入参数：相应难度有的行列
  说    明：安全区就等同于默认已经有雷了 但是这样会影响sum 所以换个思路
            mode==1是有安全区的情况，对应子任务2之后，默认mode==0
***************************************************************************/
void place_mines(MineSweeperGame& game,int r_input,int c_input,bool mode) 
{
    srand((unsigned int)time(0));

    int sum = 0;
    while (sum < game.mines) 
    {
        int r = (rand() % game.rows) + 1; 
        int c = (rand() % game.cols) + 1;  
        if (mode == 1)
        {
            int dr = r - r_input;
            int dc = c - c_input;
            if (dr >= -1 && dr <= 1 && dc >= -1 && dc <= 1)
                continue;
        }
        if (!game.board[r][c].mine)
        {
            game.board[r][c].mine = 1;
            sum++;
        }
    }
}

/***************************************************************************
  函数名称：判断游戏结束函数
  功    能：通过数是否找到了所有非雷格子判断游戏是否结束
  输入参数：结构体
  返 回 值：bool值判断是否结束
***************************************************************************/
bool findallmines(MineSweeperGame&game)
{
    bool win = 0;
    int openall = game.rows * game.cols - game.mines;
    int opensum = 0;
    for (int i = 1; i <= game.rows; i++)
    {
        for (int j = 1; j <= game.cols; j++)
        {
            if (!game.board[i][j].mine && game.board[i][j].open)
                opensum++;
        }
    }
    if (openall == opensum)
        win = 1;
    return win; 
}

/***************************************************************************
  函数名称：周围雷计算函数
  功    能：计算周围雷数量
  输入参数：结构体
***************************************************************************/
void calculate_around_numbers(MineSweeperGame& game)
{
    for (int i = 1; i <= game.rows; ++i) 
    {
        for (int j = 1; j <= game.cols; ++j) 
        {
            if (game.board[i][j].mine)
                continue;
            int around_sum = 0;
            for (int x1 = -1; x1 <= 1; x1++)
            {
                for (int y1 = 1; y1 >= -1; y1--) 
                { 
                    if (x1 == 0 && y1 == 0)
                        continue;
                    int x0 = i + x1;
                    int y0 = j + y1;
                    if (game.board[x0][y0].mine)
                        around_sum++;
                }
            }
            game.board[i][j].around =around_sum;
        }
    }
}

/***************************************************************************
  函数名称：递归函数
  功    能：通过递归作初始展开
  输入参数：结构体、输入的坐标
  说    明：递归周围8个 遇到雷、或者已经打开的或者边界就停止 只打开一层 所以
            只有在自己为0的时候才递归
***************************************************************************/
void open_not_mine(MineSweeperGame& game, int r, int c)
{
    if (r<1 || c<1 || r>game.rows || c>game.cols)
        return;
    else if (game.board[r][c].open || game.board[r][c].mine)
        return;
    game.board[r][c].open = 1;
    if (game.board[r][c].around == 0)
    {
        open_not_mine(game, r - 1, c - 1);
        open_not_mine(game, r - 1, c);
        open_not_mine(game, r - 1, c + 1);
        open_not_mine(game, r, c - 1);
        open_not_mine(game, r, c + 1);
        open_not_mine(game, r + 1, c - 1);
        open_not_mine(game, r + 1, c);
        open_not_mine(game, r + 1, c + 1);
    }
}

/***************************************************************************
  函数名称：反显函数
  功    能：在打开的时候或者标记的时候反显
  输入参数：格子结构体，是否标记和打开
            demo模版：标记则无法打开（不管是不是雷）
            打开则无法标记
***************************************************************************/
void highlight(const Cell& cell, bool open=0,int flag=0,bool is_mine=0)
{
    if (open)
    {
        cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
        if (cell.around == 0)
        {
            cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
            cout << "0";
            cct_setcolor();
            cout << " ";
        }
        else
        {
            cct_setcolor(COLOR_HYELLOW, cell.around);
            cout << cell.around;
            cct_setcolor();
            cout << " ";
        }
    }
    else if (flag == 1)
    {
        cct_setcolor(COLOR_RED, COLOR_BLACK);
        cout << "X";
        cct_setcolor();
        cout << " ";
    }
    else
        cout << "X ";
    cct_setcolor();
}

void print_board(const MineSweeperGame& game,int mode) 
{
    int row_no = 65 + game.rows;
    if (game.cols == 9)
    {
        cout << "  |";
        for (int i = 1; i <= 9; i++)
            cout << i << " ";
        cout << endl;
        cout << "--+";
        for (int i = 0; i < 20; i++)
            cout << "-";
        cout << endl;
    }
    else
    {
        cout << "  |";
        for (int i = 1; i <= 9; i++)
            cout << i << " ";
        int col_no = 97 + game.cols - 9;
        for (int j = 97; j < col_no; j++)
            cout << char(j) << " ";
        cout << endl;
        cout << "--+";
        for (int i = 0; i <2*game.cols+3; i++)
            cout << "-";
        cout << endl;
    }
    for (int i = 1; i <= game.rows; i++)
    {
        cout << (char)('A' + i - 1) << " |";
        if (mode == 1)
        {
            for (int j = 1; j <= game.cols; j++)
            {
                if (game.board[i][j].mine)
                    cout << "* ";  // 地雷
                else
                    cout << game.board[i][j].around << " ";
            }
            cout << endl;
        }
        else if (mode==2)
        {
            for (int j = 1; j <= game.cols; j++)
                cout << "X ";
            cout << endl;
        }
        else if (mode==3)
        {
            for (int j = 1; j <= game.cols; j++)
            {
                highlight(game.board[i][j], game.board[i][j].open, game.board[i][j].flag, game.board[i][j].mine);
            }
            cout << endl;
        }
    }
    cout << endl;
}

void print_end_board(const MineSweeperGame& game,int &x,int&y )
{
    int row_no = 65 + game.rows;
    if (game.cols == 9)
    {
        cout << "  |";
        for (int i = 1; i <= 9; i++)
            cout << i << " ";
        cout << endl;
        cout << "--+";
        for (int i = 0; i < 20; i++)
            cout << "-";
        cout << endl;
    }
    else
    {
        cout << "  |";
        for (int i = 1; i <= 9; i++)
            cout << i << " ";
        int col_no = 97 + game.cols - 9;
        for (int j = 97; j < col_no; j++)
            cout << char(j) << " ";
        cout << endl;
        cout << "--+";
        for (int i = 0; i < 2 * game.cols + 3; i++)
            cout << "-";
        cout << endl;
    }
    for (int i = 1; i <= game.rows; i++)
    {
        cout << (char)('A' + i - 1) << " |";
        for (int j = 1; j <= game.cols; j++)
        {
            if (game.board[i][j].flag == 1)
            {
                cct_setcolor(COLOR_RED, COLOR_BLACK);
                cout << "X";
                cct_setcolor();
                cout << " ";
            }
            else if (game.board[i][j].open == 0)
                cout << "X ";
            else if (game.board[i][j].open != 0 && game.board[i][j].mine == 0)
            {
                 cct_setcolor(COLOR_HYELLOW, game.board[i][j].around);
                 cout << game.board[i][j].around;
                 cct_setcolor();
                 cout<< " ";
            }
            else
                cout << "* ";
        }
        cout << endl;
    }
    cct_setcolor();
}

void base_inner()
{
    MineSweeperGame game;
    cct_cls();
    set_dif(game, input_dif());
    zero_init(game);
    place_mines(game);
    calculate_around_numbers(game);
    cout << "内部数组：" << endl;
    print_board(game,1);
}

void open_init()
{
    MineSweeperGame game;
    cct_cls();
    int dif = input_dif();
    set_dif(game, dif);
    
    cout << "内部数组：" << endl;
    print_board(game, 2);
    int row = 0, col = 0;
    int x = -1;
    input_open(dif, row, col,x,0);
    zero_init(game);
    place_mines(game, row, col, 1);
    calculate_around_numbers(game);
    open_not_mine(game, row, col);
    cout << "点开后的数组：" << endl;
    print_board(game, 3);
}

void open_game()
{
    MineSweeperGame game;
    cct_cls();
    int dif = input_dif();
    set_dif(game, dif);
    
    cout << "内部数组：" << endl;
    print_board(game, 2);
    int row1 = 0, col1 = 0;
    int x = -1;
    input_open(dif, row1, col1, x, 0);
    if (x == -2)
        return;
    else
    {
        zero_init(game);
        place_mines(game, row1, col1, 1);
        calculate_around_numbers(game);
        open_not_mine(game, row1, col1);
        while (1)
        {
            cout << "当前数组：" << endl;
            print_board(game, 3);
            int r = 0, c = 0;
            int x = -1;
            input_open(dif, r, c, x, 0);
            if (x == -2)
                return;
            else
            {
                if (game.board[r][c].mine == 1)
                {
                    game.board[r][c].open = 1;
                    print_end_board(game, r, c);
                    cout << "你输了，游戏结束" << endl;
                    break;
                }
                else if (game.board[r][c].around == 0)
                    open_not_mine(game, r, c);
                else
                    game.board[r][c].open = 1;
                if (findallmines(game))
                {
                    print_board(game, 3);
                    cout << "恭喜胜利，游戏结束" << endl;
                    break;
                }
            }
        }
    }
}

void open_game_able_to_flag()
{
    MineSweeperGame game;
    cct_cls();
    int dif = input_dif();
    set_dif(game, dif);
    Timer game_timer;
    game_timer.start();
    
    cout << "内部数组：" << endl;
    print_board(game, 2);
    int row = 0, col = 0;
    int x = -1;
    while (true)
    {
        input_open(dif, row, col, x, 1);
        if (x == -2)
            return;
        else if (x == 2)
        {
            game_timer.pause();
            game_timer.printElapsedTime();
            game_timer.resume();
            continue;
        }
        else if (x == 0 || x == 1)
        {
            cout << "第一次禁止标记：）" << endl;
            continue;
        }
        else
            break;
    }
    zero_init(game);
    place_mines(game, row, col, 1);
    calculate_around_numbers(game);
    open_not_mine(game, row, col);
    while (true)
    {
        cout << "当前数组：" << endl;
        print_board(game, 3);
        int r = 0, c = 0;
        int x = -1;
        input_open(dif, r, c, x, 1);
        if (x == -2)
            return;
        else if (x == 2)
        {
            game_timer.pause();
            game_timer.printElapsedTime();
            game_timer.resume();
            continue;
        }
        else if (x == 1)
        {
            if (!game.board[r][c].open && !game.board[r][c].flag)
                game.board[r][c].flag = 1;
            else if (game.board[r][c].open)
                cout << "已打开的格子不能标记！" << endl;
            continue;
        }
        else if (x == 0)
        {
            if (game.board[r][c].flag)
                game.board[r][c].flag = 0;
;
            continue;    
        }
        if (game.board[r][c].mine)
        {
            game.board[r][c].open = 1;
            print_end_board(game, r, c);
            cout << "你输了，游戏结束" << endl;
            game_timer.stop();
            game_timer.printElapsedTime();
            return;
        }
        else if (game.board[r][c].around == 0)
            open_not_mine(game, r, c);
        else
            game.board[r][c].open = 1;
        if (findallmines(game))
        {
            print_board(game, 3);
            cout << "恭喜胜利! 游戏结束" << endl;
            game_timer.stop();
            game_timer.printElapsedTime();
            return;
        }
    }
}



