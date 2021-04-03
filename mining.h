#ifndef mining_h
#define mining_h

#include "sha256.h"
#define blockBytes 96 //ÿ��������ռ�ֽ��� δ����˵� 96+ ����ָ��next���������hash  

#define MaxNum 10000000 //��nonce1,nonce2������� 
//typedef unsigned char BYTE;             // 8-bit byte

typedef struct BLOCK{
	BYTE prev_hash[32];//256
	long long chain_version;//64 bits
	long long nonce1;//64
	long long nonce2;//64
	double award;//64 �ڿ��� 
	BYTE coinbase[32];//256 �ڿ��߹�Կ
	//BILL bill[2];//1000�ʽ��״��Ϊһ������  ����ʱΪ����ȡ2 
	struct BLOCK *next;//(4bytes) ����struct���룬ռ8bytes  
} BLOCK;
typedef struct {
	BYTE from[32];//256 ��Դ�߹�Կ 
	double amount;//64 ת�Ʊ���
	BYTE to[32];//256 ȥ���߹�Կ 
	char time[16];//eg: 2021/03/30/16:05 
}BILL; //704

void Block_init(BLOCK *p,BYTE *hash);
int Mining(SHA256_CTX *ctx,BLOCK *p,BYTE *hash,int n0);
//�ҵ�nonce1 nonce2 ʹ��block��hash���㿪ͷ��n0��2����0 
#endif  
