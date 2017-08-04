#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h> // perror
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define ERROR -1
#define MAX_CLIENTS 2 //max no of clients in queue
#define MAX_DATA 1024

int main(int argc,char **argv){
	struct sockaddr_in server,client;
	int sock;
	int new; //for descriptor for client
	int sockaddr_len = sizeof(struct sockaddr_in);
	int data_len;
	char data[MAX_DATA];
	
	if((sock = socket(AF_INET,SOCK_STREAM,0))== ERROR){
		perror("server socket: ");
		exit(-1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;//to listen on all interfaces on our host(local machine) on this given port
	bzero(&server.sin_zero,0);
	
	if(bind(sock,(struct sockaddr *)&server,sockaddr_len)==ERROR){
		perror("bind: ");
		exit(-1);
	}
	
	if((listen(sock,MAX_CLIENTS))==ERROR){
		perror("listen: ");
		exit(-1);
	}	
	
	while(1){
	//accept is a blocking call
	if((new = accept(sock,(struct sockaddr *)&client, &sockaddr_len))==ERROR){
		perror("accept");
		exit(-1);
	}
	
	printf("New client connected from port no %d and IP is %s \n",ntohs(client.sin_port),inet_ntoa(client.sin_addr));
	
	data_len = 1;
	while(data_len){
	
		data_len = recv(new, data, MAX_DATA, 0);
		if(data_len){
			send(new,data,data_len,0);
			data[data_len]='\0';
			printf("Sent mesg; %s",data);
		}
	}
	
	printf("Client disconneted\n");
	close(new);
	}
close(sock);	
}
