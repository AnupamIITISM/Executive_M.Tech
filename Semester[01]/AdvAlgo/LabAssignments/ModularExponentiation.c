/**
** Author - Nitish Bhattacharjee
**/
#include<stdio.h>
//#include<conio.h>
#define MAX 500

int bin[MAX],length;

void decToBinary(int n)
{
    int i = 0;
    while (n > 0) 
	{
        bin[i] = n % 2;
        n = n / 2;
        i++;
    }
    length = i-1;
}

void Square_N_Multiply(int b, int e,int n)
{ 
	if(n==0)
 		{
		 	printf("\nInvalid Input!!!... (n) Mod operand cann't be zero");return;
		}
 	else if(b==0)
    	{
			printf("\n[(%d^%d) Mod %d]:= %d",b,e,n,0);return;
		}
	else if(e==0)
		{
			if(n==1)
				printf("\n[(%d^%d) Mod %d]:= %d",b,e,n,0);
			else
    			printf("\n[(%d^%d) Mod %d]:= %d",b,e,n,1);
    		return;
    	}	
    else
		{
    		int z=1,j;
    		decToBinary(e);
    		printf("\nMod calculated on each step is : ");
    		for(j=length;j>=0;j--)
    			{	
					z=((z*z)%n);
					if(bin[j]==1)
						{
							z=((z*b)%n);
							printf("%d ",z);
						}
					else
						{
							printf("%d ",z);
						}
				}	
    		printf("\n\nFinally  - [(%d^%d) Mod %d]:= %d",b,e,n,z);
    }
}

int main()
{
    int b,e,n;
    printf("\nEnter the base value(b): ");
    scanf("%d",&b);
    printf("\nEnter the exponent value(e): ");
    scanf("%d",&e);
    printf("\nEnter the other mod operand value(n): ");
    scanf("%d",&n);
	Square_N_Multiply(b,e,n);    
	//getch();
    return 0;
}
