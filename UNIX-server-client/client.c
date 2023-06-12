#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include <sys/un.h>
#include <signal.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>

#define SIZE 6000

#define SERVER "server.sock"
#define SOCKET_PATH "/tmp/resol.sock"

int main()
{
	int e;

	int sockfd;
	FILE *fp, *fd;
	char *filename = "recv_2.txt";
	socklen_t addr_size;
	//int flag = 0;
	char data[SIZE] = {0};
	char line[SIZE];
	char buffer[SIZE] = {0};
	int flag = 0;
	
	
	/*while(1)
	{*/
		sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			perror("error in socket creation");
			exit(1);
		}

		printf("Server socket created succefully\n");
		
		struct sockaddr_un addr;
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, "/tmp/mysocket");
		int connect_status = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
		if (connect_status < 0)
		{
			printf("errno is %d\n", errno);
			if (errno == EACCES)
				printf("error in EACCES\n");
			else if (errno == EPERM)
				printf("error in EPERM\n");
			else if (errno == EADDRINUSE)
				printf("error in EADDRINUSE\n");
			else if (errno == EADDRNOTAVAIL)
				printf("error in EADDRNOTAVAIL\n");
			else if (errno == EAFNOSUPPORT)
				printf("error in EAFNOSUPPORT\n");
			else if (errno == EAGAIN)
				printf("error in EAGAIN\n");
			else if (errno == EALREADY)
				printf("error in EALREADY\n");
			else if (errno == EBADF)
				printf("error in EBADF\n");
			else if (errno == ECONNREFUSED)
				printf("error in ECONNREFUSED\n");
			else if (errno == EFAULT)
				printf("error in EFAULT\n");
			else if (errno == EINPROGRESS)
				printf("error in EINPROGRESS\n");
			else if (errno == EINTR)
				printf("error in EINTR\n");
			else if (errno == EISCONN)
				printf("error in EISCONN\n");
			else if (errno == ENETUNREACH)
				printf("error in ENETUNREACH\n");
			else if (errno == ENOTSOCK)
				printf("error in ENOTSOCK\n");
			else if (errno == EPROTOTYPE)
				printf("error in EPROTOTYPE\n");
			else if (errno == ETIMEDOUT)
				printf("error in ETIMEDOUT\n");
			perror("error in connection");
			exit(1);
		}

		printf("connected to server\n");
	while(1)
	{ 	
		fd = fopen(filename, "r");
		if (fd == NULL)
		{
		  	perror("error in reading file");
			exit(1);
		}
	 
		//dup2(fd, STDOUT_FILENO);
		//printf("%d - dup\n", STDOUT_FILENO);
		/*if (close(fd) != 0)
        		fprintf(stderr," Error: Failed to close command stream \n");*/
		if (flag)
		printf("before while loop\n");
			
		while (fgets(data, sizeof(data), fd) != EOF)
		{
			//printf("%s - command\n", data);
			if (flag)
			printf("inside while loop\n");
			//strcpy(data, buffer);
			//printf("%s - data \n", data);
				
			int len = strlen(data) - 1;
		
			if (data[len] == '\n')
				data[len] = '\0';
				
			if (flag)
			printf("before send\n");
			
			int send_status = send(sockfd, data, sizeof(data), 0);
			
			if (send_status < 0)
			{
				perror("send_status");
			}
			memset(&data, 0, sizeof(data));
			if (flag)
			printf("after send\n");
			
			memset(&buffer, 0, sizeof(buffer));
			int recv_status = recv(sockfd, buffer, sizeof(buffer), 0);
			
			if (recv_status < 0)
			{
				perror("recv_status");
			}
			
			if (flag)
			printf("after recv\n");
			
			printf("%s", buffer);
			/*while ( fgets( buffer, sizeof buffer, NULL))

	  		{

	    			printf("%s", buffer);

	  		}*/
	  		if (flag)
	  		printf("after while line\n");

	  		//memset(&buffer, 0, sizeof(buffer));
		}
	}

	
}
