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

#include "../include/board.h"
#include "../include/input.h"

#define CLR() printf("\033[2J\033[H")

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
        print_stats( number_of_mines, checked, (width * height) );

        if ( loser ) break;
        if ( checked == (width * height) - number_of_mines ) break;

        char    user_input[9];
        int     x = -1, y = -1;

        printf(": ");
        if ( fgets( user_input, sizeof(user_input), stdin ) ) {
            if ( check_commands( user_input, &cmd ) > 0 ) {
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
                        set_in_board( game_board, width, x, y, calc_cell_value( game_board, width, height, x, y ) );

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

                case 4:
                {
                    int8_t value = game_board[ y * width + x ];

                    // If it is not a number, ignore
                    if ( value == ND_EMPTY_SPACE || value == ND_MINE_HIDDEN || value == ND_FLAG_EMPTY || value == ND_FLAG_MINE ) break;

                    int8_t nearby_mine_counter = 0;

                    check_nearby_flag_squares( game_board, width, height, x, y, y-1, &nearby_mine_counter );
                    check_nearby_flag_squares( game_board, width, height, x, y, y, &nearby_mine_counter );
                    check_nearby_flag_squares( game_board, width, height, x, y, y+1, &nearby_mine_counter );

                    // Cannot clear nearby if they are not equal
                    if ( nearby_mine_counter != value ) break;

                    for ( int y_1 = y-1; y_1 <= y+1; y_1++ ) {
                        for ( int x_1 = x - 1; x_1 <= x+1; x_1++ ) {
                            if ( y_1 < 0 || y_1 >= height || x_1 < 0 || x_1 >= width ) continue;

                            if ( game_board[ y_1 * width + x_1 ] == ND_EMPTY_SPACE ) {
                                set_in_board( game_board, width, x_1, y_1, calc_cell_value( game_board, width, height, x_1, y_1 ) );

                                checked++;
                            }
                            else if ( game_board[ y_1 * width + x_1 ] == ND_MINE_HIDDEN ) {
                                set_in_board( game_board, width, x_1, y_1, ND_MINE );

                                loser = true;
                            }

                        }
                    }
                }
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

