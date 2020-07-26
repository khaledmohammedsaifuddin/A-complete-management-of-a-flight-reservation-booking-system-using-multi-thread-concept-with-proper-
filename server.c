#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "application.c"

#define PORT 4000

void *myThreadFun(void *vargp);
void *Thread(void *vargp);
void create_customer_record(int newSocket);
int count=0;

pthread_t thread_id; 
pthread_t thread;
int sockfd, ret;
struct sockaddr_in serverAddr;

int newSocket;
struct sockaddr_in newAddr;

socklen_t addr_size;

char buffer[1024];
pid_t childpid;

char* welcome = "Welcome!!!";
int trigger = 0;
int main(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 200) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}
	
	int* xyz;
	pthread_create(&thread_id, NULL, myThreadFun, NULL); 
	//printf("Debug print -----------------------\n");

	pthread_join(thread_id,&xyz);
	//printf("---------------%d",*xyz); 

	close(newSocket);
	return 0;
}

void *myThreadFun(void *vargp) 
{ 
	int* xyz;
	int* abc=(int*)malloc(sizeof(int));
	*abc=1;
    while(1){
		pthread_create(&thread, NULL, Thread, NULL); 
		pthread_join(thread,&xyz);

		newSocket = *xyz;
		//printf("-------------------%d",newSocket);
		
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
				recv(newSocket, buffer, 1024, 0);
				//printf("New Socket:%d from client\n",newSocket);
				if(strcmp(buffer, "5:exit") == 0){
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}else{
					if(trigger == 0){strcpy(buffer,"");trigger=1;}
					printf("Client: %s\n", buffer);
					//execute();
					send(newSocket, welcome, strlen(welcome),0);
					bzero(buffer,sizeof(buffer));
				}
			}
		}

	}
	return abc;
}

void *Thread(void *vargp) 
{
int* abc=(int*)malloc(sizeof(int));

*abc = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
printf("Thread %d has started\n",++count);
return abc;

}