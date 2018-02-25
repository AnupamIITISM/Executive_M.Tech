/**
** Author - Nitish Bhattacharjee
**/
#include<stdio.h>
//include<conio.h>

int Euclid(int ,int);

int main()
	{
 		int a,b; 
 		
 		printf("\nEnter number_1 : ");
 		scanf("%d",&a);
 		printf("\nEnter number_2 : ");
 		scanf("%d",&b);
		printf("\nG.C.D for the two inputs is : %d",Euclid(a,b));
 		//getch();
 		return 0;
	}
	
int Euclid(int a,int b)
	{ 
 		if(b==0)
			return a;
		else
			return Euclid(b,(a%b));	
	}
