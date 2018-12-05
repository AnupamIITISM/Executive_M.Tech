/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<string.h>
void extendedEuclideInv(int,int,int,int,int,int);
char affineCipherEnc(char,int,int);
char affineCipherDec(char,int,int);
int gcd,t,s,mod;
int main(){
	int i,r1,r2,s1=1,s2=0,t1=0,t2=1,k1,k2,invk1;
	char plaintext[15], ciphertext[15],plaintext1[15];
	do{
		printf("\nModulus value used is : 26"); mod=26;
		printf("\nEnter the value for multiplicative key : "); scanf("%d",&k1);
		printf("\nEnter the value for additive key : "); scanf("%d",&k2);
		r1=mod; r2=k1;
		extendedEuclideInv(r1,r2,s1,s2,t1,t2);
		if(gcd!=1) printf("\nPlease choose multiplicative key in such a way, so that it is co-prime with the mod...");
	}while(gcd!=1);
	if(t<0)	t+=mod;
	invk1=t;
	printf("\nEnter the plaintext : ");
	scanf("%s",plaintext);
	for(i=0;i<strlen(plaintext);i++) ciphertext[i]=affineCipherEnc(plaintext[i],k1,k2);
    printf("\nThe encoded ciphertext is : ");
    for(i=0;i<strlen(plaintext);i++) printf("%c",ciphertext[i]);
	for(i=0;i<strlen(ciphertext);i++)  plaintext1[i]=affineCipherDec(ciphertext[i],k2,invk1);
	printf("\nThe decoded plaintext is : %s",plaintext1);
	return 0;
}

void extendedEuclideInv(int r1,int r2,int s1,int s2,int t1,int t2){
	if(r2==0){
		gcd=r1;	s=s1; t=t1;
	}
	else{
		int q, r, s, t;
		q = r1 / r2;
		r = r1 - q * r2;
		s = s1 - q * s2;
		t = t1 - q * t2;
		extendedEuclideInv(r2,r,s2,s,t2,t);
	}
}

char affineCipherEnc(char c,int k1,int k2){
	int i,flag;
	if((c>=65)&&(c<=90)){ 
		c-=65;
		flag = 0;
	}
	else if((c>=97)&&(c<=122)){  
		c-=97;
		flag = 1;
	}
	c=(c*k1)%mod;
	c=(c+k2)%mod;
	if(flag==0) c+=65;
	else c+=97;
	return c;
}
char affineCipherDec(char c,int k2,int invk1){
	int i,flag;
	if((c>=65)&&(c<=90)){ 
		c-=65;
		flag = 0;
	}
	else if((c>=97)&&(c<=122)){  
		c-=97;
		flag = 1;
	}
	c=c-k2;
	if(c<0) c+=mod;
    c=c%mod;
    c=(c*invk1)%mod;
	if(flag==0) c+=65;
	else  c+=97;
	return c;
}

