#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>


int main() {

    int sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = 5000;

    bind(sock_desc, (struct sockaddr*)&servAddr, sizeof(servAddr));
    listen(sock_desc, 5);
    printf("Server is listening at port 5000!\n");

    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);
    int temp_sock = accept(sock_desc, (struct sockaddr*)&clientAddr, &len);
    printf("Client connected!\n");

    int seq = 1;
    int n;
   
    char d;
    while(1) {
        // read(temp_sock, &d, 1);
        read(temp_sock, &n, sizeof(int));
       
        //printf("char: %c, int: %d\n", d, n);
        
        // write(client, &d, 1);
        // write(client, &n, sizeof(int));
        // printf("%d", n);
       
        if(n != seq) {
            printf("Discarded data %d\n", n); //nothig send to the client
        } else {
            int k = rand();
            if(k % 3 == 0) {
                printf("Error! (coruption in %d)\n", n);
                char c = 'c';
                write(temp_sock, &c, 1); 
                write(temp_sock, &seq, sizeof(int)); 
            } else {
                printf("Data recieved %d(success send ack)\n", 1); //send the ack
                char a ='a';
                write(temp_sock, &a, 1);
                write(temp_sock, &n, sizeof(int));
                seq++; //send the next expected frame
            }
        }
        sleep(1);
    }

    return 0;
}