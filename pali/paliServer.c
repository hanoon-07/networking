#include"sys/socket.h"
#include"netinet/in.h"
#include"stdio.h"
#include"string.h"
#include"stdlib.h"


int main() {


	char buf[100];
	//char rev[j];
	socklen_t len;
	int sock_desc,temp_sock_desc;
	struct sockaddr_in server,client;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);

	if(sock_desc==-1)
		printf("Error in socketcreation");

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=4000;
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=4000;

	int k;
	k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	if(k==-1)
		printf("error in binding");
	k=listen(sock_desc,5);
	if(k==-1)
		printf("Error in listening");
	len=sizeof(client);
	temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
	if(temp_sock_desc==-1)
	printf("error in temporary socket creation");


	while(1){



		k=recv(temp_sock_desc,buf,100,0);
		if(k==-1)
		printf("error in receiving");
		printf("Message from client:%s",buf);
		
		if(strcmp(buf,"quit")==0){
			break;
		}


		int l=strlen(buf);
		l--;
		
		//for(int i=l-1;i>=0;i--){
		//	rev[j]=buf[i];
		//	j++;
		//}

		//printf("reverse of message is %s",rev);

		int flag = 0;
		for(int i = 0;i < l/2;i++){
			if(buf[i] != buf[l-i-1]) {
				flag++;
				break;
			}
		} 

		
		if(flag == 0){
			strcpy(buf, "true");			
		} else {
			strcpy(buf, "false");
		}

		send(temp_sock_desc,buf,100,0);
	}
	close(temp_sock_desc);
	return 0;
}

