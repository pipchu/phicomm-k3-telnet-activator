#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "rsa.h"
#include "md5.h"
#include "udp.h"


int main(int argc, const char *argv[])
{
	unsigned char src[0x90];
	unsigned char enc[0x90];
	unsigned char dec[0x90];
	unsigned char hsrc[0x90];
	unsigned char hs[0x20];
	int i;
	if(argc == 1){
		printf("Usage: %s routerip\nExample: %s 192.168.0.1\n", argv[0], argv[0]);
		return 0;
	}
	const int server_port = 21210;
	const char const *server_ip = argv[1];
	memset(src, 0, sizeof(src));
	memset(enc, 0, sizeof(enc));
	memset(dec, 0, sizeof(dec));
	memset(hsrc, 0, sizeof(hsrc));
	memset(hs, 0, sizeof(hs));
	//generate random data for encrypt
	srand((unsigned int)time(NULL));
	for(i = 0; i < 0x80; ++i)
		src[i] = random() % 0xFE + 1;
	rsaop(enc, src, 1);
	rsaop(dec, enc, 0);
	memcpy(hsrc, enc, 0x80);
	//memcpy(hsrc + 0x80, &"+TEMP", 0x5);//Temporarily activate telnet
	memcpy(hsrc + 0x80, &"+PERP", 0x5);//Permanetly activate telnet
	md5raw(hs, hsrc, 0x80);
	//print data
	puts("src:");
	for(i = 0; i < 0x80; ++i)
			printf("%x%x",src[i] >> 4, src[i] & 0xF);
	puts("\nenc:");
	for(i = 0; i < 0x80; ++i)
			printf("%x%x",enc[i] >> 4, enc[i] & 0xF);
	puts("\ndec:");
	for(i = 0; i < 0x80; ++i)
			printf("%x%x",dec[i] >> 4, dec[i] & 0xF);
	puts("\nhsrc:");
	for(i = 0; i < 0x85; ++i)
			printf("%x%x",hsrc[i] >> 4, hsrc[i] & 0xF);
	puts("\nhash:");
	for(i = 0; i < 0x10; ++i)
			printf("%x%x",hs[i] >> 4, hs[i] & 0xF);
	puts("");
	//send activate data to router
	sendudp(server_port, server_ip, enc, 0x80);
	sleep(1);
	sendudp(server_port, server_ip, hs, 0x10);
	return 0;
}
