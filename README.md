# blockchain
 这是本地的工程文件直接上传的。 创建10个区块，下一区块(block)存储上一区块的hash值，构建区块链。每个区块数据存到一个二进制文件blockn,存储到blockchain_data文件夹。

 交易数据格式：
 
 typedef struct {
 
	BYTE from[33];//264bits 来源者公钥 
	
	BYTE to[33];//264 去向者公钥 
	
	double amount;//64 转移币数
	
	BYTE signature[64];//512 ecc数字签名  
	
	}Transaction; //实际占144bytes(由于数据对齐) 

使用ECDSA算法实现数字签名

 区块数据格式：
 
typedef struct BLOCK{

	BYTE prev_hash[32];//256前一个哈希值
	
	long long chain_version;//64 bits区块链版本号
	
	long long nonce1;//64挖矿随机数
	
	long long nonce2;//64
	
	double award;//64 挖矿奖励 
	
	BYTE coinbase[32];//256 挖矿者公钥
	
	Transaction trans[5];//n笔交易打包为一个区块 
	
	struct BLOCK *next;//(4bytes) 由于struct对齐，占8bytes  
	
	} BLOCK;//824 bytes

检验数字签名是否合法：

if(n==4)//第五笔交易模仿假的私钥

{
	privateKey_f[3]+=1;//修改私钥  验证数字签名应该不通过 

}
		
ecdsa_sign(privateKey_f,trans_hash,signature);//使用from的私钥对交易记录进行数字签名 
 if(ecdsa_verify(publicKey_f,trans_hash,signature))

{
	printf("transaction %d verified\n",n+1);

 ...
}
else
		
	printf("transaction %d verification failed\n",n+1);
			
结果见下图：
![image](https://user-images.githubusercontent.com/69345371/113707839-0e98cd80-9713-11eb-84b9-3ca7c08ae816.png)
