#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/select.h>

#define PORT 8080
//#include <pthread.h>

int buffer_message(char * message);
int find_network_newline(char * message, int inbuf);
#define COMPLETE 0
#define BUF_SIZE 1024

static int inbuf; // how many bytes are currently in the buffer?
static int room; // how much room left in buffer?
static char *after;

int buffer_message(char * message){

    int bytes_read = read(STDIN_FILENO, after, 256 - inbuf);
    short flag = -1; // indicates if returned_data has been set 
    inbuf += bytes_read;
    int where; // location of network newline

    // Step 1: call findeol, store result in where
    where = find_network_newline(message, inbuf);
    if (where >= 0) { // OK. we have a full line

        // Step 2: place a null terminator at the end of the string
        char * null_c = {'\0'};
        memcpy(message + where, &null_c, 1); 

        // Step 3: update inbuf and remove the full line from the clients's buffer
        memmove(message, message + where + 1, inbuf - (where + 1)); 
        inbuf -= (where+1);
        flag = 0;
    }

    // Step 4: update room and after, in preparation for the next read
    room = sizeof(message) - inbuf;
    after = message + inbuf;

    return flag;
}

int find_network_newline(char * message, int bytes_inbuf){
    int i;
    for(i = 0; i<inbuf; i++){
        if( *(message + i) == '\n')
        return i;
    }
    return -1;
}


//void *connection_handler(void *);
int main(int argc, char const* argv[])
{
	//printf("1\n");
	int server_fd, client_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1, *new, pid;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	
	
//set up variables for select()
fd_set all_set, r_set;
int maxfd = server_fd + 1;
//printf("1.1\n");
FD_ZERO(&all_set);
//printf("2\n");
//FD_SET(0, &all_set); 
//printf("3\n");
//FD_SET(server_fd, &all_set);
//printf("4\n");
r_set = all_set;
struct timeval tv; tv.tv_sec = 2; tv.tv_usec = 0;

//set the initial position of after
after = buffer;


	//char* hello = "Message recevied from server!";
	//char* hello = NULL;
	//char hello[1024] = { 0 };
	//int i = 0, j = 0;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	FD_SET(0, &all_set); 
	FD_SET(server_fd, &all_set);
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("waiting for client to receive!!.... \n");
	while (1)
	{
		
		r_set = all_set;
	    	//check to see if we can read from STDIN or sock
	    	select(maxfd, &r_set, NULL, NULL, &tv);
		
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		
		if(FD_ISSET(server_fd, &r_set)){
        		//Receive a reply from the server
			if( recv(server_fd , buffer , 1024 , 0) < 0)
			{
			    puts("recv failed");
			    //break;
			}

		printf("\nClient Reply: %s\n", buffer);
		buffer[0]='\0';

	  	}
    
    
		//bzero(buffer, 1024);
		/*valread = recv(new_socket, buffer, sizeof(buffer), 0);
		if (valread < 0)
		{
			printf("received failed from client to server\n");
		}
		printf("%s - buffer\n", buffer);*/
		
		const char delim[] = " ";
		char *hello;
		char *inputCopy = malloc(255 * sizeof(char));
		strcpy(inputCopy, buffer);
		char * ptr = strtok(inputCopy, delim);
		//hello = strtok(NULL, delim);
		after = strtok(NULL, delim);
		memset(buffer, 0, sizeof(buffer));
		/*char * token = strtok(buffer, " ");
		while( token != NULL ) {
      			//printf( " %s\n", token ); //printing each token
      			token = strtok(NULL, " ");
      			printf( " %s\n", token ); //printing each token
      			//strcpy(hello, token);
   		}*/
   		
		printf("%s - hello\n", hello);
    		/*int valsend = send(new_socket, hello, strlen(hello), MSG_OOB);
    		if (valsend < 0)
		{
			printf("send failed from server to client\n");
		} 
		memset(hello, 0, sizeof(hello));*/
		
		if(FD_ISSET(0, &r_set)){

			if(buffer_message(hello) == COMPLETE){
			    //Send some data
			    if(send(server_fd, hello, strlen(hello) + 1, 0) < 0)
			    {
				puts("Send failed");
				return 1;
			    }

			    //puts("Enter message:");
			}
		    }
    
    
    		close(client_fd);
	}
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
