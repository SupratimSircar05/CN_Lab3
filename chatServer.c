#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    printf("\nServer Socket");
    int fd, res;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("\nReturn value : %d", fd);
    char buff[100];
    if (fd == -1)
        printf("\nSocket not created\n");
    else
        printf("\nSocket created\n");

    char stopword[4] = "bye";

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

    while(1) {

        recvfrom(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &client, &l);
        printf("\nMessage from client :\n%s\n", buff);
        if(strcmp(stopword, buff) == 0)
            break;

        printf("\nEnter a message :\n");
        gets(buff);
        if(strcmp(stopword, buff) != 0)
            sendto(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &client, sizeof(client));
        else
        {
            sendto(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &client, sizeof(client));
            break;
        }

    }
    printf("\nCommunication terminated !\n");

    return 0;
}