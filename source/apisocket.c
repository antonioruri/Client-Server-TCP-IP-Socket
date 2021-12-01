
#include "../include/apisocket.h"

int initSocket(){
    #if defined WIN32
        WSADATA wsadata;
        if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0){
            return ERROR;
        }
    #endif

    return SUCCESS;
}

void closeSocket(int socket){
    #if defined WIN32
        closesocket(socket);
        WSACleanup();
    #else
        close(socket);
    #endif
}

int bindSocket(int socket, struct sockaddr_in address){
    return bind(socket, (struct sockaddr*)&address, sizeof(address));
}

int sendData(int destination_sock, void* data, size_t dsize){
    if((send(destination_sock, data, dsize, 0) != dsize)){
            return ERROR;
        }
        return dsize;
}
char *receiveMsg(int socket){
    char buffer[DEF_BUFFER];
    int valread = recv(socket, buffer, DEF_BUFFER, 0);

    if(valread > 0){
        buffer[valread] = '\0';
    }else{
        return NULL;
    }

    char *result = (char *) malloc(sizeof(char) * strlen(buffer));
    strcpy(result, buffer);

    return result;
}

int sendOperation(int destination_socket, operation operation){
    operation.op = htonl(operation.op);
    operation.a = htonl(operation.a);
    operation.b = htonl(operation.b);
    return sendData(destination_socket, &operation, sizeof(operation));
}
int receiveOperation(int socket, operation *operation){
    if(recv(socket, operation, sizeof(*operation), 0) != ERROR){
       operation->a = ntohl(operation->a);
       operation->b = ntohl(operation->b);
       operation->op = ntohl(operation->op);
       operation->op = intochar(operation->op);
       return SUCCESS;
    }
    return ERROR;
}

char *generateOpMsg(operation op){
    char buffer[DEF_BUFFER] = "";

    switch(op.op){
        case '+':
            sprintf(buffer, "Result of the addition %d + %d = %.1f\0", op.a, op.b, (double)(op.a + op.b));
            break;
        case '-':
            sprintf(buffer, "Result of the subtraction %d - %d = %.1f\0", op.a, op.b, (double)(op.a - op.b));
            break;
        case '/':
            if(op.b == 0){
                    sprintf(buffer, "Result of the division %d / %d = error\0", op.a, op.b);
            }else{
                    sprintf(buffer, "Result of the division %d / %d = %.1f\0", op.a, op.b, (double)(op.a / op.b));
            }
            break;
        case '*':
            sprintf(buffer, "Multiplication result %d + %d = %.1f\0", op.a, op.b, (double)(op.a * op.b));
            break;

        default:
            strcpy(buffer, "End client process\n");
    }

    char* result_message = (char *) malloc(sizeof(char) * strlen(buffer));
    strcpy(result_message, buffer);
    return result_message;
}

