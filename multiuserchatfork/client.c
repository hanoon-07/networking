#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


int sock;

void* listenthread(){
    char buf[100];
    while (1)
    {
        recv(sock,buf,sizeof(buf),0);
        printf("hey ive recieved\n");
        printf("\n%s",buf);
        fflush(stdout);
        memset(buf,'\0',sizeof(buf));
    }

    return NULL;
    
}


int main(int argc, char* argv[]){
    sock = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(3003);
    inet_pton(AF_INET,argv[1],&server.sin_addr);

    connect(sock,(struct sockaddr*)&server,sizeof(server));
    printf("enter your name");
    char name[100];scanf("%s",name);
    send(sock,name,sizeof(name),0);

    
    pthread_t t;
    pthread_create(&t,NULL,listenthread,NULL);
    pthread_detach(t);
    
    char buf[100];
    while(1){

        printf("enter your message");
        scanf("%s",buf);
        send(sock,buf,sizeof(buf),0);
        memset(buf,'\0',sizeof(buf));

    }


}