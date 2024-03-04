/*
 * Server.hpp
 *
 *  Created on: Feb 17, 2024
 *      Author: Tyre Sheffield, Shep Harper
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_
#include <stdio.h>

#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>


#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>

#include <istream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <iterator>

using namespace std;
#define PORT 60010

class Server {
public:
	Server();
	~Server();
	char *parse(char line[], const char symbol[]);
	void startServer();
	
private:
	int serverSocket, newClientSocket;
	long readFromClient;
	struct sockaddr_in address;
	int addressLength;
	
};

#endif /* SERVER_HPP_ */
