#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

int main(){
    int sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    bind(sock_desc, (struct sockaddr*)&server, sizeof(server));

    char buf[100];

    while (1)
    {
        recvfrom(sock_desc, buf, sizeof(buf), 0, (struct sockaddr*)&client, &len);
        if(strcmp(buf,"get")==0){
            time_t t = time(NULL);
            char* timestr = ctime(&t);
            sendto(sock_desc, timestr, strlen(timestr), 0,(struct sockaddr*)&client, len);
        }
    }


}