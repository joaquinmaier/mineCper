#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_input( char* user_input, int* x, int* y );

int check_commands( char* user_input, int* cmd );

#endif
