#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // create the socket
    int clientSocket;
    char address[256] = "127.0.0.1";

    // // prompt for address
    // printf("Enter address of server:\n");
    // scanf("%s", &address);

    // AF_INET is IPv4 address
    // SOCK_STREAM is a TCP socket
    // 0 is default protocol (tcp)
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // specify socket address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    // port number must be converted from int into network byte order 
    serverAddress.sin_port = htons(8080);

    // sin_addr is struct itself
    // convert IPv4 address to struct in_addr
    inet_aton(address, &serverAddress.sin_addr.s_addr);

    // cast address to correct structure type and passes pointer
    // will return 0 or -1 for error handling
    int connectionStatus = connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    // check return of connection
    if (connectionStatus == -1) {
        printf("!!! There was an issue connecting to the server !!!\n\n");
    }

    // string stores response from server
    char serverResponse[256];

    // serverResponse is location of data that is recieved
    // sizeof data buffer
    // 0 is optional flag parameter
    recv(clientSocket, &serverResponse, sizeof(serverResponse), 0);

    // print server's reponse to terminal
    printf("%s", serverResponse);

    // close the socket
    close(clientSocket);

    return 0;
} 