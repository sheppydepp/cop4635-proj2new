#include "client.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    char quitArray[5] = {'q','u','i','t','\0'};
    char clientBuffer[1024];
    char hostToConnect[16];
    char portToConnect[256];
    char fileToRetrieve[256];
    int portNumber;
    int userSocket = 0;
    long valueRead;
    struct sockaddr_in serverAddress;

    std::string fileToObtain;
    std::string messageSendToServer;
    int messageSize;

    while(1) {
        // memset to make sure they all get cleared upon another request by the client
        memset(clientBuffer, '\0', sizeof(clientBuffer));
        memset(hostToConnect, '\0' ,sizeof(hostToConnect));
        memset(portToConnect, '\0' ,sizeof(portToConnect));
        memset(&serverAddress, '\0', sizeof(serverAddress));

        // Obtain host name or "quit" to close out of client
        std::cout << "Enter Host name or quit to quit: ";
        std::cin.getline(hostToConnect, 16);
        if(strncmp(quitArray, hostToConnect, 4) == 0) {
            break;
        }
        std::cout << "Enter Port: ";
        std::cin.getline(portToConnect, 256);

        // Obtains name of file you're looking for in format of of "/testPresence.html" or "/imp.jpg"
        // converts it to string to make it easier to surround with "GET" an "HTTP/1.1" for sending to server.
        std::cout << "Enter the .html file you're trying to access, starting with '/' and ending in .html: ";
        std::cin.getline(fileToRetrieve, 256);
        fileToRetrieve[strlen(fileToRetrieve)-1] = '\0';
        fileToObtain = fileToRetrieve;

        // Construct the first line a client sends to server for obtaining a file, then makes the connection
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
            exit(1);
        }

        if(send(userSocket, messageSendToServer.c_str(), messageSize, 0) == -1){
            perror("Error in send()!");
            exit(1);
        }

        // Data put into clientBuffer but valueRead holds number to see if it could read or not.
        valueRead = read(userSocket, clientBuffer, 1024);
        if(valueRead > 0){
            std::cout << clientBuffer << std::endl;
            clientBuffer[valueRead]='\0';
        }
        else{
            perror("Error in reading response");
            exit(1);
        }
    }

    close(userSocket);
    return 0;
}

