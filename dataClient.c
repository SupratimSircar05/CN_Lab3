#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

    printf("\nClient Socket");
    int a, b, result, fd, res;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("\nReturn value : %d", fd);
    if (fd == -1)
        printf("\nSocket not created\n");
    else
        printf("\nSocket created\n");

    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = ntohs(6000);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    res = bind(fd, (struct sockaddr *) &client, sizeof(client));
    if (res == -1)
        printf("\nBind error\n");
    else
        printf("\nBind successfully\n");

    struct sockaddr_in server;
    int l = sizeof(server);

    struct sockaddr_in y;
    y.sin_family = AF_INET;
    y.sin_port = ntohs(7000);
    y.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\nEnter two integers to add :\n");
    scanf("%d%d", &a, &b);
    sendto(fd, &a, sizeof(a), 0, (struct sockaddr *) &y, sizeof(y));
    sendto(fd, &b, sizeof(b), 0, (struct sockaddr *) &y, sizeof(y));
    recvfrom(fd, &result, sizeof(result), 0, (struct sockaddr *) &server, &l);

    printf("\nResult :\n%d + %d = %d\n", a, b, result);

    return 0;
}