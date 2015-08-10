/*************************************************************************
	> File Name: client.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月10日 星期一 16时21分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define SERV_PORT 9877
#define MAXLINE 1024
 
static int	read_cnt;
static char	*read_ptr;
static char	read_buf[MAXLINE];

static ssize_t my_read(int fd, char *ptr)
{

	if (read_cnt <= 0) 
    {
again:
		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) 
        {
			if (errno == EINTR)
				goto again;
			return -1;
		} 
        else 
        if (read_cnt == 0)
			return(0);
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char	c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) 
    {
		if ( (rc = my_read(fd, &c)) == 1) 
        {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets() */
		} 
        else 
        if (rc == 0) 
        {
			*ptr = 0;
			return n-1;	/* EOF, n - 1 bytes were read */
		} 
        else
			return -1;		/* error, errno set by read() */
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}

ssize_t readlinebuf(void **vptrptr)
{
	if (read_cnt)
		*vptrptr = read_ptr;
	return(read_cnt);
}

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
            if(nwritten < 0&&errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}

void str_cli(FILE *fp,int sockfd)
{
    char sendline[MAXLINE],recvline[MAXLINE];
    
    while(fgets(sendline,MAXLINE,fp) != NULL)
    {
        writen(sockfd,sendline,strlen(sendline));

        if(readline(sockfd,recvline,MAXLINE) == 0)
        {
            perror("str_cli:server terminated prematurely");
            exit(5);
        }

        if(fputs(recvline,stdout) == EOF)//ctrl+d是终端EOF
        {
            perror("str_cli:fputs error");
            exit(6);
        }
    }
}

int main(int argc , const char *argv[])
{
    int sockfd;
    int ret;
    struct sockaddr_in servaddr;
    
    if(argc != 2)
    {
        perror("usage: ./client <IPAddress>");
        exit(1);
    }

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    {
        perror("client socket error");
        exit(2);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    ret = inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    if(ret != 1)
    {
        fprintf(stderr,"<IPAddress>:xxx.xxx.xxx.xxx\n");
        exit(3);
    }

    ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if(ret < 0)
    {
        perror("client connect error");
        exit(4);
    }

    str_cli(stdin,sockfd);
    exit(0);
}
