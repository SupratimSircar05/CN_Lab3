#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int sock;
    struct sockaddr_in server;
    int server_reply[10];
    int number[10] = { 5, 4, 3, 8, 9, 1, 2, 0, 7, 6 }, i;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8880);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected");

    if (send(sock, &number, 10 * sizeof(int), 0) < 0) {
        puts("Send failed");
        return 1;
    }

    if (recv(sock, &server_reply, 10 * sizeof(int), 0) < 0) {
        puts("recv failed");
        return 0;
    }

    printf("\nOriginal Unsorted array :\n");
    for (i = 0; i < 10; i++) {
        printf("%d\t", number[i]);
    }
    printf("\n");

    puts("Sorted array by server :");
    for (i = 0; i < 10; i++) {
        printf("%d\t", server_reply[i]);
    }
    printf("\n");

    close(sock);
    return 0;
}
