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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CLR() printf("\033[2J\033[H")

void check_nearby_row_squares( int8_t* board, int width, int height, int x, int y, int y_pos, int8_t* counter)
{
    if ( y_pos < 0 || y_pos >= height ) return;

    for ( int i = -1; i < 2; i++ ) {
        int x_1 = x + i;

        if ( x_1 < 0 || x_1 >= width ) continue;

        if ( board[ y_pos * width + x_1 ] == -1 ) *counter += 1;
    }
}

void populate_board( int8_t* board, int number_of_mines, int width, int height )
{
    for ( int i = 0; i < number_of_mines; i++ ) {
        int     x = rand() % width;
        int     y = rand() % height;

        if ( board[y * width + x] != -1 ) {
            board[y * width + x] = -1;
        }

        else    i--;
    }

}

void print_board( int8_t* board, int width, int height )
{
    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) {
            switch( board[i * width + j] ) {
                case 127:   printf("X\t");
                            break;

                case -1:    printf("X\t");
                            break;

                case -128:  printf("\033[0;31m*\t\033[0m");
                            break;

                case 0:     printf(" \t");
                            break;

                case 1:     printf("\033[0;34m1\t\033[0m");
                            break;

                case 2:     printf("\033[0;32m2\t\033[0m");
                            break;

                case 3:     printf("\033[0;31m3\t\033[0m");
                            break;

                case 4:     printf("\033[1;35m4\t\033[0m");
                            break;

                case 5:     printf("\033[1;31m5\t\033[0m");
                            break;

                case 6:     printf("\033[0;36m6\t\033[0m");
                            break;

                case 7:     printf("\033[0;30m7\t\033[0m");
                            break;

                case 8:     printf("\033[0;33m8\t\033[0m");
                            break;

                default:    printf("%d\t", board[i * width + j]);
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

int main( void )
{
    int8_t*     game_board;
    int         width = 0, height = 0;

    srand( time(NULL) );

    // Get the width and the height of the game board
    printf("Width and the height of the board: ");
    scanf( "%d %d", &width, &height );

    if ( width < 0 || height < 0 || width > 255 || height > 255 ) {
        printf("Board size outside of range [0; 255]");
        return -1;
    }

    // Initialize the game board
    game_board  = malloc( (width * height) * sizeof(int8_t) );

    for ( int y = 0; y < height; y++ ) {
        for ( int x = 0; x < width; x++ ) {
            game_board[ y * width + x ] = 127;
        }
    }

    // Populate the board with mines
    double  average_mine_ratio = 0.15625;
    int     number_of_mines = ( width * height ) * average_mine_ratio;

    printf("Number of mines: %d", number_of_mines );

    populate_board( game_board, number_of_mines, width, height );

    // Gameplay loop
    bool loser = false;
    int checked = 0;


    while ( true )
    {
        CLR();
        print_board( game_board, width, height );

        if ( loser ) break;
        if ( checked == (width * height) - number_of_mines ) break;

        char    user_input[8];
        int     x, y;

        if ( fgets( user_input, sizeof(user_input), stdin ) ) {
            if ( strcmp( user_input, "exit" ) == 0 ) break;
            if ( sscanf( user_input, "%d %d", &x, &y ) >= 1 ) {
                if ( x < 0 || x > 255 || y < 0 || y > 255 ) continue;

                if ( game_board[ y * width + x ] == -1 ) {
                    game_board[y * width + x] = -128;
                    loser = true;

                }
                else if ( game_board[ y * width + x ] == 127 ) {
                    int8_t  nearby_mine_counter = 0;

                    check_nearby_row_squares( game_board, width, height, x, y, y - 1, &nearby_mine_counter );
                    check_nearby_row_squares( game_board, width, height, x, y, y, &nearby_mine_counter );
                    check_nearby_row_squares( game_board, width, height, x, y, y + 1, &nearby_mine_counter );

                    game_board[ y * width + x ] = nearby_mine_counter;
                    checked++;
                }
            }
        }
    }

    if ( loser ) {
        printf("\nYOU LOSE\nGAME OVER\n");

    } else {
        printf("\nYOU WIN\n");

    }

    // Free up memory and exit
    free( game_board );
    return 0;
}

