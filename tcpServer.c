#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    // set server response string
    char serverMessage[256] = "Server connection achieved";

    // create server socket
    int serverSocket;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // define server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    // port number must be converted from int into network byte order
    serverAddress.sin_port = htons(8080);
    
    // sin_addr is struct itself
    // INADDR_ANY is equivalent of address 0.0.0.0
    // listen on all addresses
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind socket to IP and port
    bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    printf("+++ Connection established +++");

    // 1 is backlog of clients that can connect
    listen(serverSocket, 1);

    // NULL and NULL are additional structs that can be used to see where client is connecting from
    int clientSocket;
    clientSocket = accept(serverSocket, NULL, NULL);

    // send the server message
    send(clientSocket, serverMessage, sizeof(serverMessage), 0);

    close(serverSocket);

    return 0;
}