
#include "../include/operation.h"

char intochar(int i){
    return i + '0';
}

int chartoint(char c){
    return c - '0';
}

char readChar(string message){
    char buffer[512];

    do{
        printf("%s", message);
        fgets(buffer, 512, stdin);
    }while((strlen(buffer) - 1) > 1 || (strlen(buffer) - 1) <= 0);

    return buffer[0];
}

int readInt(string message){
    int number;
    printf("%s", message);
    scanf("%d", &number);
    return number;
}

operation readOperation(){
    fflush(stdin);
    char temp[512];
    operation op;
    gets(temp);
    char seps[]=" ";
    char *token;
    token= strtok(temp, seps);
    op.op=chartoint(*token);
    token=strtok(NULL, seps);
    op.a=atoi(token);
    token=strtok(NULL, seps);
    op.b=atoi(token);
    return op;
}
