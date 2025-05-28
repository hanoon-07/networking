#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(){
    struct sockaddr_in server;

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=3003;

    int sock_desc=socket(AF_INET, SOCK_STREAM, 0);

    if(sock_desc<0){
        printf("socket creation failed bro");
    }


    int k = bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k<0){
        printf("the binding failed bro\n");
    }

    listen(sock_desc,5);

    int tempsock=accept(sock_desc,NULL,NULL);

    if(tempsock<0){
        printf("the temporary socket creation failed bro\n");
    }

    struct packet{
        int rollno;
        char name[100];
    };

    struct packet single;

    while(1){
        recv(tempsock,&single,sizeof(single),0);

        char buf[100];
        sprintf(buf, "the server says hi to %s", single.name);
        send(tempsock,buf,100,0);
        // memset(buf,'\0',sizeof(buf));
    }

}   