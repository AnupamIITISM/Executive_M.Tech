/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<math.h>

#define BLOCK_SIZE 16
#define KEY_SIZE 10

int binToDec(int no){
    int i=0,d,num=0;
    while(no!=0){
        d=no%10; num=num+(pow(2,i)*d); i++; no=no/10;
    }
    return num;
}

int decToBin(int no){
    int i=0,num=0;
    while(no!=0){
        num=num+((no%2)*pow(10,i)); i++; no=no/2;
    }
    return num;
}

int main(void){
    int i,j,no,n,row_no1,col_no1,row_no2,col_no2,val1,val2,n1,n2,n3,n4,n5,n6,c1=0,c2=0;
    int ip[BLOCK_SIZE],op[BLOCK_SIZE],LPT[BLOCK_SIZE/2],RPT[BLOCK_SIZE/2],key[KEY_SIZE],RPT1[BLOCK_SIZE/4],RPT2[BLOCK_SIZE/4],RPT1extd[BLOCK_SIZE/4],RPT2extd[BLOCK_SIZE/4],sbox[4][8];
    printf("Data Encryption Standard encoder : ");
	printf("\nEnter plain text(integer form, size=%d) : ",BLOCK_SIZE);
    for(i=0;i<BLOCK_SIZE;i++) scanf("%d",&ip[i]);
    printf("\nEnter key(integer form, size=%d) : ",KEY_SIZE);
    for(i=0;i<KEY_SIZE;i++) scanf("%d",&key[i]);
    for(i=0;i<BLOCK_SIZE/2;i++){
        LPT[i]=ip[i]; RPT[i]=ip[i+BLOCK_SIZE/2];
    }
    for(i=0;i<4;i++){
        RPT1[i]=RPT[i]; RPT2[i]=RPT[i+4];
    }
    for(i=0;i<4;i++){
        RPT1extd[i]=RPT1[i]; RPT2extd[i]=RPT2[i];
    }
    RPT1extd[0]=RPT2[i-1];
    RPT1extd[i]=RPT2[0];
    RPT2extd[0]=RPT1[i-1];
    RPT2extd[i]=RPT1[0];
    row_no1=RPT1extd[0]*10 + RPT1extd[i];
    col_no1=RPT1extd[1]*100 + RPT1extd[2]*10 + RPT1extd[3];
    row_no2=RPT2extd[0]*10 + RPT2extd[i];
    col_no2=RPT2extd[1]*100 + RPT2extd[2]*10 + RPT2extd[3];
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            sbox[i][j]=c1++;sbox[i][j+4]=c2++;
        }
    }
    n1=binToDec(row_no1);
    n2=binToDec(col_no1);
    val1=sbox[n1][n2];
    n3=decToBin(val1);
    n4=binToDec(row_no2);
    n5=binToDec(col_no2);
    val2=sbox[n4][n5];
    n6=decToBin(val2);
    for(i=0;i<BLOCK_SIZE/2;i++) op[i]=LPT[i];
    i=i+4;
    while(n3!=0){
        i--; op[i]=n3%10; n3=n3/10;
    }
    while(i!=8) op[--i]=0;
    i=i+8;
    while(n6!=0){
        i--; op[i]=n6%10; n6=n6/10;
    }
    while(i!=12) op[--i]=0;
    printf("\nGenerated cipher text :");
    for(i=0;i<BLOCK_SIZE;i++) printf("%d ",op[i]);
    return 0;
}


