#include <string.h>
#include <ctype.h>
#include "tools.h"

int 
hex2chr(unsigned char *out, const unsigned char *in, int strlen)
{
	int i;
	if(strlen % 2)
		return 0;
	unsigned char seq[16] = "0123456789ABCDEF";
	memset(out, 0, strlen / 2);
	for(i = 0; i < strlen; i += 2){
		unsigned char* high = strchr(seq, toupper(in[i]));
		unsigned char* low = strchr(seq, toupper(in[i + 1]));
		if(high == NULL || low == NULL)
			return 0;
		out[i / 2] = ((high - seq) << 4) | (low - seq);
	}
	return 1;
}
