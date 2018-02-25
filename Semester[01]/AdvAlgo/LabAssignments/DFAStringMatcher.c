/**
** Author - Nitish Bhattacharjee
**/
#include<stdio.h>
#include<string.h>
//#include<conio.h>
#define TL 100
#define PL 10
#define ALPH 256 
 
int NextS(char *pat, int M, int state, int x)
{
    if (state < M && x == pat[state])
        return state+1;
 
    int ns, i; 
    for (ns = state; ns > 0; ns--) 
    {
        if (pat[ns-1] == x)
        {
            for (i = 0; i < ns-1; i++)
                if (pat[i] != pat[state-ns+1+i])
                    break;
            if (i == ns-1)
                return ns;
        }
    }
 
    return 0;
}
 
void Transition_Function(char *pat, int M, int TF[][ALPH])
{
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < ALPH; ++x)
            TF[state][x] = NextS(pat, M, state, x);
}
 
void DFA_String_Matcher(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, state=0;
    int flag =0; 
    int TF[M+1][ALPH];
 
    Transition_Function(pat, M, TF);
    for (i = 0; i < N; i++)
    {
        state = TF[state][txt[i]];
        if (state == M)
            {
            	printf ("\nPattern occurs with shift= %d",(i-M+1));	
            	flag = 1;
			}
    }
    if (flag == 0)
    	printf ("\nNo Pattern Match is present..");
}
 
int main()
{
    char txt[TL],pat[PL];
	printf("\nEnter the text(Case-Sensitive) : ");
	gets(txt);
	printf("\nEnter the pattern(Case-Sensitive) : ");
	gets(pat);
	DFA_String_Matcher(pat, txt);
	//getch();
    return 0;
}
