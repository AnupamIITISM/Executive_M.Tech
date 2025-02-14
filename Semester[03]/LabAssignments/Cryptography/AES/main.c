/**
*
*@n1t1shb
*
**/
#include <stdio.h>
#include <stdlib.h>
#include "aes.h"

int main(){
	uint8_t i;
	uint8_t key[] = {
		0x00, 0x01, 0x02, 0x03,	0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,	0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,	0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,	0x1c, 0x1d, 0x1e, 0x1f};
	uint8_t plaintT[] = {
		0x00, 0x11, 0x22, 0x33,	0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,	0xcc, 0xdd, 0xee, 0xff};
	uint8_t cipherT[16];
	uint8_t *w; // expanded key
	w = aes_init(sizeof(key));
	aes_key_expansion(key, w);
	printf("\nOriginal plaintext :");
	for(i=0;i<4;i++) printf("%x %x %x %x ",plaintT[4*i+0],plaintT[4*i+1],plaintT[4*i+2],plaintT[4*i+3]);
	aes_cipher(plaintT,cipherT,w);
	printf("\n\nAES encryption :\nCipher text :");
	for(i=0;i<4;i++) printf("%x %x %x %x ", cipherT[4*i+0], cipherT[4*i+1], cipherT[4*i+2], cipherT[4*i+3]);
	aes_inv_cipher(cipherT,plaintT,w);
	printf("\n\nAES decryption :\nDecrypted text :");
	for(i=0;i<4;i++) printf("%x %x %x %x ",plaintT[4*i+0],plaintT[4*i+1],plaintT[4*i+2],plaintT[4*i+3]);
	free(w);
	return 0;
}
