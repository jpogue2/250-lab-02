/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     * argc and *argv[] are command line arguments. They allow the user to provide
     * inputs to the main() function without using individual cin statements. argc is an
     * integer that contains the number of arguments, and *argv[] is an array of char*'s 
     * which contains the actual arguments.
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     * Source: ChatGPT
     * A UNIX file descriptor is a unique reference integer used by the OS to open a file
     * when a program requests to open it. A file descriptor table is a way of organizing
     * the file descriptors so that the OS can properly link files and programs.
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     * A struct is a "suitcase" that packages together many variables into a single object. 
     * In this example, the sockaddr_in struct has data members serv_addr and cli_addr.
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     * Source: ChatGPT
     * socket() has three input parameters. The first input parameter is the type of address.
     * In this case, the AF_INET address family is used. The second input parameter is the 
     * type of socket. The last input parameter is the protocol to be used with the socket.
     * socket() returns the socket descriptor of the new socket.
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     * Source: ChatGPT
     * bind() has three input parameters. The first input parameter is the socket descriptor
     * of the socket being used (created above using socket()). The second input
     * parameter is a pointer to a sockaddr struct which contains the address of the 
     * server to be used. The third input parameter is the length of the address.
     * listen() has two input parameters. The first is the socket descriptor returned by
     * socket(). The second input parameter is an integer that signifies the maximum
     * number of communications that can be backlogged on the socket at any given time.
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        * while(1) ensures that the code within the while loop executes forever. Due
        * to the way the error() function has been written, the program will be terminated immediately
        * if any of the simultaneous connections have errors. Therefore, all connections will fail if only
        * one receives an error. 
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         * Source: ChatGPT
         * The fork() function basically duplicates execution of the file into two processes:
         * a child process and a parent process. These two processes can occur simultaneously,
         * allowing the program to perform multiple tasks (on multiple items) at once.
         * Here, this is helpful so that every connection enters a "separate" while loop.
         * Therefore, if one connection cannot be read or written to, it will not affect
         * the other connections.
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 * A system call is a request sent to the Linux Kernel to carry out some command on the hardware. The 
 * existence of system calls allows for a level of protection between software and hardware, so that software
 * must work through the Kernel in order to make hardware changes.
 */
