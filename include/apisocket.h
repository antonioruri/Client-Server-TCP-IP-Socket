
#ifndef apisocket_h
#define apisocket_h

#include "operation.h"
#include <stdlib.h>

#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define PROTOPORT 60000
#define LOCALHOST "127.0.0.1"
#define QLEN 5
#define DEF_BUFFER 512


int initSocket(); //Startup WSA(WIN32)
void closeSocket(int socket); //Close socket and WSA Cleanup(WIN£32)
int bindSocket(int socket, struct sockaddr_in addr); //Binding socket to input address

int sendData(int destination_sock, void* data, size_t dsize); //Send generic data and return number of bytes sent
char *receiveMsg(int socket); //Receive a text message
int sendOperation(int socket, operation operation); //Send an opearation-type struct
int receiveOperation(int socket, operation *operation); //Receive operations data
char *generateOpMsg(operation operation);//Calculates the operation and processes a text message with the result

#endif /* apisocket_h */
