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

#define AVG_MINE_RATIO  0.15625

#define ND_MINE_HIDDEN  -1
#define ND_MINE         -128
#define ND_FLAG_MINE    -64         // Flag is correctly placed
#define ND_FLAG_EMPTY   64          // Flag is incorrectly placed
#define ND_EMPTY_SPACE  127

#define CLR() printf("\033[2J\033[H")

void set_in_board( int8_t* board, int board_width, int x, int y, int8_t val )
{
    board[ y * board_width + x ] = val;
}

int parse_input( char* user_input, int* x, int* y )
{
    if ( sscanf( user_input, "%d %d", x, y ) < 1 ) {
        return -1;
    }

    return 0;
}

int check_commands( char* user_input, int size, int* cmd )
{
    if ( user_input[0] == 'f' ) {
        *cmd = 1;
        return 1;
    }

    if ( user_input[0] == 'F' ) {
        *cmd = 2;
        return 2;
    }

    if ( user_input[0] == 'e' || user_input[0] == 'E' ) {
        *cmd = 3;
        return 3;
    }

    *cmd = 0;
    return 0;
}

void check_nearby_row_squares( int8_t* board, int width, int height, int x, int y, int y_pos, int8_t* counter)
{
    if ( y_pos < 0 || y_pos >= height ) return;

    for ( int i = -1; i < 2; i++ ) {
        int x_1 = x + i;

        if ( x_1 < 0 || x_1 >= width ) continue;

        if ( board[ y_pos * width + x_1 ] == ND_MINE_HIDDEN || board[ y_pos * width + x_1 ] == ND_FLAG_MINE ) *counter += 1;
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

int main( void )
{
    FILE*       log;
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
            game_board[ y * width + x ] = ND_EMPTY_SPACE;

        }
    }

    // Populate the board with mines
    int     number_of_mines = ( width * height ) * AVG_MINE_RATIO;

    populate_board( game_board, number_of_mines, width, height );

    // Gameplay loop
    bool loser = false;
    int cmd = -1;
    int checked = 0;

    while ( true )
    {
        CLR();
        print_board( game_board, width, height );

        if ( loser ) break;
        if ( checked == (width * height) - number_of_mines ) break;

        char    user_input[9];
        int     x = -1, y = -1;

        if ( fgets( user_input, sizeof(user_input), stdin ) ) {
            if ( check_commands( user_input, sizeof( user_input ), &cmd ) > 0 ) {
                parse_input( user_input + sizeof(char), &x, &y );

            } else {
                parse_input( user_input, &x, &y );

            }

            if ( cmd == 3 ) break;

            if ( x < 0 || x > 255 || y < 0 || y > 255 ) continue;

            switch ( cmd ) {
                case 0:
                    if ( game_board[ y * width + x ] == ND_MINE_HIDDEN ) {
                        set_in_board( game_board, width, x, y, -128 );
                        loser = true;

                    }
                    else if ( game_board[ y * width + x ] == ND_EMPTY_SPACE ) {
                        int8_t  nearby_mine_counter = 0;

                        check_nearby_row_squares( game_board, width, height, x, y, y - 1, &nearby_mine_counter );
                        check_nearby_row_squares( game_board, width, height, x, y, y, &nearby_mine_counter );
                        check_nearby_row_squares( game_board, width, height, x, y, y + 1, &nearby_mine_counter );

                        set_in_board( game_board, width, x, y, nearby_mine_counter );
                        checked++;
                    }
                    break;

                case 1:
                    if ( game_board[ y * width + x ] == ND_MINE_HIDDEN ) {
                        set_in_board( game_board, width, x, y, ND_FLAG_MINE );

                    }
                    else if ( game_board[ y * width + x ] == ND_EMPTY_SPACE ) {
                        set_in_board( game_board, width, x, y, ND_FLAG_EMPTY );

                    }
                    break;

                case 2:
                    if ( game_board[ y * width + x ] == ND_FLAG_MINE ) {
                        set_in_board( game_board, width, x, y, ND_MINE_HIDDEN );

                    }
                    else if ( game_board[ y * width + x ] == ND_FLAG_EMPTY ) {
                        set_in_board( game_board, width, x, y, ND_EMPTY_SPACE );

                    }
                    break;
            }
        }
    }

    if ( loser ) {
        printf("\nYOU LOSE\nGAME OVER\n");

    } else if ( cmd != 3 ) {
        printf("\nYOU WIN\n");

    }

    // Free up memory and exit
    free( game_board );
    return 0;
}

