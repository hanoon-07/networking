#include "sys/socket.h"
#include "netinet/in.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"



int main() {

	char buf[100];
	socklen_t len;
	int sock_desc,temp_sock_desc;
	struct sockaddr_in server,client;
	sock_desc=socket(AF_INET, SOCK_STREAM, 0);

	if(sock_desc==-1){
		printf("Error in socket creation");
		exit(1);
	}

	

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3003;


	int k;
	k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	if(k==-1){
		printf("error in binding");
		close(sock_desc);
        exit(1);
	}

	k=listen(sock_desc,5);
	if(k==-1){
		printf("Error in listening");
		close(sock_desc);
        exit(1);
	}

	len=sizeof(client);
	temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
	//temp_sock_desc=accept(sock_desc,NULL,NULL); this also possible if no info of client that came is to be retrieved
	if(temp_sock_desc==-1){
		printf("error in temporary socket creation");
		close(sock_desc);
        exit(1);
	}


	while(1){

		k=recv(temp_sock_desc,buf,100,0);
		if(k==-1){
			printf("error in receiving");
			break;
		}

		printf("Message from client:%s",buf);
		
		if(strcmp(buf,"quit")==0){
			break;
		}


		int l=strlen(buf);
		
		

		for(int i = 0;i < l/2;i++){
			char temp = buf[i];
			buf[i] = buf[l-i-1];
			buf[l-i-1] = temp;
		} 


		send(temp_sock_desc,buf,100,0);
	}
	
	close(temp_sock_desc);
	close(sock_desc);
	return 0;
}

