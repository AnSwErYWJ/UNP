/*************************************************************************
	> File Name: hostbyteorder.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月03日 星期一 12时01分26秒
 ************************************************************************/

/*
 *判断主机字节序
 */

#include<stdio.h>
#include<sys/utsname.h>
#include<stdlib.h>

union _byteorder
{
    short s;
    char c[sizeof(short)];
};

int main(void)
{
    union _byteorder un;
    struct utsname info;

    un.s=0x0102;
    
    if(uname(&info) == -1)
    {
        perror("uname failed");
        exit(1);
    }
    printf("%s-%s-%s %s:\n",info.sysname,info.release,info.version,info.machine);
    
    if(sizeof(short) == 2)
    {
        if(un.c[0] == 2&&un.c[1] == 1)
            printf("little-endian\n");
        if(un.c[0] == 1&&un.c[1] == 2)
            printf("nig-endian\n");
    }
    else
        printf("sizeof(short) = %ld\n",sizeof(short));
    exit(0);
}
