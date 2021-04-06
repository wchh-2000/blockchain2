#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "sha256.h"
#include "mining.h"

#define N0 8  //hash开头有N0个2进制0 
int main(void) {
	int i,j;
	unsigned char hash[32]={0}; //256 bits hash  0用于给第一个区块赋值 
	BLOCK *pre,*h;//前区块指针 区块链头指针 
	SHA256_CTX ctx;
	sha256_init(&ctx);
	
	for(i=0;i<10;i++)//生成10个区块 
	{
		BLOCK *block=(BLOCK *)malloc(sizeof(BLOCK));//分配的内存跳出循环仍存在 
		puts("creating new block:\n");
		Block_init(block,hash);//创建初始区块 hash为上一个区块的 第一个区块hash=0 
		Mining(&ctx,block,hash,N0); 
		
		//printf("sizeof block:%d size of transaction:%d\n",sizeof(*block),sizeof(block->trans));
		printf("\ninfo of %d th block:\n",i+1);
		print_block(block);
		printf("hash:");
		for(j=0;j<32;j++)
			printf("%x ",hash[j]);
		puts("\n");
		
		char s[]="blockchain_data/block";
		char n[4];
		itoa(i+1,n,10);
		strcat(s,n);
		FILE *fp=fopen(s,"wb");
		if(fp==NULL)
		{
		printf("can't open the file\n");
		exit(0);
		}
		fwrite(block,blockBytes,1,fp);//每个区块信息存储到二进制文件 block->next不存，无意义 	
		//blockBytes=sizeof(BLOCK)-8  block->next(4bytes) 由于struct对齐，占8 
		fclose(fp);
		
		if(i==0)//第一个区块 
		{
			h=block;//记录链头地址 
			pre=block;
			continue; //跳过下面的 
		}
		pre->next=block;//新区块加入链，上一个区块记录新区块地址 
		pre=block;//用最新的区块地址更新pre
	}
	//printf("%lld",h->next->next->nonce2);//验证链建好 第三个block的nonce2 
	pre->next=NULL;
	return 0;
	system("pause");
}
