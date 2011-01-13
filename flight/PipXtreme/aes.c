
// http://gladman.plushost.co.uk/oldsite/AES/index.php

//#include <stdio.h>

#include "aes.h"

#define BPOLY   0x1B
#define DPOLY   0x8D

const uint8_t sbox[256] =
{
	0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
	0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
	0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
	0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
	0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
	0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
	0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
	0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
	0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
	0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
	0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
	0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
	0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
	0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
	0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
	0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

const uint8_t isbox[256] =
{
	0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
	0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
	0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
	0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
	0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
	0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
	0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
	0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
	0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
	0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
	0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
	0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
	0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
	0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
	0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
	0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
};

//#define xtime(x)	( (x << 1) ^ (((x >> 7) & 1) * BPOLY) )
//#define xtime(x)	( (x << 1) ^ ((x & 0x80) ? BPOLY : 0) )

const uint8_t xtime[256] =
{
	0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,
	0x20,0x22,0x24,0x26,0x28,0x2a,0x2c,0x2e,0x30,0x32,0x34,0x36,0x38,0x3a,0x3c,0x3e,
	0x40,0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,
	0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,
	0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,0x92,0x94,0x96,0x98,0x9a,0x9c,0x9e,
	0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb4,0xb6,0xb8,0xba,0xbc,0xbe,
	0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,
	0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xf0,0xf2,0xf4,0xf6,0xf8,0xfa,0xfc,0xfe,
	0x1b,0x19,0x1f,0x1d,0x13,0x11,0x17,0x15,0x0b,0x09,0x0f,0x0d,0x03,0x01,0x07,0x05,
	0x3b,0x39,0x3f,0x3d,0x33,0x31,0x37,0x35,0x2b,0x29,0x2f,0x2d,0x23,0x21,0x27,0x25,
	0x5b,0x59,0x5f,0x5d,0x53,0x51,0x57,0x55,0x4b,0x49,0x4f,0x4d,0x43,0x41,0x47,0x45,
	0x7b,0x79,0x7f,0x7d,0x73,0x71,0x77,0x75,0x6b,0x69,0x6f,0x6d,0x63,0x61,0x67,0x65,
	0x9b,0x99,0x9f,0x9d,0x93,0x91,0x97,0x95,0x8b,0x89,0x8f,0x8d,0x83,0x81,0x87,0x85,
	0xbb,0xb9,0xbf,0xbd,0xb3,0xb1,0xb7,0xb5,0xab,0xa9,0xaf,0xad,0xa3,0xa1,0xa7,0xa5,
	0xdb,0xd9,0xdf,0xdd,0xd3,0xd1,0xd7,0xd5,0xcb,0xc9,0xcf,0xcd,0xc3,0xc1,0xc7,0xc5,
	0xfb,0xf9,0xff,0xfd,0xf3,0xf1,0xf7,0xf5,0xeb,0xe9,0xef,0xed,0xe3,0xe1,0xe7,0xe5
};

// ***********************************************************************************
/*
void createXTimeTable(void)
{
	uint8_t i = 0;
	do {
		xtime[i] = (i << 1) ^ ((i & 0x80) ? BPOLY : 0);
	} while (++i != 0);
}
*/
// ***********************************************************************************
/*
uint8_t powTable[256];
uint8_t logTable[256];

uint8_t sbox[256];
uint8_t isbox[256];

void createPowLogTables(void)
{
	uint8_t i = 0;
	uint8_t t = 1;

	do {
		powTable[i] = t;
		logTable[t] = i;
		i++;
		t ^= (t << 1) ^ ((t & 0x80) ? BPOLY : 0);
	} while (t != 1);

	powTable[255] = powTable[0];
}

void createSubstitueBoxTable(void)
{
	int i = 0;
	do {
		uint8_t temp;

		if (i > 0)
			temp = powTable[255 - logTable[i]];
		else
			temp = 0;

		uint8_t sb = temp ^ 0x63;
		for (int j = 0; j < 4; j++)
		{
			temp = (temp << 1) | (temp >> 7);
			sb ^= temp;
		}

		sbox[i] = sb;
	} while (++i != 0);
}

void createInverseSubstitueBoxTable(void)
{
	uint8_t i = 0;
	uint8_t j = 0;
	do {
		do {
			if (sbox[j] == i)
			{
				isbox[i] = j;
				j = 255;
			}
		} while (++j != 0);
	} while (++i != 0);
}
*/
// ***********************************************************************************

void copy_block(void *d, void *s)
{
	if (d == s) return;

	register uint8_t *src = s;
	register uint8_t *dest = d;
	for (int i = N_BLOCK; i; --i)
		*dest++ = *src++;
}

void xor_block(void *d, void *s)
{
	register uint8_t *src = s;
	register uint8_t *dest = d;
	for (int i = N_BLOCK; i; --i)
		*dest++ ^= *src++;
}

void xor_word(uint8_t *d, uint8_t *s)
{
	*d++ ^= *s++;
	*d++ ^= *s++;
	*d++ ^= *s++;
	*d++ ^= *s++;
}

void xor_sub_word(uint8_t *d, uint8_t *s)
{
	*d++ ^= sbox[*s++];
	*d++ ^= sbox[*s++];
	*d++ ^= sbox[*s++];
	*d++ ^= sbox[*s++];
}

void xor_sub_rot_word(uint8_t *d, uint8_t *s, uint8_t rc)
{
	*d++ ^= sbox[s[1]] ^ rc;
	*d++ ^= sbox[s[2]];
	*d++ ^= sbox[s[3]];
	*d++ ^= sbox[s[0]];
}

void mix_sub_column(uint8_t *a)
{
	uint8_t a0 = a[0];
	uint8_t a1 = a[1];
	uint8_t a2 = a[2];
	uint8_t a3 = a[3];
	uint8_t tmp = a0 ^ a1 ^ a2 ^ a3;
	a[0] = a0 ^ xtime[a0 ^ a1] ^ tmp;
	a[1] = a1 ^ xtime[a1 ^ a2] ^ tmp;
	a[2] = a2 ^ xtime[a2 ^ a3] ^ tmp;
	a[3] = a3 ^ xtime[a3 ^ a0] ^ tmp;
}

void mix_sub_columns(void *a)
{
	mix_sub_column((uint8_t*)a + 0);
	mix_sub_column((uint8_t*)a + 4);
	mix_sub_column((uint8_t*)a + 8);
	mix_sub_column((uint8_t*)a + 12);
}

void inv_mix_sub_column(uint8_t *a)
{
	uint8_t tmp;
	tmp = xtime[xtime[a[0] ^ a[2]]];
	a[0] ^= tmp;
	a[2] ^= tmp;
	tmp = xtime[xtime[a[1] ^ a[3]]];
	a[1] ^= tmp;
	a[3] ^= tmp;
}

void inv_mix_sub_columns(void *a)
{
	inv_mix_sub_column((uint8_t*)a + 0);
	inv_mix_sub_column((uint8_t*)a + 4);
	inv_mix_sub_column((uint8_t*)a + 8);
	inv_mix_sub_column((uint8_t*)a + 12);

	mix_sub_columns(a);
}

void shift_sub_rows(uint8_t *a)
{
	uint8_t tmp;

	a[0]  = sbox[a[0]];
	a[4]  = sbox[a[4]];
	a[8]  = sbox[a[8]];
	a[12] = sbox[a[12]];

	tmp   = a[1];
	a[1]  = sbox[a[5]];
	a[5]  = sbox[a[9]];
	a[9]  = sbox[a[13]];
	a[13] = sbox[tmp];

	tmp   = a[2];
	a[2]  = sbox[a[10]];
	a[10] = sbox[tmp];
	tmp   = a[6];
	a[6]  = sbox[a[14]];
	a[14] = sbox[tmp];

	tmp   = a[15];
	a[15] = sbox[a[11]];
	a[11] = sbox[a[7]];
	a[7]  = sbox[a[3]];
	a[3]  = sbox[tmp];
}

void inv_shift_sub_rows(uint8_t *a)
{
	uint8_t tmp;

	a[0]  = isbox[a[0]];
	a[4]  = isbox[a[4]];
	a[8]  = isbox[a[8]];
	a[12] = isbox[a[12]];

	tmp   = a[13];
	a[13] = isbox[a[9]];
	a[9]  = isbox[a[5]];
	a[5]  = isbox[a[1]];
	a[1]  = isbox[tmp];

	tmp   = a[2];
	a[2]  = isbox[a[10]];
	a[10] = isbox[tmp];
	tmp   = a[6];
	a[6]  = isbox[a[14]];
	a[14] = isbox[tmp];

	tmp   = a[3];
	a[3]  = isbox[a[7]];
	a[7]  = isbox[a[11]];
	a[11] = isbox[a[15]];
	a[15] = isbox[tmp];
}

// ***********************************************************************************

// 'on the fly' encryption key update for 128 bit keys
void update_encrypt_key_128(uint8_t *k, uint8_t *rc)
{
	xor_sub_rot_word(k + 0, k + 12, *rc);

 	*rc = (*rc << 1) ^ ((*rc & 0x80) ? BPOLY : 0);

	for (int i = 4; i < 16; i += 4)
		xor_word(k + i + 0, k + i - 4);
}

// Encrypt a single block of 16 bytes
void aes_encrypt_cbc_128(void *data, void *key, void *chain_block)
{
	uint8_t rc = 1;

	if (chain_block)
		xor_block(data, chain_block);

	for (int round = 10; round; --round)
	{
		xor_block(data, key);			// add_round_key
		update_encrypt_key_128((uint8_t *)key, &rc);
		shift_sub_rows(data);
		if (round <= 1) continue;
		mix_sub_columns(data);
	}
	xor_block(data, key);				// add_round_key

	if (chain_block)
		copy_block(chain_block, data);
}

// 'on the fly' decryption key update for 128 bit keys
void update_decrypt_key_128(uint8_t *k, uint8_t *rc)
{
	for (int i = 12; i; i -= 4)
		xor_word(k + i + 0, k + i - 4);

	*rc = (*rc >> 1) ^ ((*rc & 1) ? DPOLY : 0);

	xor_sub_rot_word(k + 0, k + 12, *rc);
}

// Decrypt a single block of 16 bytes
void aes_decrypt_cbc_128(void *data, void *key, void *chain_block)
{
	uint8_t tmp_data[N_BLOCK];

	uint8_t rc = 0x6c;

	copy_block(tmp_data, data);

	xor_block(data, key);					// add_round_key
	for (int round = 10; round; --round)
	{
		inv_shift_sub_rows(data);
		update_decrypt_key_128(key, &rc);
		xor_block(data, key);				// add_round_key
		if (round <= 1) continue;
		inv_mix_sub_columns(data);
	}

	if (chain_block)
	{
		xor_block(data, chain_block);
		copy_block(chain_block, tmp_data);
	}
}

void aes_decrypt_key_128_create(void *enc_key, void *dec_key)
{
	copy_block(dec_key, enc_key);

	uint8_t rc = 1;
	for (int i = 0; i < 10; i++)
		update_encrypt_key_128(dec_key, &rc);
}

// ***********************************************************************************

// 'on the fly' encryption key update for 256 bit keys
void update_encrypt_key_256(uint8_t *k, uint8_t *rc)
{
	xor_sub_rot_word(k + 0, k + 28, *rc);

 	*rc = (*rc << 1) ^ ((*rc & 0x80) ? BPOLY : 0);

	for (int i = 4; i < 16; i += 4)
		xor_word(k + i + 0, k + i - 4);

	xor_sub_word(k + 16, k + 12);

	for (int i = 20; i < 32; i += 4)
		xor_word(k + i + 0, k + i - 4);
}

// Encrypt a single block of 16 bytes
void aes_encrypt_cbc_256(void *data, void *key, void *chain_block)
{
	uint8_t rc = 1;

	if (chain_block)
		xor_block(data, chain_block);

	for (int round = 7; round; --round)
	{
//		printf("key - ");
//		uint8_t *p = key;
//		for (int i = 0; i < 32; i++) printf("%0.2X ", *p++);
//		printf("\r\n");

		xor_block(data, key);					// add_round_key
		shift_sub_rows(data);
		mix_sub_columns(data);
		xor_block(data, (uint8_t*)key + 16);		// add_round_key
		update_encrypt_key_256(key, &rc);
		shift_sub_rows(data);
		if (round <= 1) continue;
		mix_sub_columns(data);
	}
	xor_block(data, key);						// add_round_key

	if (chain_block)
		copy_block(chain_block, data);
}

// 'on the fly' decryption key update for 256 bit keys
void update_decrypt_key_256(uint8_t *k, uint8_t *rc)
{
	for (int i = 28; i >= 20; i -= 4)
		xor_word(k + i + 0, k + i - 4);

	xor_sub_word(k + 16, k + 12);

	for (int i = 12; i; i -= 4)
		xor_word(k + i + 0, k + i - 4);

	*rc = (*rc >> 1) ^ ((*rc & 1) ? DPOLY : 0);

	xor_sub_rot_word(k + 0, k + 28, *rc);
}

// Decrypt a single block of 16 bytes
void aes_decrypt_cbc_256(void *data, void *key, void *chain_block)
{
	uint8_t tmp_data[N_BLOCK];

	uint8_t rc = 0x80;

	copy_block(tmp_data, data);

	xor_block(data, key);						// add_round_key
	for (int round = 7; round; --round)
	{
		inv_shift_sub_rows(data);
		update_decrypt_key_256(key, &rc);
		xor_block(data, (uint8_t*)key + 16);		// add_round_key
		inv_mix_sub_columns(data);
		inv_shift_sub_rows(data);
		xor_block(data, key);					// add_round_key
		if (round <= 1) continue;
		inv_mix_sub_columns(data);
	}

	if (chain_block)
	{
		xor_block(data, chain_block);
		copy_block(chain_block, tmp_data);
	}
}

void aes_decrypt_key_256_create(void *enc_key, void *dec_key)
{
	if (dec_key != enc_key)
	{
		copy_block(dec_key, enc_key);
		copy_block((uint8_t*)dec_key + 16, (uint8_t*)enc_key + 16);
	}

	uint8_t rc = 1;
	for (int i = 7; i; --i)
		update_encrypt_key_256(dec_key, &rc);
}

// ***********************************************************************************
