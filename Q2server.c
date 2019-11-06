#include <stdio.h>
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

    struct sockaddr_in x;
    x.sin_family = AF_INET;
    x.sin_port = ntohs(7000);
    x.sin_addr.s_addr = inet_addr("127.0.0.1");

    res = bind(fd, (struct sockaddr *) &x, sizeof(x));
    if (res == -1)
        printf("\nBind error\n");
    else
        printf("\nBind successfully\n");

    struct sockaddr_in client;
    int l = sizeof(client);

    recvfrom(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &client, &l);
    printf("\nMessage from client :\n");
    printf("%s\n", buff);

    printf("\nEnter a message : \n");
    gets(buff);
    sendto(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &client, sizeof(client));

    return 0;
}
