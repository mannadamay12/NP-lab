#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define PORT 22000

int main(int argc, char **argv)
{
    char sendmsg[100];
    char recvmsg[100];

    int sock_fd, n;

    sock_fd=socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while(1)
    {
        bzero(sendmsg, 100);
        bzero(recvmsg, 100);
        printf("Enter the message: ");
        fgets(sendmsg, 100, stdin);

        send(sock_fd, sendmsg, strlen(sendmsg), 0);
        recv(sock_fd, recvmsg, 100, 0);

        printf("Message received: %s\n", recvmsg);
    }
}
