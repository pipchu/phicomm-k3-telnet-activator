main : main.c md5.c md5.h rsa.c rsa.h udp.c udp.h
	cc -o phicomm-k3-telnet-activator main.c rsa.c md5.c udp.c \
	-lcrypto -ldl --static
	
udptestserver : udptestserver.c
	cc -o udptestserver udptestserver.c
	
clean : 
	rm -f phicomm-k3-telnet-activator udptestserver
