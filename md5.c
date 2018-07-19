#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include "md5.h"

int 
md5raw(unsigned char *out, const unsigned char *in, int len)
{
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, in, len);
	MD5_Final(out, &c);
	return 1;
}
