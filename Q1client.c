#include <stdio.h>
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

    struct sockaddr_in x;
    x.sin_family = AF_INET;
    x.sin_port = ntohs(6000);
    x.sin_addr.s_addr = inet_addr("127.0.0.1");

    res = bind(fd, (struct sockaddr *) &x, sizeof(x));
    if (res == -1)
        printf("\nBind error\n");
    else
        printf("\nBind successfully\n");

    struct sockaddr_in y;
    y.sin_family = AF_INET;
    y.sin_port = ntohs(7000);
    y.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\nEnter a message : \n");
    gets(buff);
    sendto(fd, &buff, sizeof(buff), 0, (struct sockaddr *) &y, sizeof(y));

    return 0;
}