#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "sha256.h"
#include "mining.h"

#define N0 16  //hash��ͷ��N0��2����0 
void writefile(BLOCK *block,int num);
int main(void) {
	int i,j,N=10;
	unsigned char hash[32]={0}; //256 bits hash  0���ڸ���һ�����鸳ֵ 
	BLOCK *pre,*h;//ǰ����ָ�� ������ͷָ�� 
	for(i=0;i<N;i++)//����10������ 
	{
		BLOCK *block=(BLOCK *)malloc(sizeof(BLOCK));//������ڴ�����ѭ���Դ��� 
		puts("creating new block:\n");
		Block_init(block,hash);//������ʼ���� hashΪ��һ������� ��һ������hash=0 
		Mining(block,hash,N0); 
		//printf("sizeof block:%d size of transaction:%d\n",sizeof(*block),sizeof(block->trans));
		printf("\ninfo of %d th block:\n",i+1);
		print_block(block);
		printf("hash:");
		for(j=0;j<32;j++)
			printf("%x ",hash[j]);
		puts("\n");
		writefile(block,i+1);
		
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
	
	//malloc free
	return 0;
	system("pause");
}
void writefile(BLOCK *block,int num)//numΪ����� 
{
	char s[]="blockchain_data/block";
	char n[4];
	itoa(num,n,10);
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
}
