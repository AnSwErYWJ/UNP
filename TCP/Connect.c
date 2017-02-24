/*************************************************************************
	> File Name: connect.c
	> Author: weijie.yuan
	> Mail: yuanweijie1993@gmail.com
	> Created Time: Fri 24 Feb 2017 11:15:49 AM CST
 ************************************************************************/

#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>

#define MAXSLEEP 128

int my_connect(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen)
{
    int nsec;
    for(nsec = 1;nsec <= MAXSLEEP;nsec <<= 1)
    {
        if(connect(sockfd,servaddr,addrlen) == 0)
            return 0;//connection accepted
        if(nsec <= MAXSLEEP/2)//sleep nesc,then connect retry
            sleep(nsec);
    }
    return -1;
}
