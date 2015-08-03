/*************************************************************************
	> File Name: readn.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月03日 星期一 13时06分36秒
 ************************************************************************/

/*
 *防止内核中用于套接字的缓冲区可能到达极限而不能正确返回读写字节数
 */

#include<stdio.h>
#include<unistd.h>
#include<errno.h>

ssize_t readn(int fd,void *vptr,size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr=vptr;
    nleft=n;

    while(nleft > 0)
    {
        if((nread = read(fd,ptr,nleft)) < 0)
        {
            if(errno == EINTR)//被信号中断
                nread = 0;
            else
                return -1;
        }
        else
        if(nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return (n-nleft);
}
