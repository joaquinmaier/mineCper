#include "../include/input.h"

int parse_input( char* user_input, int* x, int* y )
{
    if ( sscanf( user_input, "%d %d", x, y ) < 1 ) {
        return -1;
    }

    return 0;
}

int check_commands( char* user_input, int* cmd )
{
    switch ( user_input[0] ) {
        case 'f':
            *cmd = 1;
            return 1;

        case 'F':
            *cmd = 2;
            return 2;

        case 'e':
        case 'E':
            *cmd = 3;
            return 3;

        case 'c':
            *cmd = 4;
            return 4;

        default:
            *cmd = 0;
            return 0;

    }
}


