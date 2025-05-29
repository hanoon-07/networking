#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

int main(){
    
    int sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in server;
    socklen_t length = sizeof(server);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(3000);


    char buf[100];

    while (1)
    {
        printf("type get to get the time:");
        scanf("%s", buf);
        sendto(sock_desc, buf, strlen(buf),0, (struct sockaddr*)&server, length);
        recvfrom(sock_desc, buf, sizeof(buf), 0, NULL, NULL);
        printf("\n%s", buf);
       
    }
    


}