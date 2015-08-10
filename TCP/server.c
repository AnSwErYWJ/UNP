/*************************************************************************
	> File Name: server.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月10日 星期一 15时44分05秒
 ************************************************************************/

/*
 *服务器程序
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<strings.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<sys/wait.h>

#define SERV_PORT 9877
#define MAXLINE 1024
     
ssize_t	writen(int fd, const void *vptr, size_t n)
{
	size_t	nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    
    while(nleft > 0)
    {
    if((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)//信号中断
                nwritten = 0;
            else
                return -1;
        }
		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];

again:
    while((n = read(sockfd,buf,MAXLINE)) > 0)
        writen(sockfd,buf,n);

    if(n < 0 && errno == EINTR)
        goto again;
    else
        if(n < 0)
            perror("str_echo:read error");
}

void sig_child(int signo)
{
    pid_t pid;
    int stat;

    while((pid = waitpid(-1,&stat,WNOHANG)))//等待任一子进程
        printf("child %d terminated\n",pid);
}

int main(void)
{
    int listenfd,connfd;
    int ret;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;
    
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd < 0)
    {
        perror("server socket error");
        exit(1);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    ret = bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if(ret < 0)
    {
        perror("server bind error");
        exit(2);
    }

    ret = listen(listenfd,5);
    if(ret < 0)
    {
        perror("server listen error");
        exit(3);
    }

    if(signal(SIGCHLD,sig_child) == SIG_ERR)//内核在任一进程终止时发给其父进程SIGHLD
    {
        perror("can not catch SIGHLD");
    }

    while(1)
    {
        clilen = sizeof(cliaddr);
        
        if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) < 0)
        {
            if(errno == EINTR)
                continue;
            else
                perror("client accept error");
        }
        if(connfd < 0)
        {
            perror("server accept error");
        }

        childpid = fork();
        if(childpid == 0)
        {
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }

        close(connfd);
    }
    
}
