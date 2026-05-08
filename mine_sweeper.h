/* 2551382 李佳仪 卓08 */
#pragma once

#define MAX_ROWS 32
#define MAX_COLUMS 32
#include <Windows.h>
#include<iostream>
#include <conio.h>
/* 空文件，给出的目的是防止大家把文件名弄错 */
int mine_menu();
int input_dif();
void to_be_continued(const char* prompt, const int X = 0, const int Y = 22);
void base_inner();
void open_init();
void open_game();
void open_game_able_to_flag();
void draw_graph();
void read_mouse();
void open_mine_graph();
void basic_game_graph();
void game_graph();




struct Cell 
{
    bool mine;    
    bool open;    
    bool flag;   
    int around; 
};
struct MineSweeperGame 
{
    int rows;       
    int cols;        
    int mines;     
    int flag_marked;
    bool gameover; 
    bool won;   
    Cell board[MAX_ROWS][MAX_COLUMS]; 
    time_t start_time; 
};
void set_dif(MineSweeperGame& game, int dif);
void calculate_around_numbers(MineSweeperGame& game);
void zero_init(MineSweeperGame& game);
void place_mines(MineSweeperGame& game, int r_input = 0, int c_input = 0, bool mode = 0);
void open_not_mine(MineSweeperGame& game, int r, int c);
void print_board(const MineSweeperGame& game, int mode);
bool findallmines(MineSweeperGame& game);
void zero_init(MineSweeperGame& game);
void set_dif(MineSweeperGame& game, int dif);
