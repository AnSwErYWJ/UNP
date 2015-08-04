/*************************************************************************
	> File Name: Listen.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月04日 星期二 21时21分29秒
 ************************************************************************/

/*
 *通过环境变量指定backlog的值的listen的包裹函数
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>

void Listen(int fd,int backlog)
{
    char *ptr;
    if((ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if(listen(fd,backlog) == -1)
        perror("Listen error");
}
