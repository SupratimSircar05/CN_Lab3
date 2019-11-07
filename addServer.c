// server adds the two numbers received and returns the result
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

    printf("\nServer Socket");
    int fd, res, a, b, result;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("\nReturn value : %d", fd);
    if (fd == -1)
        printf("\nSocket not created\n");
    else
        printf("\nSocket created\n");

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(7000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    res = bind(fd, (struct sockaddr *) &server, sizeof(server));
    if (res == -1)
        printf("\nBind error\n");
    else
        printf("\nBind successfully\n");

    struct sockaddr_in client;
    int l = sizeof(client);

    recvfrom(fd, &a, sizeof(a), 0, (struct sockaddr *) &client, &l);
    recvfrom(fd, &b, sizeof(b), 0, (struct sockaddr *) &client, &l);
    result = a + b;
    sendto(fd, &result, sizeof(result), 0, (struct sockaddr *) &client, sizeof(client));

    printf("\nThanks for asking !\n");

    return 0;
}