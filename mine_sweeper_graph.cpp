/* 2551382 李佳仪 卓08 */

/* 空文件，给出的目的是为了防止把文件名弄错 */
#include<iostream>
#include"cmd_console_tools.h"
#include"mine_sweeper.h"
#include<conio.h>
#include<iomanip>
using namespace std;

#include <windows.h>

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
  函数名称：draw_frame_no_prompt
  功    能：通过一系列嵌套循环画出伪图形边框
  输入参数：game - 游戏结构体
  返 回 值：
***************************************************************************/
void draw_frame_no_prompt(const MineSweeperGame &game,int mode)
{
    int start_x = 5;   
    int start_y = 3;    
    int cell_width = 6;
    int frame_width = game.cols * cell_width+1;
    int frame_height = game.rows*3 ;

    for (int x = 0; x < frame_width-6; x+=6)
    {
        if (x == 0)
        {
            cct_showstr(start_x + x, start_y, "╔", COLOR_HWHITE, COLOR_BLACK, 1);
            cct_showstr(start_x + x, start_y + frame_height, "╚", COLOR_HWHITE, COLOR_BLACK, 1);

        }
        for (int y = 0; y < frame_height; y += 3)
        {
            if (x == 0)
            {
                if (y != 0)
                    cct_showstr(start_x + x, start_y + y, "╠", COLOR_HWHITE, COLOR_BLACK, 1);
            }
            for (int i = 1; i < 3; i++)
            {
                cct_showstr(start_x + x, start_y + y + i, "║", COLOR_HWHITE, COLOR_BLACK, 1);
                for (int k = 2; k < 7; k++)
                {
                    if (mode == 6)
                        cct_showstr(start_x + x + k, start_y + y + i, " ", COLOR_WHITE, COLOR_BLACK, 1);
                    else if (mode == 7)
                        cct_showstr(start_x + x + k, start_y + y + i, " ", COLOR_YELLOW, COLOR_BLACK, 1);
                }
            }
            if (x > 1)
            {
                if (y == 0)
                    cct_showstr(start_x + x, start_y + y, "╦", COLOR_HWHITE, COLOR_BLACK, 1);
                else if (y == frame_height - 3)
                {
                    cct_showstr(start_x + x, start_y + y, "╬", COLOR_HWHITE, COLOR_BLACK, 1);
                    cct_showstr(start_x + x, start_y + y + 3, "╩", COLOR_HWHITE, COLOR_BLACK, 1);
                }

                else
                    cct_showstr(start_x + x, start_y + y, "╬", COLOR_HWHITE, COLOR_BLACK, 1);
            }
            for (int j = 1; j < cell_width; j++)
            {
                cct_showstr(start_x + j + x, start_y + y, "═", COLOR_HWHITE, COLOR_BLACK, 1);
                cct_showstr(start_x + j + x, start_y + frame_height, "═", COLOR_HWHITE, COLOR_BLACK, 1);
            }
            if (x == frame_width - 7)
            {
                cct_showstr(start_x + x + 6, start_y, "╗", COLOR_HWHITE, COLOR_BLACK, 1);
                for (int i = 1; i < 3; i++)
                {
                    cct_showstr(start_x + x + 6, start_y + y + i, "║", COLOR_HWHITE, COLOR_BLACK, 1);
                }
                cct_showstr(start_x + x + 6, start_y + y, "╣", COLOR_HWHITE, COLOR_BLACK, 1);
                cct_showstr(start_x + x + 6, start_y + frame_height, "╝", COLOR_HWHITE, COLOR_BLACK, 1);
            }
        }
    } 
    cct_setcolor();
}

void open_graph(const Cell& cell, int& new_x, int& new_y, bool open = 0, int flag = 0, bool is_mine = 0)
{
    if (open && flag == 0)
    {
        if (cell.mine)
            cct_showstr(new_x, new_y, "*", COLOR_WHITE, COLOR_BLACK, 1);
        else if (cell.around == 0)
        {
            for (int a = -1; a < 3; a++)
            {
                for (int b = -1; b < 1; b++)
                    cct_showstr(new_x + a, new_y + b, " ", COLOR_WHITE, COLOR_BLACK, 1);
            }
        }
        else if (cell.around != 0)
        {
            for (int a = -1; a < 3; a++)
            {
                for (int b = -1; b < 1; b++)
                    cct_showstr(new_x + a, new_y + b, " ", COLOR_WHITE, COLOR_BLACK, 1);
            }
            cct_showch(new_x, new_y, char(49 + cell.around - 1), COLOR_WHITE, cell.around, 1);
        }
           
    }
    else if (flag)
    {
        for (int a = -1; a < 3; a++)
        {
            for (int b = -1; b < 1; b++)
                cct_showstr(new_x + a, new_y + b, " ", COLOR_HRED, COLOR_BLACK, 1);
        }
        cct_showch(new_x, new_y, '#', COLOR_HRED, COLOR_BLACK, 1);
    }
    else
    {
        for (int a = -1; a < 3; a++)
        {
            for (int b = -1; b < 1; b++)
                cct_showstr(new_x + a, new_y + b, " ", COLOR_YELLOW, COLOR_BLACK, 1);
        }
    }
    cct_setcolor();
}

void print_other(const MineSweeperGame& game,int mode)
{
    int start_x = 5;
    int start_y = 3; 
    int row_no = 65 + game.rows;
    int col_no = 97 + game.cols;
    cct_gotoxy(start_x + 3,start_y-1);
    for (int j = 97; j < col_no; j++)
    {
        if(j<123)
            cout << char(j) << "     ";
        else if (j >= 123)
            cout << int(j - 97) << "    ";
    }
    cout << endl;
    for (int i = 1; i <= game.rows; i++)
    {
        cct_setcolor();
        cct_gotoxy(start_x - 2, start_y + i * 3-2);
        cout << (char)('A' + i - 1) ;
        if (mode == 6)
        {
            for (int j = 1; j <= game.cols; j++)
            {
                int new_x = start_x + 6 * (j - 1) + 3;
                int new_y = start_y + 3 * (i - 1) + 2;
                if (game.board[i][j].mine)
                    cct_showstr(new_x, new_y, "*", COLOR_WHITE, COLOR_BLACK, 1);
                else if (game.board[i][j].around != 0)
                {
                    cct_showch(new_x, new_y, char(49 + game.board[i][j].around - 1), COLOR_WHITE, game.board[i][j].around, 1);
                    cct_setcolor();
                }
            }
        }
        else if(mode==71)
            cct_setcolor();
        else if (mode == 72)
        {
            for (int j = 1; j <= game.cols; j++)
            {
                int new_x = start_x + 6 * (j - 1) + 3;
                int new_y = start_y + 3 * (i - 1) + 2;
                open_graph(game.board[i][j], new_x, new_y,game.board[i][j].open, game.board[i][j].flag, game.board[i][j].mine);
            }
        }
        cout << endl;
    }
    cct_setcolor();
}

void cal_pos(int &X,int &Y, const MineSweeperGame& game,int dif)
{
    int m = (X - 5) % 6;
    int x = X - 5, num = 1;
    for (int i = 6; i < x; i += 6)
        num++;
    int y = Y - 3, num2 = 1;
    for (int j = 3; j < y; j += 3)
        num2++;
    char no_col = 'a' + num-1;
    char no_row = 'A' + num2-1;
    cout << "[当前光标] ";
    if (dif == 1)
    {
        if (m == 0 || m == 1 || Y % 3 == 0 || X > 60 || X < 5 || Y < 3 || Y>30)
            cout << "位置非法" << endl;
        else
            cout << no_row << "行" << no_col << "列  " << endl;
    }
    else if (dif == 2)
    {
        if (m == 0 || m == 1 || Y % 3 == 0 || X > 102 || X < 5 || Y < 3 || Y>52)
            cout << "位置非法" << endl;

        else
            cout << no_row << "行" << no_col << "列  " << endl;
    }
    else
    {
        if (m == 0 || m == 1 || Y % 3 == 0 || X > 186 || X < 5 || Y < 3 || Y>52)
            cout << "位置非法" << endl;
        else
        {
            if(no_col<123)
                cout << no_row << "行" << no_col << "列  " << endl;
            else
                cout<< no_row << "行" <<int(no_col-97) << "列  " << endl; 
        }
    }
}

int cal_pos_open_col(int& X,  const MineSweeperGame& game)
{
    int m = (X - 5) % 6;
    int x = X - 5, num = 1;
    for (int i = 6; i < x; i += 6)
        num++;
    return num;
}

int cal_pos_open_row( int& Y, const MineSweeperGame& game)
{
    int y = Y - 3, num2 = 1;
    for (int j = 3; j < y; j += 3)
        num2++;
    return num2;
}

void print_end_board_graph(const MineSweeperGame& game,int &x,int &y)
{
    int new_x = 5+6*(y-1) +3;
    int new_y = 3 + 3 * (x - 1) + 2;
    for (int a = -1; a < 3; a++)
    {
        for (int b = -1; b < 1; b++)
            cct_showstr( new_x+ a, new_y + b, " ", COLOR_WHITE, COLOR_BLACK, 1);
    }
    cct_showch(new_x, new_y, '*', COLOR_WHITE, COLOR_BLACK, 1);
    cct_setcolor();
}
/***************************************************************************
  函数名称：display_data_no_prompt
  功    能：显示内部数据，0不显示
  输入参数：game - 游戏结构体
  返 回 值：无
***************************************************************************/
void draw_graph()
{
    cct_cls();
    int difficulty = input_dif(); 
    MineSweeperGame game;
    set_dif(game, difficulty);
    zero_init(game);
    place_mines(game);
    calculate_around_numbers(game);
    cct_setconsoleborder(6 * game.cols + 10, 3 * game.rows + 8, 6 * game.cols + 16, 9001);
    draw_frame_no_prompt(game,6);
    print_other(game,6);
}

void read_mouse()
{
    cct_cls();
    int difficulty = input_dif();
    MineSweeperGame game;
    set_dif(game, difficulty);
    zero_init(game);
    place_mines(game);
    calculate_around_numbers(game);
    cct_setconsoleborder(6 * game.cols + 10, 3 * game.rows + 8, 6 * game.cols + 16,9001);
    draw_frame_no_prompt(game,6);
    print_other(game,6);
    static int MX_old = -1, MY_old = -1, MAction_old = MOUSE_ONLY_MOVED;
    int X = 0, Y = 0;
    int ret, maction=0;
    int keycode1=0, keycode2=0;
    cct_enable_mouse();
    while (1)
    {
        ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
        if (ret == CCT_MOUSE_EVENT)
        {
            cct_gotoxy(0, 3+game.rows * 3 + 2);
            cal_pos(X, Y,game, difficulty);
        }
    }
}

void open_mine_graph()
{
    cct_cls();
    int difficulty = input_dif();
    MineSweeperGame game;
    set_dif(game, difficulty);
    cct_setconsoleborder(6 * game.cols + 10, 3 * game.rows + 8, 6 * game.cols + 16, 9001);
    draw_frame_no_prompt(game, 7);
    print_other(game,71);
    static int MX_old = -1, MY_old = -1, MAction_old = MOUSE_ONLY_MOVED;
    int X = 0, Y = 0;
    int ret, maction = 0;
    int keycode1 = 0, keycode2 = 0;
    cct_enable_mouse();
    while (1)
    {
        ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
        if (ret == CCT_MOUSE_EVENT)
        {
            cct_gotoxy(0, 3 + game.rows * 3 + 2);
            cal_pos(X, Y, game, difficulty);
            if (maction == MOUSE_LEFT_BUTTON_CLICK)
            {
                int col = cal_pos_open_col(X, game);
                int row = cal_pos_open_row(Y, game);
                //cout << row << endl;
                //cout << col << endl;
                zero_init(game);
                place_mines(game, row, col, 1);
                calculate_around_numbers(game);
                open_not_mine(game, row, col);
                print_other(game, 72);
                break; 
            }
        }
    }
}

void basic_game_graph()
{
    cct_cls();
    int difficulty = input_dif();
    MineSweeperGame game;
    set_dif(game, difficulty);
    cct_setconsoleborder(6 * game.cols + 10, 3 * game.rows + 8, 6 * game.cols + 16, 9001);
    draw_frame_no_prompt(game, 7);
    print_other(game, 71);
    static int MX_old = -1, MY_old = -1, MAction_old = MOUSE_ONLY_MOVED;
    int X = 0, Y = 0;
    int ret, maction = 0;
    int keycode1 = 0, keycode2 = 0;
    bool first_click = true;  // 标记是否是第一次点击
    int first_click_row = 0, first_click_col = 0;
    cct_enable_mouse();
    while (1)
    {
        ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
        if (ret == CCT_KEYBOARD_EVENT)
        {
            if (keycode1 == 27)
            {
                cout << "游戏退出" << endl;
                return;
            }
        }
        if (ret == CCT_MOUSE_EVENT)
        {

            cct_gotoxy(0, 3 + game.rows * 3 + 2);
            cal_pos(X, Y, game,difficulty);
            int col = cal_pos_open_col(X, game);
            int row = cal_pos_open_row(Y, game);
            if (maction == MOUSE_LEFT_BUTTON_CLICK)
            {
                if (first_click)
                {
                    first_click = false;
                    first_click_row = row;
                    first_click_col = col;
                    zero_init(game);
                    place_mines(game, row, col, 1);
                    calculate_around_numbers(game);
                    open_not_mine(game, row, col);
                    print_other(game, 72);
                }
                else
                {
                    if (game.board[row][col].mine)
                    {
                        game.board[row][col].open = 1;
                        print_end_board_graph(game, row, col);
                        cct_gotoxy(2,  game.rows * 3 + 6);
                        cout << "你输了，游戏结束" << endl;
                        return;
                    }
                    else if (game.board[row][col].around == 0)
                        open_not_mine(game, row, col);
                    else
                        game.board[row][col].open = 1;
                    print_other(game, 72);
                    if (findallmines(game))
                    {
                        cout << "恭喜胜利，游戏结束" << endl;
                        return;
                    }
                }
            }
            else if (maction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                if (first_click)
                    continue;
                if (game.board[row][col].flag)
                {
                    game.board[row][col].flag = 0;
                }
                else
                    game.board[row][col].flag = 1;
                print_other(game, 72);
            }
        }
    }
}
void game_graph()
{
    cct_cls();
    int difficulty = input_dif();
    MineSweeperGame game;
    Timer game_timer;
    game_timer.start();
    set_dif(game, difficulty);
    cct_setconsoleborder(6*game.cols + 10, 3*game.rows + 8, 6*game.cols+16,9001);
    draw_frame_no_prompt(game, 7);
    print_other(game, 71);
    static int MX_old = -1, MY_old = -1, MAction_old = MOUSE_ONLY_MOVED;
    int X = 0, Y = 0;
    int ret, maction = 0;
    int keycode1 = 0, keycode2 = 0;
    bool first_click = true;  // 标记是否是第一次点击
    int first_click_row = 0, first_click_col = 0;
    cct_enable_mouse();
    while (1)
    {
        ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
        if (ret == CCT_KEYBOARD_EVENT)
        {
            if (keycode1 == 27)
            {
                cout << "游戏退出" << endl;
                return;
            }
            else if (keycode1==32)
            { 
                cct_gotoxy(0, 0);
                game_timer.pause();
                game_timer.printElapsedTime();
                game_timer.resume();
                continue;
            }
        }
        if (ret == CCT_MOUSE_EVENT)
        {
            cct_gotoxy(0, 3 + game.rows * 3 + 2);
            cal_pos(X, Y, game, difficulty);
            int col = cal_pos_open_col(X, game);
            int row = cal_pos_open_row(Y, game);
            if (maction == MOUSE_LEFT_BUTTON_CLICK)
            {
                if (first_click)
                {
                    first_click = false;
                    first_click_row = row;
                    first_click_col = col;
                    zero_init(game);
                    place_mines(game, row, col, 1);
                    calculate_around_numbers(game);
                    open_not_mine(game, row, col);
                    print_other(game, 72);
                }
                else
                {
                    if (game.board[row][col].mine)
                    {
                        game.board[row][col].open = 1;
                        print_end_board_graph(game, row, col);
                        cct_gotoxy(2, game.rows * 3 + 6);
                        cout << "你输了，游戏结束 "<<endl;
                        game_timer.stop();
                        game_timer.printElapsedTime();
                        return;
                    }
                    else if (game.board[row][col].around == 0)
                        open_not_mine(game, row, col);
                    else
                        game.board[row][col].open = 1;
                    print_other(game, 72);
                    if (findallmines(game))
                    {
                        cct_gotoxy(2, game.rows * 3 + 6);
                        cout << "恭喜胜利，游戏结束 " << endl;
                        game_timer.stop();
                        game_timer.printElapsedTime();
                        return;
                    }
                }
            }
            else if (maction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                if (first_click)
                    continue;
                if (game.board[row][col].flag)
                {
                    game.board[row][col].flag = 0;
                    game.flag_marked--;
                }
                else
                {
                    game.board[row][col].flag = 1;
                    game.flag_marked++;
                }
                print_other(game, 72);
            }
        }
        cct_gotoxy(0, 0);
        if (game.flag_marked<=game.mines && game.flag_marked>-1)
        {
            cct_setcolor(COLOR_BLACK, COLOR_RED);
            cout << "  剩余雷数: " << (game.mines - game.flag_marked) << "           ";
            
            cct_setcolor();
        }
        else if (game.flag_marked == 0)
        {
            cct_setcolor(COLOR_BLACK, COLOR_RED);
            cout << "  剩余雷数: 0";
            
            cct_setcolor();
        }
    }
}
