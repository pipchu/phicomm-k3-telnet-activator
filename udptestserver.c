#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define SERVER_PORT 21210
#define BUFFER_SIZE 1024

void udp_handler(int sfd)
{
	char buf[BUFFER_SIZE];
	socklen_t len;
	struct sockaddr_in client_addr;
	int count;
	while(1){
		memset(buf, 0, BUFFER_SIZE);
		len = sizeof(client_addr);
		count = recvfrom(sfd, buf, BUFFER_SIZE, 0, 
			(struct sockaddr*)&client_addr, &len);
		if(count == -1){
			puts("receive data fail!");
			break;
		}
		printf("rcv:");
		int i;
		for(i = 0; i < count; ++i)
			printf("%x%x", (buf[i] >> 4) & 0xF, buf[i] & 0xF);
		puts("");
		sleep(1);
	}
}

int main(void)
{
	int ret, sfd;
	struct sockaddr_in server_addr;
	sfd = socket(AF_INET, SOCK_DGRAM,0);
	if(sfd == -1){
		puts("Create Socket Fail!");
		exit(1);
	}
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);
	ret = bind(sfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(ret == -1){
		puts("Bind fail!");
		close(sfd);
		exit(1);
	}
	udp_handler(sfd);
	close(sfd);
	return 0;
}
