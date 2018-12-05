/**
*
*@n1t1shb
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

long int gcd(long int a, long int b){
    if(a == 0) return b;
    if(b == 0) return a;
    return gcd(b, a%b);
}
long int isprime(long int a){
    int i;
    for(i = 2; i < a; i++) if((a % i) == 0) return 0;
    return 1;
}
long int encrypt(char ch, long int n, long int e){
    int i;
    long int temp = ch;
    for(i = 1; i < e; i++) temp = (temp * ch) % n;
    return temp;
}

char decrypt(long int ch, long int n, long int d){
    int i;
    long int temp = ch;
    for(i = 1; i < d; i++) ch =(temp * ch) % n;
    return ch;
}

int main(){
    long int i, len;
    long int p, q, n, phi, e, d, cipher[50];
    char text[50];
    do {
        p = rand() % 30;
    } while (!isprime(p));
    do {
        q = rand() % 30;
    } while (!isprime(q));
    printf("\nTwo prime numbers generated randomly are (p and q) : %ld, %ld",p,q);
    n = p * q;
    printf("\nn = (p * q) = %ld",n);
    phi = (p - 1) * (q - 1);
    printf("\nphi = (p - 1) * (q - 1) = %ld",phi);
    do {
        e = rand() % phi;
    } while (gcd(phi, e) != 1);
    do {
        d = rand() % phi;
    } while (((d * e) % phi) != 1);
    printf("\nEnter the text to be encrypted: ");  scanf("%s",&text);
    len = strlen(text);
    printf("\nPublic key for encryption (n,e): (%ld,%ld)",n,e);
    for (i = 0; i < len; i++)
        cipher[i] = encrypt(text[i], n, e);
    printf("\nEncrypted message: ");
    for (i = 0; i < len; i++) printf("%ld",cipher[i]);
    printf("\nPrivate key for decryption(d): %d",&d);
    for (i = 0; i < len; i++) text[i] = decrypt(cipher[i], n, d);
    printf("\nDecrypted message: ");
    for (i = 0; i < len; i++) printf("%c",text[i]);
    return 0;
}
