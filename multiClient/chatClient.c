#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 3003
#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        return 1;
    }

    char *server_ip = argv[1];  // Get IP from command line
    char buf[BUFFER_SIZE];
    int sock_desc, k;
    struct sockaddr_in server;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        perror("Error in socket creation");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);  // Use provided IP
    server.sin_port = htons(PORT);

    k = connect(sock_desc, (struct sockaddr*)&server, sizeof(server));
    if (k == -1) {
        perror("Error in connecting to server");
        close(sock_desc);
        exit(1);
    }

    while (1) {
        printf("\nEnter message: ");
        fgets(buf, BUFFER_SIZE, stdin);

        send(sock_desc, buf, strlen(buf), 0);

        if (strcmp(buf, "quit\n") == 0) {
            break;
        }

        k = recv(sock_desc, buf, BUFFER_SIZE, 0);
        if (k <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        buf[k] = '\0';  // Null-terminate received string

        printf("Server response: %s", buf);
    }

    close(sock_desc);
    return 0;
}
