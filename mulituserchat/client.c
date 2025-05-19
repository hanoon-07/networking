#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>


char buf[100];
int sock_desc;

void* listenthread(){

    while(1){
        int bytes_received = read(sock_desc, buf, 100);
        if (bytes_received <= 0) { 
            // Server disconnected or error occurred
            printf("\nServer disconnected. Exiting...\n");
            exit(0);
        }

        printf("\n%senter your message:", buf);
        fflush(stdout);

        for(int i = 0;i < 100;i++) {
            buf[i] = '\0';
        }
    }
    return NULL;

}


int main(int argc, char* argv[]){
    int k;
   
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(3000);

    inet_pton(AF_INET, argv[1], &server.sin_addr);
    printf("enter your name:");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0';

    int c=connect(sock_desc, (struct sockaddr*)&server, sizeof(server));
    send(sock_desc, buf, strlen(buf), 0);

    pthread_t tempthread;
    pthread_create(&tempthread, NULL, listenthread, NULL);
    pthread_detach(tempthread);
    
    while(1){
        printf("enter your message:");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        send(sock_desc, buf, strlen(buf), 0);

        for(int i = 0;i < 100;i++) {
            buf[i] = '\0';
        }
    }


}


