#include <stdio.h>  
#include <string.h>  
#include <openssl/sha.h>  
#include <stdlib.h>  
#include <openssl/bn.h>
#include <time.h>
#define SHA_DIGEST_LENGTH 20  
int main()  
{  
	clock_t start, finish;   
	double Total_time;  
	unsigned char digest[SHA_DIGEST_LENGTH];
	unsigned char sig[SHA_DIGEST_LENGTH]; 	
	BIGNUM *rnd;  
//    rnd = BN_new();
	char *p;
	char *temp;
	int length,i,j,k,result;  
//    char *show;  
//	  BN_random  
//    int bits = 16;  
//    int top =0;  
//    int bottom = 0;   
//    BN_rand(rnd,256,0,0); 
//	  p=BN_bn2hex(rnd);
//	  printf ("number is 0x%s\n", p);
//    length = BN_num_bits(rnd);  
//    show = BN_bn2dec(rnd);  
//    printf("length:%d,rnd:%s\n",length,show); 	 
//    BN_free(rnd);

	 
    rnd = BN_new(); 
    char *d;    
    BN_rand(rnd,256,0,0);  
	d = BN_bn2dec(rnd); 
    printf("The random message d to be signed is:%s\n",d); 	 
    BN_free(rnd);

	char  **s0 =(char**)malloc(sizeof(char*)*256); 
	for(i = 0; i <= 255; i++)    
		s0[i]=(char*)malloc(sizeof(char)*2);  
	for(i = 0; i <= 255; i++)
	{
		rnd = BN_new();
		BN_rand(rnd,10,-9,0); 
		s0[i] = BN_bn2dec(rnd); 
//		printf("The %dth random number is:%s\n",i+1,s0[i]);
		BN_free(rnd);
	}
	
	
	unsigned char  **s1 =(unsigned char**)malloc(sizeof(unsigned char*)*256); 
	for(i = 0; i <= 255; i++)    
		s1[i]=(unsigned char*)malloc(sizeof(unsigned char)*2);  
	for(i = 0; i <= 255; i++)
	{
		
		SHA1((unsigned char*)s0[i]	, strlen(s0[i]), (unsigned char*)&digest); 
//		sprintf(s1[i], "%d", (unsigned int)digest[0]);
//		sprintf(&s1[i][1], "%d", ((unsigned int)digest[1])%4);
		s1[i][0]=digest[0];
		s1[i][1]=digest[1]%4;
		int j = s1[i][0]+s1[i][1]*256;
//		memccpy(&s1[i][0],&digest[0],1);
//		printf("%d     ",s1[i][0]);
//		printf("%c      ",s1[i][0]);
//		printf("The %dth number is:%d\n",i+1,j);
	}
	
	
	
	
	
	
	unsigned int v[20];
	unsigned int dtemp;
	
	
	for(j=0;j<17500;j++)
	{
		
//	unsigned char digest[SHA_DIGEST_LENGTH];  
//	char string[] = "123";  
//	printf("%d",strlen(show));
//	SHA1((unsigned char*)&string, strlen(string), (unsigned char*)&digest);  
	SHA1((unsigned char*)d, strlen(d), (unsigned char*)&digest);  
//	char mdString[SHA_DIGEST_LENGTH*2+1];  
  
//	for(i = 0; i < SHA_DIGEST_LENGTH; i++)  
//		sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);  
  
//	printf("SHA1 digest: %s\n", mdString);  
	
	for(i = 0; i < 20; i++)
	{
		v[i] = (unsigned int)digest[i];
//		printf("%d ",dtemp);
//		v[i] = s0[dtemp][0]+s0[dtemp][1]*256;
	}
	
	}
	finish = clock(); 
	Total_time = (double)(finish-start);  ;
	printf( "Total time of 1000 signatures is: %f seconds\n", Total_time);   

	
	printf("The signature of d is: (");
	for(i = 0; i < 19; i++)
		printf("%s, ",s0[v[i]]);
	printf("%s)\n",s0[v[19]]);
	
	start = clock(); 
	for(k=0;k<17500;k++)
	{
	SHA1((unsigned char*)d, strlen(d), (unsigned char*)&digest);  
	for(i = 0; i < 20; i++)
	{
		j = (unsigned int)digest[i];
		SHA1((unsigned char*)s0[j]	, strlen(s0[j]), (unsigned char*)&sig); 
		if(s1[j][0]==sig[0] && s1[j][1]==(sig[1]%4))
			result = 1;
		else result =0;
	}
	}
 		
	if(result == 1)
		printf("signature is right!\n");


	return 0;  
  
}  