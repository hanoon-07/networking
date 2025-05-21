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

    int i=0;
    char buf[100]={1,2,3};
    char msg[100];

    struct boo{
        char name[100];
    };

    struct boo me;
    strcpy(me.name,"hanoon");
    while (i<1)
    {
        // printf("type what do you want to send to server");
        // scanf("%s",buf);
        if(sendto(sock,&me,sizeof(me),0,(struct sockaddr*)&server,sizeof(server))<0){
            printf("sending failed");
        }
        
        if(recvfrom(sock,msg,sizeof(msg),0,NULL,NULL)<0){
            printf("receiving failed");
        }

        printf("%s",msg);


        memset(buf,0,sizeof(buf));
        memset(msg,'\0',sizeof(msg));
        i++;
    }
    close(sock);

}

