/*************************************************************************
	> File Name: client_host.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月10日 星期一 10时42分02秒
 ************************************************************************/
/*
 *本地网络套接字客户端程序
 */

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

int main(void)
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    address.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&address.sin_addr.s_addr);
    address.sin_port = 9734;
    len = sizeof(address);

    result = connect(sockfd,(struct sockaddr *)&address,len);
    if(result == -1)
    {
        perror("connect failed");
        exit(1);
    }

    write(sockfd,&ch,1);
    read(sockfd,&ch,1);
    printf("char from server = %c\n",ch);
    close(sockfd);
    exit(0);
}
