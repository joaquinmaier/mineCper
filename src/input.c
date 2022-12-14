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


