
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/operation.h"
#include "../include/apisocket.h"

void errorHandler(char *errorMessage) {
    printf ("%s", errorMessage);
}

int main(void) {

    if(initSocket()!=0){
        errorHandler("WINSOCK not initilized");
    }
    
    // CLient socket creation
    int client_socket;
    client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket < 0) {
        errorHandler("Socket creation failed.\n");
        closesocket(client_socket);
        return -1;
    }
    // IP assignment
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PROTOPORT);

    // connection to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address))< 0)
    {
        errorHandler( "Failed to connect.\n" );
        closesocket(client_socket);
        return -1;
    }
    
    char *message=receiveMsg(client_socket);
    printf("%s", message);
    
    operation op;
    char m; //service char to test when client close connection
    printf("Insert operation: \nUse one of this +,-,/,* operators and two integer operands\nEX. + 17 92\n");
    while((m!='=')){
        op=readOperation();
        if(sendOperation(client_socket, op)==ERROR){
            errorHandler("Operation sending failed");
        }
        char *operation_result=receiveMsg(client_socket);
        printf("%s\n", operation_result);
        printf("Press ENTER for a new operation or press '=' to quit.");
        m=getchar();
    }

    closeSocket(client_socket);
    printf("Disconnected.\n");
    
    return SUCCESS;
}
