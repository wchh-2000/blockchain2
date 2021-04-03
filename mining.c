#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "mining.h"
void struct2str(BLOCK *p,BYTE *s)
//����ṹ��תΪ�ַ����� ���ڼ���hash 
//ÿ�������ַ�����ᱻ���� 
{
	int i;
	for(i=0;i<blockBytes;i++)
		s[i]=*((BYTE *)p+i);
	s[i]="\0";//�Կ��ַ���β �����Ժ�õ��ַ����� 
}
void long2str(long long n,BYTE *s)//long long 64bits �ֳ�8��BYTE 
{
	int i;
	long long a=n;
	for(i=0;i<8;i++)
		s[i]=*((BYTE *)&a+i);
}
void Block_init(BLOCK *p,BYTE *hash)
{
	int i;
	p->chain_version=101;
	//memset(p->prev_hash, 0, sizeof(BYTE) * 32);
	for(i=0;i<32;i++)
		p->prev_hash[i]=hash[i];
	p->nonce1=0;
	p->nonce2=0;
	for(i=0;i<32;i++)
		p->coinbase[i]=rand()%256;//0-255����� 
	p->award=100;
	//p->bill[0].from=
}
int Mining(SHA256_CTX *ctx,BLOCK *p,BYTE *hash,int n0)
//�ҵ�nonce1 nonce2 ʹ��block��hash���㿪ͷ��n0��2����0 
//�Բ�ͬnonce������תΪ�ַ����� ��֤verify ��������nonce, hash 
{
	long long i,j;
	int v;
	int k;
	BYTE str[blockBytes+1];//�Կ��ַ���β ����+1 
	struct2str(p,str);
	v=verify(ctx,str,hash,n0);
	
	for(i=0;v==0&& i<MaxNum;i++)
	{
		long2str(i,&str[40]);//ֱ���޸��ַ������ڵ�ֵ����������struct2str ���Ч�� 
		for(j=0;v==0 && j<MaxNum;j++)
		{
			long2str(j,&str[48]);
			v=verify(ctx,str,hash,n0);
		} 
		if(v)//����Ҫ��
		{
			p->nonce1=i;
			p->nonce2=j;
			/*
			for (k = 0; k < 96; k++)
				printf("%d ", str[k]);
			printf("\n");��֤�ַ�������*/ 
			return 1;
		}
	}
	return 0;
}
int verify(SHA256_CTX *ctx,BYTE *str,BYTE *hash,int n)
// �ַ�������str ʹ��hashǰn��2������Ϊ0 ���㷵��1 
{
	int i,m,r;
	sha256_update(ctx, str, strlen(str));
	sha256_final(ctx, hash);
	m=n/8;//0ռBYTE���� 
	r=n%8;//���� 
	for(i=0;i<m;i++)
	{
		if(hash[i]!=0)
			return 0;
	}
	switch(r)//hashǰ��m��BYTE��Ϊ0ʱ �жϵ�m+1��BYTE�Ƿ�ǰ�溬r��0
	{
		case 0: return 1;
		case 1: if(hash[i]<=0x7f) return 1; break;
		case 2: if(hash[i]<=0x3f) return 1; break;
		case 3: if(hash[i]<=0x1f) return 1; break;
		case 4: if(hash[i]<=0x0f) return 1; break;
		case 5: if(hash[i]<=0x07) return 1; break;
		case 6: if(hash[i]<=0x03) return 1; break;
		case 7: if(hash[i]<=0x01) return 1; break;
	}
	return 0;
}
