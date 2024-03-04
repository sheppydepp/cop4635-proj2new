COP4635 - Systems & Networks II - Project 2
Professor Dr.Mishra 
Team Members: Tyre Sheffield, Shep Harper

Included Files: img.jgp, index.html, testPresence.html, server_main.cpp, server.hpp, 
server.cpp, makefile, client_main.cpp

=== Compilation Directions ===
This project was tested sucessfully using Windows Subsystem for Linux (WSL). Two different WSL were
running simulatanousely, one for running the server and one for running the client.
To compile, navigate to the folder containing the project files.
In one WSL, Run the command 'make server'. After compilation finishes, the server portion of the
project can be initiated by running the command './server'
In the second WSL, Run the command 'make client'. After compilation finishes, the client portion
of the project can be initiated by running the command:
 './client <hostaddress> 60010 /<file name>'  
For example, if a file name is "index.html", run the command: ./client <hostaddress> 60010 /index.html

=== During the Program ===
The server terminal will then display a message stating that the server is waiting for a new connection.
The client terminal will show a GET request to the server. It will then display the contents of requested file
including the HTTP protocol and content type and length.
The server terminal will show the GET request from the client along with the HTTP protocol. 

=== Accomplishments === 
The server WSL terminal sucessfuly shows any file requests being made by the client WSL terminal
showing interaction between the client and server.

=== Other Notes ===
The Port Number specified in our code is 60010.


