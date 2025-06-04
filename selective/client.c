#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

int wsize = 5;

int main()
{
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 5000;

    connect(sock_desc, (struct sockaddr *)&server, sizeof(server));

    int seq = 1;
    char s;

    int error_array[100];
    int error_count = 0;

    while (1)
    {
        int csize = 0;
        int ecount = error_count;
        int i = 0;
        while (i < ecount)
        {
            write(sock_desc, &error_array[i], sizeof(int));
            printf("data %d sent\n", error_array[i]);
            read(sock_desc, &s, 1);

            if (s == 'e')
            {
                i++; // skip this one, move to next
                continue;
            }

            printf("ack received\n");

            // Shift all remaining elements to the left
            for (int j = i; j < ecount - 1; j++)
            {
                error_array[j] = error_array[j + 1];
            }

            ecount--;      // one less element now
            error_count--; // update error count
            csize++;       // update whatever csize is tracking

            // Don't increment i — recheck current index
        }

        while (csize < wsize)
        {
            write(sock_desc, &seq, sizeof(int));
            printf("data %d sent\n", seq);
            read(sock_desc, &s, 1);

            if (s == 'e')
            {
                error_array[error_count++] = seq;
                printf("acknowledgement not recieved\n");
                seq++;
            }
            else
            {
                printf("ack received\n");
                seq++;
            }
            csize++;
        }
    }
}