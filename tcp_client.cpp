// Server side C/C++ program to demonstrate Socket programming 
// Here's some include statements that might be helpful for you
#include <string> 
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) 
{ 
	// check to see if user input is valid
	char socket_read_buffer[1024];
	
	// TODO: Fill out the server ip and port
	std::string server_ip = "localhost";
	std::string server_port = "3000";

	int opt = 1;
	int client_fd = -1;
	int n;

	// TODO: Create a TCP socket()
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	// Enable reusing address and port
	if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		return -1;
	}

	// Check if the client socket was set up properly
	if(client_fd == -1){
		printf("Error- Socket setup failed");
		return -1;
	}
	
	// Helping you out by pepping the struct for connecting to the server
	struct addrinfo hints;
	struct addrinfo *server_addr;
	// Ok so the hints struct is a certain size. This makes all of the memory that the hints struct
	// can POTENTIALLY use set to 0.
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	// This says to take the human-readable ip and port, combine them with hints, and put it in server
	// address
	getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints, &server_addr);

	// TODO: Connect() to the server (hint: you'll need to use server_addr)
	if (connect(client_fd, server_addr->ai_addr, server_addr->ai_addrlen) < 0) 
	{
		printf("ERROR connecting\n");
		return -1;
	}
	
	// TODO: Retreive user input
	printf("Please enter the message: ");
	bzero(socket_read_buffer, 1024);
	fgets(socket_read_buffer, 1023, stdin);
	
	
	// TODO: Send() the user input to the server
	n = send(client_fd, socket_read_buffer, strlen(socket_read_buffer), 0);
	//n = write(client_fd, socket_read_buffer, strlen(socket_read_buffer));
	if (n < 0)
	{
		printf("ERROR writing to socket\n");
		return -1;
	}
	
	// TODO: Recieve any messages from the server and print it here. Don't forget to make sure the string is null terminated!
	bzero(socket_read_buffer, 1024);
	n = read(client_fd, socket_read_buffer, 1023);
	if (n < 0)
	{
		printf("ERROR reading from socket\n");
		return -1;
	}
	printf("%s\n", socket_read_buffer);
	
	// TODO: Close() the socket
	close(client_fd);

	return 0; 
} 

