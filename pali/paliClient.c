#include"sys/socket.h"
#include"netinet/in.h"
#include"stdio.h"
#include"string.h"
#include"stdlib.h"


int main() {
	char buf[100];
	int k;

	char reve[100];

	int sock_desc;
	struct sockaddr_in client;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);

	if(sock_desc==-1)
		printf("Error in socketcreation");

	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=4000;
	k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
	
	if(k==-1)
		printf("Error in binding");
	k=listen(sock_desc,5);
	//if(k==-1)
	//	printf("Error in connecting to server");

	while(1){
		printf("\n Enter the data to be send:");


		fgets(buf,100,stdin);

		k=send(sock_desc,buf,100,0);
		if(strcmp(buf,"quit")==0){
			break;
		}


		recv(sock_desc,reve,100,0);
		printf("Result(is-palindrome): %s",reve);
	}
	close(sock_desc);
	return 0;
}

