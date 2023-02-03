#ifndef _SPACESH0T_H
#define _SPACESH0T_H

#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define count(x)	sizeof(x)/sizeof(x[0])
#define diff(x,y)	abs(x-y)

void throwException(char *msg);
void askForNameAndScoreBoard();


#endif // SPACESH0T_H