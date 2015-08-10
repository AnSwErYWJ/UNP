/*************************************************************************
	> File Name: client_local.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月10日 星期一 10时42分02秒
 ************************************************************************/
/*
 *文件系统套接字客户端程序
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

int main(void)
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';

    sockfd = socket(AF_UNIX,SOCK_STREAM,0);

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path,"server_socket");
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
