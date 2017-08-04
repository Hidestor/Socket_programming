/*This sample program creates a simple TCP server using socket which prints "Hello to the world of socket programming!!"
as soon as the client connects to the server*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h> // ntohs,ntohl,htons,htonl
#include<errno.h> // perror

int main(){
	int sock,cli,sent;
	struct sockaddr_in server, client;
	unsigned int len;
	char mesg[] = "Hello to the world of socket programming!!";
	
	if((sock = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(-1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(10002);
	server.sin_addr.s_addr = INADDR_ANY;
	//alternative to bzero is memset
	bzero(&server.sin_zero,0);//The bzero() function sets the first n bytes of the area starting at s to zero (bytes containing '\0').

	len = sizeof(struct sockaddr_in);
	
	if((bind(sock, (struct sockaddr *)&server,&len))==-1){
		perror("bind");
		exit(-1);
	
	}
	
	if(listen(sock,5)==-1){
		perror("listen");
		exit(-1);
	}
	
	while(1){
		if((cli == accept(sock,(struct sockaddr *)&client, len))==-1){
			perror("accept");
			exit(-1);
		
		}
		
		sent = send(cli,mesg,strlen(mesg),0);
		printf("Sent %d bytes to client : %s\n",sent,inet_ntoa(client.sin_addr))	;		
	
		close(cli);
	}

}
