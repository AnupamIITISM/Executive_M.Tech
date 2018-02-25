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
    int i, j, flag =0;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
 
    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*ALPH)%q;
 
    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++)
    {
        p = (ALPH*p + pat[i])%q;
        t = (ALPH*t + txt[i])%q;
    }
 
    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
 
        // Check the hash values of current window of text & pattern. If the hash values match then only
        // check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
 
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                {
                	printf("Pattern occurs with shift %d \n", i);
                	flag = 1;
				}
			if (j<M)
				printf("Spurious hit occurs with shift %d \n", i);
        }
 
        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (ALPH*(t - txt[i]*h) + txt[i+M])%q;
 
            // We might get negative value of t, converting it to positive
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
   	int q = 101; // A prime number
   	printf("\nEnter the text(Case-Sensitive) : ");
	gets(txt);
	printf("\nEnter the pattern(Case-Sensitive) : ");
	gets(pat);
    RabinKarp_Matcher(pat, txt, q);
    //getch();
    return 0;
}
