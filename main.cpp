#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string>


using namespace std;

// CURSOR
const int CURSER_BLINKING = 1; // 0 for No, 1 for Yes


void make_grid(WINDOW *board, int boardY, int boardX, int boardHeight, int boardWidth);


int main (int argc, char const *argv[]) {
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(CURSER_BLINKING);

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int top_margin, bot_margin;
    top_margin = bot_margin = 2;
    int left_margin, right_margin;
    left_margin = right_margin = 2;

    int game_board_y, game_board_x;
    game_board_y = 0 + top_margin;
    game_board_x = (xMax * 0.3) + left_margin;

    int game_board_height, game_board_width;
    game_board_height = (yMax - top_margin - bot_margin) * 0.7;
    game_board_width = (xMax - left_margin - right_margin) * 0.7;

    int game_board_spaces = (game_board_width - 2) % 6;

    if(game_board_spaces != 0) {
        right_margin += game_board_spaces - 1;
        game_board_width -= game_board_spaces - 1;
    }

    int mini_board_y, mini_board_x;
    mini_board_y = 0 + top_margin;
    mini_board_x = 0 + left_margin;

    int mini_board_height, mini_board_width;
    mini_board_height = (yMax - top_margin - bot_margin) * 0.5;
    mini_board_width = (xMax - left_margin - right_margin) * 0.3; 

    WINDOW * game_board = newwin(game_board_height, game_board_width, game_board_y, game_board_x);
    wmove(game_board, game_board_y, game_board_y);
    box(game_board, 0, 0);
    wrefresh(game_board);

    WINDOW * mini_board = newwin(mini_board_height, mini_board_width, mini_board_y, mini_board_x);
    wmove(mini_board, mini_board_y, mini_board_x);
    box(mini_board, 0, 0);
    wrefresh(mini_board);

    for(int i = 1; i < game_board_height - 1; i++) {

        if(i % 2 == 0){
            for(int j = 1; j < game_board_width - 1; j++){
                wmove(game_board, i, j);
                wprintw(game_board, "-");
            }
        } else {

            for(int j = 1; j < game_board_width - 1; j++){
                if(j % 4 == 0) {
                    wmove(game_board, i, j);
                    wprintw(game_board, "|");
                }
                
            }

        }
    }

    // screen 20 x 12 changes with resolution
    // grid 40 x 24
    
    int grid[40][24];
    for(int i = 0; i <= 40; i++) {
        for(int j = 0; j <= 24; j ++) {
            int n = rand();
            grid[i][j] = n;
        }
    }


    /*  TO DO  */
    // GET AMOUNT OF CELLS ON SCREEN AS A VARIABLE
    // USE THESE CELL NUMBERS AS THE INDEXES OF THE NUMBERS OF GRID
    // CHANGE THE POS OF CELLS IF TRYING TO MOVE OFF SCREEN
    // MAKE A BOX INSIDE MINI MAP USING THE RATIOS BETWEEN THEM
    // CHANGE GRID SIZE TO A VARIABLE SHOULD BE SET BY THE PLAYER ON GAME START
    // MAKE ANOTHER WINDOW BELOW THE MINI MAP TO SHOW SCORE
    // MAKE A WINDOW AT THE BOTTOM CONTAINING ALL OF THE CONTROLS INFORMATION
    // MOVE LOGIC OUT INTO FUNCTIONS IN OTHER FILES.



    wrefresh(game_board);

    int cursorY = 1;
    int cursorX = 2;
    
    wmove(game_board, cursorY, cursorX);
    wrefresh(game_board);
    while(true) {
        // GAME LOOP
        char key_press = getchar();
        if(key_press == 'w') {
            if(cursorY > 1)
            {
                cursorY -= 2;
            }
        }
        else if(key_press == 'a') {
            if(cursorX > 2)
            {
                cursorX -= 4;
            }
        }
        else if(key_press == 's') {
            if(cursorY < game_board_height - 2)
            {
                cursorY += 2;
            }
        }
        else if(key_press == 'd') {
            if(cursorX < game_board_width - 4)
            {
                cursorX += 4;
            }
        }
        wmove(game_board, cursorY, cursorX);
        wrefresh(game_board);
    }

    wgetch(game_board);
    
    delwin(game_board);
    delwin(mini_board);

    endwin();

    return 0;
};
