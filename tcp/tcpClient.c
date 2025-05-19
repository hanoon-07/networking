#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   // Required for inet_addr()

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unistd.h"



int main() {
	char buf[100];
	int k;

	char reve[100];

	int sock_desc;
	struct sockaddr_in server;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);

	if(sock_desc==-1)
		printf("Error in socketcreation");

	server.sin_family=AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	server.sin_port=3003;
	k=connect(sock_desc,(struct sockaddr*)&server,sizeof(server));
	
	
	if(k==-1)
		printf("Error in connecting to server");

	while(1){
		printf("\n Enter the data to be send:");


		fgets(buf,100,stdin);

		k=send(sock_desc,buf,100,0);
		if(strcmp(buf,"quit")==0){
			break;
		}


		recv(sock_desc,reve,100,0);
		printf("String from server: %s",reve);
	}


	close(sock_desc);
	return 0;
}

