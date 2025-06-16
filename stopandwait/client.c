#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>


int main(){
    int sock_desc = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server;


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 5000;

    connect(sock_desc,(struct sockaddr*)&server,sizeof(server));

    int seq = 1;
    char a;
    while (1)
    {

        write(sock_desc,&seq,sizeof(int));
        printf("data %d sent\n", seq);
        read(sock_desc,&a,1);

        if(a == 'e'){
            printf("acknowledgement not recieved\n");
        }
        else{
            printf("acknowledgement recieved\n");
            seq++;
        }

        sleep(1);
    }
    
}


