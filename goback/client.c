#include <stdio.h>

#include <netinet/in.h>
#include <sys/types.h>

#include <pthread.h>

int seq = 1;
int w_size = 5;
int c_size = 0;
int error = 0;
int r_frame = 1;
int sock_desc;

void* recvData() {

    while(1) {
        int n;
        char d;
        read(sock_desc, &d, 1);
        read(sock_desc, &n, sizeof(int));
        //printf("%d\n", n);
        if(d == 'a') {
            printf("Data ack for %d\n", n);
            c_size--;
        } else if(d == 'c') {
            
            error = 1;
            r_frame = n;
            //printf("%d", r_frame);
        }
        sleep(1);
    }

    return NULL;
}

void* sendData() {

    char d = 'd';
    int n;


    while(1) {
        if(error == 1) { //error is set by the recvData upon recieving the 'c' frames
            error = 0;
            c_size = 0;
            seq = r_frame;
            printf("Corruption detected!(frame - %d) resend!\n", r_frame);
        }

        while(c_size < w_size) {
            // write(sock_desc, &d, 1);
            write(sock_desc, &seq, sizeof(int));
            printf("Send frame %d\n", seq);
            seq++;
            c_size++;
            sleep(1);
        }

    }

    return NULL;
}


int main() {

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = 5000;

    connect(sock_desc, (struct sockaddr*)&servAddr, sizeof(servAddr));
    printf("Connected to the server!\n");

    pthread_t recv;
    pthread_t sender;
    pthread_create(&recv, NULL, recvData, NULL);
    pthread_create(&sender, NULL, sendData, NULL);
    
    pthread_join(recv, NULL);
    pthread_join(sender, NULL);


    return 0;
}