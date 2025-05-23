#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 1024

void handle_client(int client_sock) {
    char filename[100], buffer[BUF_SIZE];
    pid_t pid = getpid();

    while (1) {
        int bytes = recv(client_sock, filename, sizeof(filename), 0);
        if (bytes <= 0) {
            printf("[PID %d] Client disconnected.\n", pid);
            break;
        }
        filename[bytes] = '\0';  // Null terminate

        printf("[PID %d] Requested file: %s\n", pid, filename);

        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            snprintf(buffer, BUF_SIZE, "Server PID: %d\nFile '%s' not found.\n", pid, filename);
            send(client_sock, buffer, strlen(buffer), 0);
            send(client_sock, "__END__", strlen("__END__"), 0);
        } else {
            snprintf(buffer, BUF_SIZE, "Server PID: %d\nFile content:\n", pid);
            send(client_sock, buffer, strlen(buffer), 0);

            while (fgets(buffer, BUF_SIZE, fp) != NULL) {
                send(client_sock, buffer, strlen(buffer), 0);
            }
            fclose(fp);

            // Send end-of-file marker
            send(client_sock, "__END__", strlen("__END__"), 0);
        }
    }

    close(client_sock);
    exit(0);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4000);

    bind(server_sock, (struct sockaddr*)&server, sizeof(server));
    listen(server_sock, 10);

    printf("Server listening on port 4000...\n");

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr*)&client, &client_len);
        printf("New client connected.\n");

        if (fork() == 0) {
            close(server_sock);
            handle_client(client_sock);
        } else {
            close(client_sock);
        }
    }

    close(server_sock);
    return 0;
}
