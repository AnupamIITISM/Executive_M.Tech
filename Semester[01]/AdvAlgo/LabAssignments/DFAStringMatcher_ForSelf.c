#include<stdio.h>
#include<string.h>
#define TL 100
#define PL 10
#define NO_OF_CHARS 256 //size of ASCII character set = cardinality of alphabet set(total number of possible characters in pattern and text)
 
int NextS(char *pat, int M, int state, int x)
{
    if (state < M && x == pat[state])// If the char is same as next char in pattern, goto next state
        return state+1;
 
    int ns, i; // ns stores the result which is next state
    for (ns = state; ns > 0; ns--) // Start from largest possible value & stop find a prefix which is also suffix
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
 
/*builds TF table which represents DFA for given pattern */
void Transition_Function(char *pat, int M, int TF[][NO_OF_CHARS])
{
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = NextS(pat, M, state, x);
}
 
void DFA_String_Matcher(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int flag =0; 
    int TF[M+1][NO_OF_CHARS];
 
    Transition_Function(pat, M, TF);
 
    // Process txt over FA.
    int i, state=0;
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
    return 0;
}
