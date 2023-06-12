#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<signal.h>
#include<sys/time.h>
#include <sys/types.h>
 //#include <sys/time.h>
#include <netdb.h>




#define SIZE 6000

#define SERVER "server.sock"

#define SOCKET_PATH "/tmp/resol.sock"  // master (connection) socket path
#define BACKLOG 20                     // maximum size of pending connections
#define BUFFER_SIZE 6000

#define MAX_CLIENTS 32

int main()
{
	int e;
	FILE *FileOpen, *fp;
	int flag = 0;
	char line[SIZE];

	//unlink(SOCKET_PATH);
	int sockfd, new_sock;
	socklen_t addr_size;
	char buffer[BUFFER_SIZE];
	char str[BUFFER_SIZE];

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("error in socket");
		exit(1);
	}

	printf("server created socket successfully\n");

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "/tmp/mysocket");
	
	int bind_status = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if (bind_status < 0)
	{
		perror("binding error");
		exit(1);
	}

	printf("binding done successfully\n");
	

	int listen_status = listen(sockfd, 5);
	if (listen_status < 0)
	{
		perror("error in listening");
		exit(1);
	}
	
	
		struct sockaddr_un client_addr;
		socklen_t client_addrlen = sizeof(client_addr);
		int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addrlen);
		
		printf("client accepted\n ");
	while (1)
	{	
		
		int recv_status = recv(clientfd, buffer, sizeof(buffer), 0);
		if (recv_status < 0)
		{
			perror("recv_status");
		}
		
		FileOpen = popen(buffer, "r");
		
		while ( fgets( line, sizeof line, FileOpen))

	  	{
	    		int send_status = send(clientfd, line, sizeof(line), 0);
			if (send_status < 0)
			{
				perror("send_status");
			}

	  	}
		
		
	}
	
	
	
	
	
}
