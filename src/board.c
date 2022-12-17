/*
Copyright (c) 2022 Joaquín Maier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute and/or sublicense
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "../include/board.h"

void set_in_board( int8_t* board, int board_width, int x, int y, int8_t val )
{
    board[ y * board_width + x ] = val;
}

void check_nearby_row_squares( int8_t* board, int width, int height, int x, int y, int y_pos, int8_t* counter )
{
    if ( y_pos < 0 || y_pos >= height ) return;

    for ( int i = -1; i < 2; i++ ) {
        int x_1 = x + i;

        if ( x_1 < 0 || x_1 >= width ) continue;

        if ( board[ y_pos * width + x_1 ] == ND_MINE_HIDDEN || board[ y_pos * width + x_1 ] == ND_FLAG_MINE ) *counter += 1;
    }
}

void check_nearby_flag_squares( int8_t* board, int width, int height, int x, int y, int y_pos, int8_t* counter )
{
    if ( y_pos < 0 || y_pos >= height ) return;

    for ( int i = -1; i < 2; i++ ) {
        int x_1 = x + i;

        if ( x_1 < 0 || x_1 >= width ) continue;

        if ( board[ y_pos * width + x_1 ] == ND_FLAG_MINE ) *counter += 1;
    }
}

void populate_board( int8_t* board, int number_of_mines, int width, int height )
{
    for ( int i = 0; i < number_of_mines; i++ ) {
        int     x = rand() % width;
        int     y = rand() % height;

        if ( board[y * width + x] != ND_MINE_HIDDEN ) {
            board[y * width + x] = ND_MINE_HIDDEN;
        }

        else    i--;
    }

}

void print_board( int8_t* board, int width, int height )
{
    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) {
            switch( board[i * width + j] ) {
                case ND_MINE_HIDDEN:
                case ND_EMPTY_SPACE:    printf("X\t");
                                        break;

                case ND_FLAG_MINE:
                case ND_FLAG_EMPTY:     printf("\033[0;31m⚐\t\033[0m");
                                        break;

                case ND_MINE:           printf("\033[0;31m*\t\033[0m");
                                        break;

                case 0:                 printf(" \t");
                                        break;

                case 1:                 printf("\033[0;34m1\t\033[0m");
                                        break;

                case 2:                 printf("\033[0;32m2\t\033[0m");
                                        break;

                case 3:                 printf("\033[0;31m3\t\033[0m");
                                        break;

                case 4:                 printf("\033[1;35m4\t\033[0m");
                                        break;

                case 5:                 printf("\033[1;31m5\t\033[0m");
                                        break;

                case 6:                 printf("\033[0;36m6\t\033[0m");
                                        break;

                case 7:                 printf("\033[0;30m7\t\033[0m");
                                        break;

                case 8:                 printf("\033[0;33m8\t\033[0m");
                                        break;

                default:                printf("%d\t", board[i * width + j]);
                                        break;
            }
        }
        printf("\t\033[1;30m%d\033[0m\n", i);
    }

    printf("\n");
    for ( int g = 0; g < width; g++ ) {
        printf("\033[1;30m%d\t\033[0m", g);
    }
    printf("\n\n");
}

void print_stats( int number_of_mines, int checked, int spaces )
{
    printf("\t\tMINES: %d\t\tREVEALED: %d/%d\n\n", number_of_mines, checked, spaces-number_of_mines);
}

int8_t calc_cell_value( int8_t* game_board, int width, int height, int x, int y )
{
    int8_t  nearby_mine_counter = 0;

    check_nearby_row_squares( game_board, width, height, x, y, y - 1, &nearby_mine_counter );
    check_nearby_row_squares( game_board, width, height, x, y, y, &nearby_mine_counter );
    check_nearby_row_squares( game_board, width, height, x, y, y + 1, &nearby_mine_counter );

    return nearby_mine_counter;
}

int8_t* init_board( int width, int height )
{
    int8_t* ptr = malloc( (width * height) * sizeof(int8_t) );

    for ( int y = 0; y < height; y++ ) {
        for ( int x = 0; x < width; x++ ) {
            ptr[ y * width + x ] = ND_EMPTY_SPACE;

        }
    }

    return ptr;
}

