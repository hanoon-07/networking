#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>


struct clients{
    int socket;
    char name[100];
}clientsArr[100];

char buf[100];
int count = 0;

void broadcast(char buf[], char name[], int socket){
    char message[100];
    strcpy(message, name);
    strcat(message, " sent ");
    strcat(message, buf);
    strcat(message, "\n");


    for(int i = 0;i < count;i++) {
        if(clientsArr[i].socket == socket) continue;
        else {
            send(clientsArr[i].socket, message, strlen(message), 0);
        }
    }
    
}

void* clientHandle(){
    int index = count - 1 ;
    int socket = clientsArr[index].socket;
    char name[100];
    strcpy(name,clientsArr[index].name);

    while(1){
        read(socket, buf, 100); 
        broadcast(buf,name,socket);
        for(int i = 0;i < 100;i++) {
            buf[i] = '\0';
        }
    }

    return NULL;

}


int main(){ 
    int sock_desc;
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(sock_desc, (struct sockaddr*)&server, sizeof(server));
    listen(sock_desc, 4);

    int tempsock_desc;
    pthread_t tempthread;

    while(1){
        tempsock_desc = accept(sock_desc, NULL, NULL);
        printf("New client connected!\n");
        clientsArr[count].socket = tempsock_desc;

        read(tempsock_desc, buf, 100);
        //clientsArr[count].name = buf; not allowed you are assigning pointer there
        strcpy(clientsArr[count].name, buf);

        for(int i = 0;i < 100;i++) {
            buf[i] = '\0';
        }


        pthread_create(&tempthread, NULL, clientHandle, NULL);
        pthread_detach(tempthread);

        count++;

    }
    
    close(sock_desc);
    return 0;
}
