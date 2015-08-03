/*************************************************************************
	> File Name: nethostbyte.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年08月03日 星期一 12时21分16秒
 ************************************************************************/

/*
 *网络主机字节序转换
 */

#include<stdio.h>
#include<netinet/in.h>

int main(void)
{
    uint16_t shost=0x1234;
    uint32_t lhost=0x12345678;
    uint16_t snet=0x1234;
    uint32_t lnet=0x12345678;

    printf("htons:%#x-%#x\n",shost,htons(shost));
    printf("htonl:%#x-%#x\n",lhost,htonl(lhost));
    printf("ntohs:%#x-%#x\n",snet,ntohs(snet));
    printf("ntohl:%#x-%#x\n",lnet,ntohl(lnet));

    return 0;
}
