
#ifndef operation_h
#define operation_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERROR -1
#define SUCCESS 0

typedef char* string;
typedef struct operation{
    int op; //operator
    int a; //first operand
    int b; //second operand
}operation;

char intochar(int i);
int chartoint(char c);//convert an input integer to a char
char readChar(string message);//read a char from stdin
int readInt(string message);//read integer from stdin
operation readOperation();

#endif /* operation_h */
