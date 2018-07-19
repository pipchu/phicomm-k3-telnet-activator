#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "udp.h"

void freesock(const int fd);
int getsock();
struct sockaddr_in getsockaddr(const int p, const char *host);

int  
sendudp(const int p, const char *ip, const char *data, int len)
{
	struct sockaddr_in dst = getsockaddr(p, ip);
	int i, c, fd = getsock();
	if(!fd)
		return -1;
	socklen_t sklen = sizeof(dst);
	c = sendto(fd,data,len,0,(struct sockaddr*)&dst,sklen);
	freesock(fd);
	puts("-------------------udp------------------");
	if(c != -1){
		printf("sent:");
		for(i = 0; i < len; ++i)
			printf("%x%x", (data[i] >> 4) & 0xF, data[i] & 0xF);
		puts("");
		
	}else{
		puts("udp sent fail!");
	}
	puts("-------------------udp------------------");
	return c;
}

struct sockaddr_in 
getsockaddr(const int p, const char *ip)
{
	struct sockaddr_in ser_addr;	
	memset(&ser_addr,0,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr(ip);
	ser_addr.sin_port = htons(p);
	return ser_addr;
}

int 
getsock()
{
	int fd;
	fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd == -1){
		puts("create udp socket fail!");
		return 0;
	}
	return fd;
}

void 
freesock(const int fd)
{
	close(fd);
}



