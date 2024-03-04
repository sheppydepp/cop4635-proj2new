/*
 * Server.cpp
 *
 *  Created on: Feb 17, 2024
 *      Author: Tyre Sheffield, Shep Harper
 */

#include "Server.hpp"

Server::Server() {
	// TODO Auto-generated constructor stub
	 addressLength = sizeof(address);

	 address.sin_family = AF_INET;
	 address.sin_addr.s_addr = INADDR_ANY;
     address.sin_port = htons( PORT );

	 memset(address.sin_zero, '\0', sizeof address.sin_zero);
}

Server::~Server() {

}

char* Server::parse(char line[], const char symbol[])
{
	char * token = strtok(line, symbol);

	token = strtok(NULL, " ");
	return token;
}

void Server::startServer(){
	const char* errorMessage = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 20\n\n404 Error, Not Found";

	// Creating socket file descriptor
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
	    perror("Error in socket() method");
	    exit(EXIT_FAILURE);
	}

	if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address))<0) {
	    perror("Error in bind() method");
	    exit(EXIT_FAILURE);
	}

	if (listen(serverSocket, 10) < 0) {
	    perror("Error in listen() method");
	    exit(EXIT_FAILURE);
	}

	while(true) {
	    printf("=====Waiting for new connection=====\n");
	    if ((newClientSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t*)&addressLength))<0) {
	        perror("Error in accept() method");
	        exit(EXIT_FAILURE);
	    }

	    char clientBuffer[30000] = {0};
	    readFromClient = read( newClientSocket , clientBuffer, 30000);
	    printf("%s\n", clientBuffer);
	    char *parse_string = parse(clientBuffer, " ");  //Get path requested by client
	    printf("Client ask for path: %s\n", parse_string);

	    int errorCode = 404;
	    string content = "<h1>404 Not Found</h1>";

		string fileName;
		if (string(parse_string) == "/") {
			fileName = "./index.html";
		}
		else {
			fileName = string(".") + string(parse_string);
		}
	    
	    // Open document in local file system
	    ifstream readFile(fileName);
		
	    // Check if opened and if so, grab the entire contents
	    if (readFile.good()) {
	        
	        string str((istreambuf_iterator<char>(readFile)), istreambuf_iterator<char>());
	        content = str;
	        errorCode = 200;
		    
	        ostringstream responseToClient;
	        responseToClient << "HTTP/1.1 " << errorCode << " OK\r\n";
	        responseToClient << "Cache-Control: no-cache, private\r\n";
	        responseToClient << "Content-Type: text/html\r\n";
	        responseToClient << "Content-Length: " << content.size() << "\r\n";
	        responseToClient << "\r\n";
	        responseToClient << content;

	        string output = responseToClient.str();
	        int size = output.size() + 1;

	        write(newClientSocket, output.c_str(), size);

	    }
		else{
	        write(newClientSocket , errorMessage, strlen(errorMessage));
	    }
	    readFile.close();
	    close(newClientSocket);
	}
}

