#ifndef BOARD_H
#define BOARD_H

#define AVG_MINE_RATIO  0.15625

#define ND_MINE_HIDDEN  -1
#define ND_MINE         -128
#define ND_FLAG_MINE    -64         // Flag is correctly placed
#define ND_FLAG_EMPTY   64          // Flag is incorrectly placed
#define ND_EMPTY_SPACE  127

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void    set_in_board( int8_t* board, int board_width, int x, int y, int8_t val );

int8_t* init_board( int width, int height );
void    populate_board( int8_t* board, int number_of_mines, int width, int height );
int8_t  calc_cell_value( int8_t* game_board, int width, int height, int x, int y );

void    check_nearby_row_squares( int8_t* board, int width, int height, int x, int y, int y_pos, int8_t* counter );
void    check_nearby_flag_squares( int8_t* board, int width, int height, int x, int y, int y_pos, int8_t* counter );

void    print_board( int8_t* board, int width, int height );
void    print_stats( int number_of_mines, int checked, int spaces );

#endif

