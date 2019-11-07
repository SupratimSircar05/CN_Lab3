// chat client
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    printf("\nClient Socket");
    char buff[100];
    int fd, res;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("\nReturn value : %d", fd);
    if (fd == -1)
        printf("\nSocket not created\n");
    else
        printf("\nSocket created\n");

    char stopword[4] = "bye";

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

    while (1) {

        printf("\nEnter a message :\n");
        gets(buff);
        if (strcmp(stopword, buff) != 0)
            sendto(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &y, sizeof(y));
        else {
            sendto(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &y, sizeof(y));
            break;
        }

        recvfrom(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &server, &l);
        printf("\nMessage from server :\n%s\n", buff);
        if (strcmp(stopword, buff) == 0)
            break;
    }
    printf("\nCommunication terminated !\n");

    return 0;
}