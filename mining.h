#ifndef mining_h
#define mining_h

#include "sha256.h"
#include "ecc.h"

#define blockBytes 816 //每个区块所占字节数 96+transaction*n 区块指针next不参与计算hash  
#define transBytes 80 //每笔交易记录所占字节数 不算数字签名 
#define MaxNum 10000000 //试nonce1,nonce2的最大数 
//typedef unsigned char BYTE;             // 8-bit byte

typedef struct {
	BYTE from[33];//264bits 来源者公钥 
	BYTE to[33];//264 去向者公钥 
	double amount;//64 转移币数
	//char time[16];//eg: 2021/03/30/16:05 //增加内容注意改transBytes
	BYTE signature[64];//512 ecc数字签名  
}Transaction; //1104 bits 138 实际占144bytes(33+33+6为8的倍数 64位数据宽度64bits 8 bytes) 
typedef struct BLOCK{
	BYTE prev_hash[32];//256
	long long chain_version;//64 bits
	long long nonce1;//64
	long long nonce2;//64
	double award;//64 挖矿奖励 
	BYTE coinbase[32];//256 挖矿者公钥
	Transaction trans[5];//n笔交易打包为一个区块  
	struct BLOCK *next;//(4bytes) 由于struct对齐，占8bytes  
} BLOCK;//824 bytes

void print_block(BLOCK *p);

void Block_init(BLOCK *p,BYTE *hash);
int Mining(SHA256_CTX *ctx,BLOCK *p,BYTE *hash,int n0);
//找到nonce1 nonce2 使得block的hash满足开头有n0个2进制0 
#endif  
