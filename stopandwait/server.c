#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>

int main()
{
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 5000;

    bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    listen(sock_desc,5);

    int temp_sock = accept(sock_desc, NULL, NULL);

    int n;

    while (1)
    {
        read(temp_sock, &n, sizeof(int));

        int k = rand();
        if (k % 3 == 0)
        {
            char a = 'e';
            printf("error occured\n");
            write(temp_sock, &a, 1);
        }
        else
        {
            char a = 'a';
            printf("data %d received successfully\n", n);
            write(temp_sock, &a, 1);
        }

        sleep(1);
    }
}
