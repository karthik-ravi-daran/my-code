// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char *hello = malloc(255 * sizeof(char));
	//char hello[1024] = {};
	char *buffer = malloc(255 * sizeof(char));
	int count = 0;
	
	int flag = 0;
	
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
		/*int valsend = send(client_fd, hello, strlen(hello), MSG_OOB);
		if (valsend < 0)
		{
			printf("send failed from client to server\n");
		}
		memset(hello, 0, sizeof(hello));
		
		//------------------------------------------------------------
		/*strcpy(buffer, argv[2]);
		send(client_fd, buffer, strlen(buffer), 0);
		//printf("%s message sent\n", hello);
		//sleep(5);
		//send(client_fd, hello, strlen(hello), 0);
    		//printf("Hello message sent\n");
    		//valread = read(client_fd, buffer, 1024);
    		
    		//-------------------------------------------------------------
    		
    		
    		valread = recv(client_fd, buffer, sizeof(buffer), 0);
    		if (valread < 0)
		{
			printf("received failed from server to client\n");
		}
    		printf("%s - %d\n", buffer, count++);
    		memset(buffer, 0, sizeof(buffer));*/
		//sleep(2);
		/*while (1){*/
		if (flag)
		printf("before send\n");
		
		
		if (send(client_fd, hello, sizeof(buffer), 0) == -1)
		      perror("send");
		//printf("In loop \n");
		//bzero(hello, 1024);
		
		
		
		if (flag)
		printf("before recv\n");
		
		//bzero(buffer, 1024);
		if (recv(client_fd, buffer, sizeof(buffer), 0) == -1)
			perror("recv");
			
		printf("%s - %d\n", buffer, count++);
		
	    //memset (buffer, 0, 256);
    	    //memset (hello, 0, 256);		

		close(client_fd);
		//shutdown(client_fd, SHUT_RDWR);	
	}
	//close(client_fd);
	//}
	// closing the connected socket
	//close(client_fd);
	return 0;
}

