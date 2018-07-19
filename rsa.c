#include <string.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include "rsa.h"

RSA* newrsa(void);
void freersa(RSA *rsa);

int 
rsaop(unsigned char *out, const unsigned char *in ,int enc)
{
	RSA* rsa = newrsa();
	int size = 0x80;
	int stat = 1;
	if(!rsa)
		return 0;
	if(enc)
		size = RSA_private_encrypt(size, in, out, rsa, RSA_NO_PADDING);
	else
		size = RSA_public_decrypt(size, in, out, rsa, RSA_NO_PADDING);
	if(size == -1){
		printf("%s Error:%ld\n", 
			enc ? "RSA_private_encrypt" : "RSA_public_decrypt", 
			ERR_get_error());
		stat = 0;
	}
	if(!rsa)
		freersa(rsa);
	if(stat)
		return 1;
	else
		return 0;
}

RSA* 
newrsa(void)
{
	int size;
	int stat = 1;
	RSA* rsa = RSA_new();
	if(rsa == NULL){
		printf("RSA_new Error:%ld\n", ERR_get_error());
		return NULL;
	}
	
	BIGNUM *bn_n = BN_new();
	BIGNUM *bn_e = BN_new();
	BIGNUM *bn_d = BN_new();
	do{
		if(!(bn_n && bn_e && bn_d)){
			printf("BN_new Error:%ld\n", ERR_get_error());
			stat = 0;
			break;
		}
		if(BN_set_word(bn_e, 0x10001) != 1){
			printf("BN_set_word Error:%ld\n", ERR_get_error());
			stat = 0;
			break;
		}
		size = BN_hex2bn(&bn_n, 
		"CC232B9BB06C49EA1BDD0DE1EF9926872B3B16694AC677C8C581E1B4F59128912CBB92"
		"EB363990FAE43569778B58FA170FB1EBF3D1E88B7F6BA3DC47E59CF5F3C3064F62E504"
		"A12C5240FB85BE727316C10EFF23CB2DCE973376D0CB6158C72F6529A9012786000D82"
		"0443CA44F9F445ED4ED0344AC2B1F6CC124D9ED309A519");
		if(!size){
			printf("BN_hex2bn Error:%ld\n", ERR_get_error());
			stat = 0;
			break;
		}
		size = BN_hex2bn(&bn_d, 
		"9FC8FFBF53AECF8461DEFB98D81486A5D2DEE341F377BA16FB1218FBAE23BB1F376673"
		"2F8D382E15543FC2980208D968E7AE1AC4B48F53719F6D9964E583A0B791150B9C0C35"
		"4143AE285567D8C042240CA8D7A6446E49CCAF575ACC63C55BAC8CF5B6A77DEE0580E5"
		"0C2BFEB62C06ACA49E0FD0831D1BB0CB72BC9B565313C9");
		if(!size){
			printf("BN_hex2bn Error:%ld\n", ERR_get_error());
			stat = 0;
			break;
		}
	}while(0);
	if(!stat){
		RSA_free(rsa);
		free(bn_n);
		free(bn_e);
		free(bn_d);
		return NULL;
	}
	rsa->n = bn_n;
	rsa->e = bn_e;
	rsa->d = bn_d;
	return rsa;
}

void 
freersa(RSA* rsa)
{
	RSA_free(rsa);
	free(rsa->n);
	free(rsa->e);
	free(rsa->d);
}

