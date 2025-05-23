#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <server-ip>\n", argv[0]);
        return 1;
    }

    int sock;
    struct sockaddr_in server;
    char filename[100], buffer[BUF_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(4000);
    inet_pton(AF_INET, argv[1], &server.sin_addr);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    while (1) {
        printf("\nEnter filename to request (or type 'exit' to quit): ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        if (strcmp(filename, "exit") == 0)
            break;

        send(sock, filename, strlen(filename), 0);

        printf("\n----- Server Response -----\n");
        while (1) {
            int bytes = recv(sock, buffer, BUF_SIZE - 1, 0);
            if (bytes <= 0) {
                printf("Server disconnected.\n");
                close(sock);
                return 1;
            }
            buffer[bytes] = '\0';

            if (strstr(buffer, "__END__")!=NULL)
                break;

            printf("%s", buffer);
        }
        printf("----------------------------\n");
    }

    close(sock);
    return 0;
}
