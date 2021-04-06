#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "sha256.h"
#include "mining.h"

#define N0 8  //hash��ͷ��N0��2����0 
int main(void) {
	int i,j;
	unsigned char hash[32]={0}; //256 bits hash  0���ڸ���һ�����鸳ֵ 
	BLOCK *pre,*h;//ǰ����ָ�� ������ͷָ�� 
	SHA256_CTX ctx;
	sha256_init(&ctx);
	
	for(i=0;i<10;i++)//����10������ 
	{
		BLOCK *block=(BLOCK *)malloc(sizeof(BLOCK));//������ڴ�����ѭ���Դ��� 
		puts("creating new block:\n");
		Block_init(block,hash);//������ʼ���� hashΪ��һ������� ��һ������hash=0 
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
		fwrite(block,blockBytes,1,fp);//ÿ��������Ϣ�洢���������ļ� block->next���棬������ 	
		//blockBytes=sizeof(BLOCK)-8  block->next(4bytes) ����struct���룬ռ8 
		fclose(fp);
		
		if(i==0)//��һ������ 
		{
			h=block;//��¼��ͷ��ַ 
			pre=block;
			continue; //��������� 
		}
		pre->next=block;//���������������һ�������¼�������ַ 
		pre=block;//�����µ������ַ����pre
	}
	//printf("%lld",h->next->next->nonce2);//��֤������ ������block��nonce2 
	pre->next=NULL;
	return 0;
	system("pause");
}
