#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define PORT 22000

int main()
{
    char str[100]; 

    int listen_fd, comm_fd; 

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1)
    {
        printf("Socket creation failed\n");
        return -1;
    }
    else
        printf("Socket successfully created\n");
    
   
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)); 

    listen(listen_fd, 10);

    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL); 
    while(1)
    {
        bzero(str, 100);

        recv(comm_fd, str, 100, 0);
        printf("Client says:%s", str);
        
        bzero(str, 100);
        printf("Input from server:");
        fgets(str, 100, stdin);
        
        send(comm_fd, str, strlen(str), 0);
    }
    close(comm_fd);

}