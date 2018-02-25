#include<stdio.h>
#include<string.h>
//#include<conio.h>
//#include<bits/stdc++.h>

#define TL 100
#define PL 10
 
void computePiArray(char *pat, int M, int *pi);
void KMPStringMatcher(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int pi[M],i=0,j=0,flag=0;
 
    computePiArray(pat, M, pi);
 
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;i++;
        }
        if (j == M)
        {
            printf("Patter occurs with shift %d\n",(i-j));
            j = pi[j-1];flag=1;
        }
 
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,they will match anyway
            if (j != 0)
                j = pi[j-1];
            else
                i = i+1;
        }
    }
    if(flag==0)
    	printf("\nNo match for the pattern is present...");
}
 
void computePiArray(char *pat, int M, int *pi)
{
    // length of the previous longest prefix suffix
    int len = 0;
    pi[0] = 0;
 
    // the loop calculates pi[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;pi[i] = len;i++;
        }
        else // (pat[i] != pat[len])
        {
           if (len != 0)
           {
                len = pi[len-1];
           }
            else // if (len == 0)
            {
                pi[i] = 0;i++;
            }
        }
    }
}
 
int main()
{
    char txt[TL],pat[PL];
   	printf("\nEnter the text(Case-Sensitive) : ");
	gets(txt);
	printf("\nEnter the pattern(Case-Sensitive) : ");
	gets(pat);
    KMPStringMatcher(pat, txt);
    //getch();
    return 0;
}
