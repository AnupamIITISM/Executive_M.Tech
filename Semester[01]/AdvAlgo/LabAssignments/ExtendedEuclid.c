/**
** Author - Nitish Bhattacharjee
**/
#include<stdio.h>
//include<conio.h>

int euclid[3];
int* Extended_Euclid(int ,int);

int main()
	{
 		int a,b,*p; 
 		
 		printf("\nEnter number_1 : ");
 		scanf("%d",&a);
 		printf("\nEnter number_2 : ");
 		scanf("%d",&b);
		
	    p=Extended_Euclid(a,b);
 		printf("\nOutput of extended euclid algorithmic calculation for");
 		printf("\nthe given numbers in the form d=gcd(a,b)=a.X+b.Y is : ");
 		printf("%d=gcd(%d,%d)=%d.%d+%d.%d\n",*(p+0),a,b,a,*(p+1),b,*(p+2));
 		//getch();
 		return 0;
	}
	
int* Extended_Euclid(int a,int b)
	{ 
 		if(b==0)
			{
 				euclid[0]=a;euclid[1]=1;euclid[2]=0;
 				int *p=euclid;
 				return p;
 			}
		int *p;
 		p=Extended_Euclid(b,a%b);
 		euclid[0]=*p;euclid[1]=*(p+1);euclid[2]=*(p+2);
 		int temp;
 		temp=euclid[2];
 		euclid[2]=euclid[1]-(a/b)*euclid[2];
 		euclid[1]=temp;
 		p=euclid;
 		
		 return p;
}
