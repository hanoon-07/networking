#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


int count = 0;
int sock;

struct storage{
    char name[100];
    int isock;
}arr[100];


void broadcast(char buf[], char name[], int socket){
    char message[100];
    strcpy(message, name);
    strcat(message, " sent ");
    strcat(message, buf);
    strcat(message, "\n");


    for(int i = 0;i < count;i++) {
        if(arr[i].isock == socket) continue;
        else {
            printf("sent message to %s\n",arr[i].name);
            send(arr[i].isock, message, strlen(message), 0);
        }
    }
    
}


void handleclient(int sock){
    printf("client connected\n");
    char buf[100];
    recv(sock,buf,sizeof(buf),0);
    strcpy(arr[count-1].name,buf);
    arr[count-1].isock=sock;


    char msg[100];
    while(1){
        read(sock, msg, sizeof(msg)); 
        broadcast(msg,arr[count-1].name,arr[count-1].isock);
        memset(msg,'\0',sizeof(msg));
        memset(buf,'\0',sizeof(buf));
    }
}


int main(){
    sock = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(3003);
    server.sin_addr.s_addr = INADDR_ANY;



    bind(sock,(struct sockaddr*)&server,sizeof(server));
    listen(sock,5);


    while(1){
        int tempsock = accept(sock,NULL,NULL);
        count++;
        if(fork()==0){
            close(sock);
            handleclient(tempsock);
        }
        else{
            close(tempsock);
        }

    }




}





