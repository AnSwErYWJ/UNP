/*************************************************************************
	> File Name: server_host.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月10日 星期一 10时48分00秒
 ************************************************************************/

/*
 *本地网络套接字服务端程序
 */

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(void)
{
    int server_sockfd,client_sockfd;
    int server_len,client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_sockfd = socket(AF_INET,SOCK_STREAM,0);

    server_address.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr.s_addr);
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);
    bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

    listen(server_sockfd,5);
    while(1)
    {
        char ch;
        printf("server waiting\n");

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

        read(client_sockfd,&ch,1);
        ch++;
        write(client_sockfd,&ch,1);
        close(client_sockfd);
    }
}
