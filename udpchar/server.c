#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(){

    int sock=socket(AF_INET,SOCK_DGRAM,0);


    struct sockaddr_in server;

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3003);

    bind(sock,(struct sockaddr*)&server,sizeof(server));

    struct sockaddr_in client;
    int len=sizeof(client);


    char buf[100];
    char msg[100];

    struct boo{
        char name[100];
    };

    struct boo me;
    while (1)
    {
        if(recvfrom(sock,&me,sizeof(me),0,(struct sockaddr*)&client,&len)<0){
            printf("receiving failed\n");
        }
        // printf("%s\n",buf);
        // fflush(stdout);
        printf("%s",me.name);
        printf("\n");
        strcpy(msg,"hello from server\n");
        if(sendto(sock,msg,sizeof(msg),0,(struct sockaddr*)&client,len)<0){
            printf("sending failed");
        }
       
        memset(buf,'\0',sizeof(msg));

       
    }
    close(sock);

}

