/**
** Author - Nitish Bhattacharjee
**/
#include<stdio.h>
#include<string.h>
//#include<conio.h>

void naive_matcher(char *pat,char *txt){
		int M=strlen(pat),N=strlen(txt),i,j,flag=0;
    	if(M>N){
				printf("No pattern match is present..");
				return;
		}    	
    	for(i=0;i<=N-M;i++){
				for(j=0;j<M;j++){
            			if(txt[i+j]!=pat[j]) break;
				}
				if(j==M){
					printf("Pattern occurs with shift %d\n", i);
					flag=1;
				}
		}
		if(flag==0)	printf("No pattern match is present..");
}

int main(){	
		char txt[100],pat[10];
		printf("\nEnter the text : "); gets(txt);
		printf("\nEnter the pattern : "); gets(pat);
   		naive_matcher(pat, txt);
   		return 0;
}
