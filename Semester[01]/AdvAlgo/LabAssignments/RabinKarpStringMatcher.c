/**
** Author - Nitish Bhattacharjee
**/
#include<stdio.h>
#include<string.h>
//#include<conio.h>

#define ALPH 256
#define TL 100
#define PL 10

void RabinKarp_Matcher(char *pat, char *txt, int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j, flag =0, p =0,t =0, h =1;
 
    for (i = 0; i < M-1; i++)
        h = (h*ALPH)%q;
 
    for (i = 0; i < M; i++)
    {
        p = (ALPH*p + pat[i])%q;
        t = (ALPH*t + txt[i])%q;
    }
 
    for (i = 0; i <= N - M; i++)
    {
        if ( p == t )
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
 
            if (j == M)
                {
                	printf("Pattern occurs with shift %d \n", i);
                	flag = 1;
				}
			if (j<M)
				printf("Spurious hit occurs with shift %d \n", i);
        }
 
        if ( i < N-M )
        {
            t = (ALPH*(t - txt[i]*h) + txt[i+M])%q;
            if (t < 0)
            	t = (t + q);
        }
    }
    if ( flag == 0)
        	printf("\nNo Pattern Match is present...");
}
 
int main()
{
   	char txt[TL],pat[PL];
   	int q = 101;
   	printf("\nEnter the text(Case-Sensitive) : ");
	gets(txt);
	printf("\nEnter the pattern(Case-Sensitive) : ");
	gets(pat);
    RabinKarp_Matcher(pat, txt, q);
    //getch();
    return 0;
}
