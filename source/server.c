
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/operation.h"
#include "../include/apisocket.h"

void errorHandler(char *errorMessage) {
    printf ("%s", errorMessage);
}

int main(int argc, char *argv[]) {

    if(initSocket() != SUCCESS){
        errorHandler("Something went wrong during WSA Startup");
    }else{
        printf("Socket API initialized\n");
    }
    
    int port;
    if (argc > 1) {
        port = atoi(argv[1]);
    }
    else
        port = PROTOPORT;
    if (port < 0) {
        printf("bad port number %s \n", argv[1]);
        return 0;
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    
    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0) {
        errorHandler("socket creation failed.\n");
        //clearwinsock();
        return -1;
    }
    printf("TCP server socket created.\n");
    
    
    // IP assignment
    memset(&server_addr, 0, sizeof(server_addr)); // ensures that extra bytes contain 0
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(port);
    
    if (bindSocket(server_socket, server_addr) < 0) {
        errorHandler("Bind error.\n");
        closeSocket(server_socket);
        //clearwinsock();
        return -1;
    }
    printf("Bind to the port: %d\n", port);
    
    // listening socket
    if (listen (server_socket, QLEN) < 0) {
        errorHandler("Listen failed.\n");
        closeSocket(server_socket);
        //clearwinsock();
        return -1;
    }
    printf("Listening...\n");
    printf("Waiting for a Client...");
    
    // acccept NEW CONNECTION
    while (1) {
        addr_size = sizeof(client_addr);
        if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size)) < 0) {
            errorHandler("accept() failed.\n");
            closeSocket(server_socket);
            //clearwinsock();
            return 0;
        }
        printf("\nHandling client: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        //connection accepted
        char message[DEF_BUFFER]="Connection occured.\n";
        if(sendData(client_socket, message, strlen(message)) == ERROR){
            errorHandler("Message sent with error\n");
        }else{
            printf("Connection message successfully sent.\n");
        }
        
        //receive operation and send result
        operation op;
        while(receiveOperation(client_socket, &op) == SUCCESS){
            char* op_result=generateOpMsg(op);
                    
            if(sendData(client_socket, op_result, strlen(op_result))==ERROR){
                errorHandler("Message sent with error.\n");
            }else{
                printf("Operation result successfully sent.\n");
            }
        }
        closeSocket(client_socket);
        printf("Client disconnected.\n");
    }
    
    closeSocket(server_socket);
    return SUCCESS;
}

        
        

