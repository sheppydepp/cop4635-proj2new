//============================================================================
// Name        : client_main.cpp
// Author      : Tyre Sheffield, Shep Harper
// Version     : 1.0
// Description : Starts the client to connect to a server and find a file in the server
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char const *argv[]) {
    char clientBuffer[1024];
    const char* hostToConnect;
    const char* portToConnect;
    const char* fileToRetrieve;
    int portNumber;
    int userSocket = 0;
    long valueRead;
    struct sockaddr_in serverAddress;

    std::string fileToObtain;
    std::string messageSendToServer;
    int messageSize;

    if (argc != 4) {
        std::cerr << "Error- Command needs to be: " << argv[0] << " <server_address> <port> <file_name>" << std::endl;
        return 1;
    }
    hostToConnect = argv[1];
    portToConnect = argv[2];
    fileToRetrieve = argv[3];

        // retrieves name of file the client is trying to access in format of of "/testPresence.html" or "/imp.jpg"

        fileToObtain = fileToRetrieve;

        // Creates the initial line a client sends to server for retrieving a file, and makes the connection
        std::ostringstream messageToServer;
        messageToServer << "GET " << fileToObtain << " HTTP/1.1\r\n";
        messageSendToServer = messageToServer.str();
        messageSize = messageSendToServer.size() + 1;
        portNumber = atoi(portToConnect);

        // Creating socket
        userSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (userSocket < 0) {
            perror("n Error in socket creation\n");
            exit(1);
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(portNumber);
        serverAddress.sin_addr.s_addr = inet_addr(hostToConnect);

        if (connect(userSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
            perror("\nFailure in connect() method! \n");
	    close(userSocket);
            exit(1);
        }

        if(send(userSocket, messageSendToServer.c_str(), messageSize, 0) == -1){
            perror("Error in send()!");
            exit(1);
        }
	cout << "Making a GET request to the server. \n" ;

//OUTPUT Section 
    // Read data from server and print to console
    while ((valueRead = read(userSocket, clientBuffer, 1024)) > 0) {
        fwrite(clientBuffer, 1, valueRead, stdout);
    }

    if (valueRead < 0) {
        perror("Error in reading response");
        exit(1);
    }

    close(userSocket);
    return 0;
}


