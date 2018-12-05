/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<math.h>

int s[100]; 
int powerMod(int a,int b,int P){ 
    if (b == 1) return a;
    else return (((int)pow(a, b)) % P);
}
int isPrime(int n){ 
	int i;
    if (n <= 1)  return 0; 
    if (n <= 3)  return 1; 
    if (n%2 == 0 || n%3 == 0) return 0; 
    for (i=5; i*i<=n; i=i+6) if (n%i == 0 || n%(i+2) == 0) return 0; 
    return 1; 
} 
int findPrimefactors(int n){ 
	int i=0,j;
    while (n%2 == 0){s[i]=2;n = n/2; i++;} 
    for (j = 3; j <= sqrt(n); j = j+2){ 
        while (n%j == 0){s[i] = j; n = n/j; i++;} 
    } 
    if (n > 2) s[i] = n; 
    return i;
} 
int findPrimitive(int n){ 
    int phi,r,flag,count,i;
	if (isPrime(n)==0) return -1; 
    phi = n-1; 
    count = findPrimefactors(phi); 
    for (r=2; r<=phi; r++){ 
        flag = 0; 
        for (i = 0; i <= count; i++){ 
            if (powerMod(r, phi/(s[i]), n) == 1){flag = 1; break;} 
        } 
        if (flag == 0) return r; 
    } 
    return -1; // No primitive root found 
} 
 
int main(){
    int P, G, x, a, y, b, ka, kb; 
    printf("\nEnter a prime number(P) :"); scanf("%d",&P);
    G = findPrimitive(P);
    printf("\nA primitive root for P = %d is G = %d",P,G); 	
	printf("\nEnter secret 'a' chosen by the first node:"); scanf("%d",&a);
    x = powerMod(G, a, P); 
    printf("\nEnter secret 'b' chosen by the second node:"); scanf("%d",&b);
    y = powerMod(G, b, P); ka = powerMod(y, a, P); kb = powerMod(x, b, P);
    printf("\nSecret key shared to first node is : %d", ka);
    printf("\nSecret Key shared to second node is : %d", kb);
    return 0;
}
