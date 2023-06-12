#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <errno.h>
#include <sys/ioctl.h>


#define PORT 8080
//#include <pthread.h>

//#define MAX_CLIENTS 10
int flag = 0;

int recvtimeout(int s, char *buf, int len, int timeout)
{
    fd_set fds;
    int n;
    struct timeval tv;
    
    if (flag)
    printf("before FD_SET\n");
    
    // set up the file descriptor set
    FD_ZERO(&fds);
    FD_SET(s, &fds);
    
    if (flag)
    printf("after FD_SET\n");
    
    // set up the struct timeval for the timeout
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    
    if (flag)
    printf("after timeout\n");
    // wait until timeout or data received
    n = select(s+1, &fds, NULL, NULL, &tv);
    if (n == 0) return -2; // timeout!
    if (n == -1) return -1; // error
    
    if (flag)
    printf("after select\n");
    //printf("%d - n\n", n);

    // data must be here, so do a normal recv()
    return recv(s, buf, len, 0);
}

//void *connection_handler(void *);
int main(int argc, char const* argv[])
{
	int server_fd, client_fd, new_socket, valread, new_fd; //, client_socket[MAX_CLIENTS];
	struct sockaddr_in address;
	int opt = 1, *new, pid, sin_size, last_fd, n, i;
	int addrlen = sizeof(address);
	char *buffer = malloc(255 * sizeof(char));
	//int all_connections[MAX_CONNECTIONS];
	
	int count = 0;
	
	int count1;
	//int status = ioctl(server_fd, FIONREAD, &count1);
	char *hello = malloc(255 * sizeof(char));

	if (flag)
	printf("before socket\n");
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (flag)
	printf("after socket\n");
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	if (flag)
	printf("after setsockopt\n");
		 
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

	if (flag)
	printf("after bind\n");
		
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if (flag)
	printf("after listen\n");
		
	fcntl(last_fd, F_SETFL, O_NONBLOCK);
        fcntl(new_fd, F_SETFL, O_NONBLOCK);
        //fcntl(server_fd, F_SETFL, O_NONBLOCK);
	if (flag)
	printf("after fcntl\n");        
        
        
        
	printf("waiting for client to receive!!.... \n");
	while (1)
	{
	
	if (flag)
	printf("before memset\n"); 	
	
	    memset (buffer, 0, 256);
    	    memset (hello, 0, 256);

	if (flag)
	printf("after memset\n"); 
			
		sin_size = sizeof(struct sockaddr_in);
        			if ((new_fd = accept(server_fd, (struct sockaddr*)&address, \
        					(socklen_t*)&addrlen)) == -1) {
        					if (errno == EAGAIN || errno == EWOULDBLOCK)
        					{
        						printf("No clients available\n");
        						close(new_fd);
        						//continue;
        					}
        				perror("accept");
        			}


         			printf("server: got connection from %s\n", \
					 inet_ntoa(address.sin_addr)); 

				if (flag)
				printf("%d - %d\n", server_fd, last_fd);

				if (flag)
	    			printf("before recv - %s\n", buffer);

				
				
				
				n = recvtimeout(new_fd, buffer, sizeof(buffer), 10);
				//printf("%d - n from main\n");
	    			//n=recv(new_fd,buffer,sizeof(buffer),0);
	    			//printf("%d\n", n);
	    			
	    			if (flag)
	    			printf("after recv\n");
	    			
	    			/*if (errno != EWOULDBLOCK)
                     		{
					perror("  recv() failed");
					//close_conn = TRUE;
                     		} */
				if (n < 1){
					//printf("%d - %d\n", n, errno);
					if (errno == EAGAIN || errno == EWOULDBLOCK) 
					{
						printf("no data available\n");
						//printf("%s -  buffer\n", buffer);
						//memset(buffer, 0, sizeof(buffer));//close(new_fd);
						printf("%s -  buffer\n", buffer);
						continue;
					}
					else if (n == -2) 
					{ 
						printf("Timeout\n");// timeout occurred 
					}
					else 
					{
            					// Fatal error, handle appropriately
            					fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
						perror("recv - non blocking \n");
	    					//printf("Round %d, and the data read size is: n=%d \n",i,n);
        				}
				}
				else{
					if (flag)
					printf("else\n");
					
					
			        	buffer[n] = '\0';
	    				printf("The string is: %s - %d\n",buffer, count++);
	    				
	    				
	    				const char delim[] = " ";
					//char *hello;
					char *inputCopy = malloc(255 * sizeof(char));
					strcpy(inputCopy, buffer);
					char * ptr = strtok(inputCopy, delim);
					hello = strtok(NULL, delim);
					
					if (flag)
					printf("before send\n");
					
					
            				if (send(new_fd, hello, sizeof(hello), 0) == -1)
                				perror("send");
                			
                			int status = ioctl(server_fd, FIONREAD, &count1);
                			printf("%d - ioctl\n",status);
				}
				//close(client_fd);
	}
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
