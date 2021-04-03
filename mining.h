#ifndef mining_h
#define mining_h

#include "sha256.h"
#define blockBytes 96 //每个区块所占字节数 未添加账单 96+ 区块指针next不参与计算hash  

#define MaxNum 10000000 //试nonce1,nonce2的最大数 
//typedef unsigned char BYTE;             // 8-bit byte

typedef struct BLOCK{
	BYTE prev_hash[32];//256
	long long chain_version;//64 bits
	long long nonce1;//64
	long long nonce2;//64
	double award;//64 挖矿奖励 
	BYTE coinbase[32];//256 挖矿者公钥
	//BILL bill[2];//1000笔交易打包为一个区块  试验时为方便取2 
	struct BLOCK *next;//(4bytes) 由于struct对齐，占8bytes  
} BLOCK;
typedef struct {
	BYTE from[32];//256 来源者公钥 
	double amount;//64 转移币数
	BYTE to[32];//256 去向者公钥 
	char time[16];//eg: 2021/03/30/16:05 
}BILL; //704

void Block_init(BLOCK *p,BYTE *hash);
int Mining(SHA256_CTX *ctx,BLOCK *p,BYTE *hash,int n0);
//找到nonce1 nonce2 使得block的hash满足开头有n0个2进制0 
#endif  
