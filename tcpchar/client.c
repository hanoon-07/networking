#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;

    int sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_desc < 0)
    {
        printf("socket creation failed bro\n");
    }

    int k = connect(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k < 0)
    {
        printf("connection failed bro\n");
    }

    struct packet{
        int rollno;
        char name[100];
    }arr[100];

    arr[0].rollno=43;
    strcpy(arr[0].name,"hanoon");

    arr[1].rollno=65;
    strcpy(arr[1].name,"tom");

    int i=0;
    while (i<2)
    {
       
            char buf[100];
            send(sock_desc, &arr[i], sizeof(arr), 0);
            // memset(buf,'\0',sizeof(buf));
            recv(sock_desc, buf, 100, 0);
            printf("%s",buf);
            memset(buf,'\0',sizeof(buf));

            i++;
            
        
        
           

    }

           
}