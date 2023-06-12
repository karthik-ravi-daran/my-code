// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/select.h>
#define PORT 8080

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


int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char* hello; // = "Hello from client";
	//char hello[1024] = {};
	char buffer[1024] = { 0 };
	int count = 0;
	
	fd_set all_set, r_set;
int maxfd = client_fd + 1;
//printf("1.1\n");
FD_ZERO(&all_set);
//printf("2\n");
//FD_SET(0, &all_set); 
//printf("3\n");
//FD_SET(server_fd, &all_set);
//printf("4\n");
r_set = all_set;
struct timeval tv; tv.tv_sec = 2; tv.tv_usec = 0;

after = buffer;


	/*if (argc < 2)
	{
		printf("For example : ./client message client1\n");
		exit(1);
	}*/
	printf("activating client\n");
	//sleep(1);
	while (1)
	{
		//printf("2\n");
		if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			printf("\n Socket creation error \n");
			return -1;
		}

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);

		// Convert IPv4 and IPv6 addresses from text to binary
		// form
		if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
				<= 0) {
			printf("\nInvalid address/ Address not supported \n");
			return -1;
		}

		if ((status= connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))< 0)
		{
			printf("\nConnection Failed \n");
			return -1;
		}
		
		FD_SET(0, &all_set); 
		FD_SET(client_fd, &all_set);
		//printf("Send message to server:\t");
	/*while (1)
	{*/
		//scanf("%[^\n]", hello);
		//printf("3\n");
		strcpy(hello, argv[1]);
		strcpy(buffer, argv[2]);
		//printf("message from %s %s \n", argv[1], argv[2]);
		strcat(hello, " ");
		strcat(hello, buffer);
		printf("%s\n", hello);
		
		if(FD_ISSET(0, &r_set)){

			if(buffer_message(hello) == COMPLETE){
			    //Send some data
			    if(send(client_fd, hello, strlen(hello) + 1, 0) < 0)
			    {
				puts("Send failed");
				return 1;
			    }

			    //puts("Enter message:");
			}
		    }
		/*int valsend = send(client_fd, hello, strlen(hello), MSG_OOB);
		if (valsend < 0)
		{
			printf("send failed from client to server\n");
		}
		memset(hello, 0, sizeof(hello));*/
		/*strcpy(buffer, argv[2]);
		send(client_fd, buffer, strlen(buffer), 0);*/
		//printf("%s message sent\n", hello);
		//sleep(5);
		//send(client_fd, hello, strlen(hello), 0);
    		//printf("Hello message sent\n");
    		//valread = read(client_fd, buffer, 1024);
    		
    		if(FD_ISSET(client_fd, &r_set)){
        		//Receive a reply from the server
			if( recv(client_fd , buffer , 1024 , 0) < 0)
			{
			    puts("recv failed");
			    //break;
			}

		printf("\nServer Reply: %s\n", buffer);
		buffer[0]='\0';

	  	}
	  	
    		/*valread = recv(client_fd, buffer, sizeof(buffer), 0);
    		if (valread < 0)
		{
			printf("received failed from server to client\n");
		}
    		printf("%s - %d\n", buffer, count++);
    		memset(buffer, 0, sizeof(buffer));*/
		//sleep(2);
		//close(client_fd);
	}
	// closing the connected socket
	close(client_fd);
	return 0;
}

