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
	FILE *fp=fopen("blockchain_data","wb");
	SHA256_CTX ctx;
	sha256_init(&ctx);
	if(fp==NULL)
	{
		printf("can't open the file\n");
		exit(0);
	}
	for(i=0;i<10;i++)//����10������ 
	{
		BLOCK *block=(BLOCK *)malloc(sizeof(BLOCK));//������ڴ�����ѭ���Դ��� 
		Block_init(block,hash);//������ʼ���� hashΪ��һ������� ��һ������hash=0 
		Mining(&ctx,block,hash,N0); 
		//printf("%d \n",sizeof(*block));
		printf("info of %d th block:\n",i+1);
		printf("nonce1:%lld nonce2:%lld\n",block->nonce1,block->nonce2);//ע��lld������ȷ��ʾlong long  
		printf("previous hash:");
		for(j=0;j<32;j++)
			printf("%x ",block->prev_hash[j]);
		printf("\nhash:");
		for(j=0;j<32;j++)
			printf("%x ",hash[j]);
		puts("\n");
		fwrite(block,blockBytes,1,fp);//������Ϣ�洢���������ļ� 
		//blockBytes=sizeof(BLOCK)-8  block->next(4bytes) ����struct���룬ռ8 ���棬������ 
		if(i==0)//��һ������ 
		{
			h=block;//��¼��ͷ��ַ 
			pre=block;
			continue; //��������� 
		}
		pre->next=block;//���������������һ�������¼�������ַ 
		pre=block;//�����µ������ַ����pre
	}
	//printf("%lld",h->next->next->nonce2);//��֤������ 
	pre->next=NULL;
	fclose(fp);
	return 0;
	system("pause");
}
