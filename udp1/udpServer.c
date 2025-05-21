#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int sock_desc;
struct sockaddr_in client;
socklen_t cliaddr = sizeof(client);
char buf[100];

void* recvthread(){
	char buf[100];
	while (1)
	{
		recvfrom(sock_desc, buf, sizeof(buf),0, (struct sockaddr*)&client, &cliaddr);
		printf("\nrecieved %s from client\nenter your message:", buf);
		fflush(stdout);

		for (int i = 0; i < 100; i++)
		{
			buf[i]='\0';
		}
		
	}
	return NULL;
}

int main(){

	sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(3000);

	bind(sock_desc, (struct sockaddr*)&server, sizeof(server));

	pthread_t tempthread;

	pthread_create(&tempthread,NULL,recvthread,NULL);
	pthread_detach(tempthread);
	while (1)
	{
		printf("enter your message:");
		fgets(buf, 100, stdin);
		buf[strcspn(buf,"\n")]='\0';

		sendto(sock_desc, buf, strlen(buf), 0, (struct sockaddr*)&client, cliaddr);
		for (int i = 0; i < 100; i++)
		{
			buf[i]='\0';
		}
	}

	
	

}