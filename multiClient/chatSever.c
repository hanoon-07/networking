#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 3003
#define BUFFER_SIZE 100

void handle_client(int client_sock) {
    char buf[BUFFER_SIZE];
    int k;

    while (1) {
        k = recv(client_sock, buf, BUFFER_SIZE, 0);
        if (k <= 0) {
            printf("Client disconnected or error in receiving.\n");
            break;
        }

        printf("Message from client: %s", buf);
        send(client_sock, buf, k, 0);
    }

    close(client_sock);
    exit(0);
}

int main() {
    int sock_desc, client_sock;
    struct sockaddr_in server, client;
    socklen_t len;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        perror("Error in socket creation");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("Error in binding");
        close(sock_desc);
        exit(1);
    }

    if (listen(sock_desc, 5) == -1) {
        perror("Error in listening");
        close(sock_desc);
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        len = sizeof(client);
        client_sock = accept(sock_desc, (struct sockaddr*)&client, &len);
        if (client_sock == -1) {
            perror("Error in accepting connection");
            continue;
        }

        printf("Client connected.\n");

        if (fork() == 0) {
            close(sock_desc);
            handle_client(client_sock);
        }
        close(client_sock);
    }

    close(sock_desc);
    return 0;
}
