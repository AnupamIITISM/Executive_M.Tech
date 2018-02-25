/**
** Author - Nitish Bhattacharjee
**/
#include<stdio.h>
//#include<conio.h>

int n,i, fe, le;
int a[2][10], t[2][9], e[2], x[2], f1[10], f2[10], l[2][10];

void input_time_values()
	{
		printf("\tAssembly Line Scheduling using two lines...\n\n");
		printf("Enter the number of stations in each line: ");
		scanf("%d",&n);
		printf("\nEnter the two entry time values:");
		for(i=0;i<2;i++)
			scanf("%d",&e[i]);
		printf("\nEnter two exit time values:");
		for(i=0;i<2;i++)
			scanf("%d",&x[i]);
			
		printf("\nEnter the time taken by stations of row/line S1:");
		for(i=0; i<n; ++i)
			{
				printf("\na1%d : ",(i+1));
				scanf("%d", &a[0][i]);
			}
		printf("\nEnter the time taken by stations of row/line S2:");
        for(i=0 ; i<n; ++i)
			{
				printf("\na2%d : ",(i+1));
				scanf("%d", &a[1][i]);
			}                                
        printf("\nEnter the transaction times taken from row/line S1 to:");
        for(i=0; i<n-1; ++i)
        	{
        		printf("\na2%d = t1%d :",(i+2),(i+2));
        		scanf("%d", &t[0][i]);
			}
        printf("\nEnter the transaction times taken from row/line S2 to:");           
        for(i=0; i<n-1; ++i)
        	{
        		printf("\na1%d = t2%d :",(i+2),(i+2));
        		scanf("%d", &t[1][i]);
			}
	}
	
void print_stations()
	{
		int j,i=le;
		printf("\nThe Optimal path is:");
		printf("\nStation %d, line %d", n,i);
		for(j=n-1;j>0;--j)
			{
				i = l[i-1][j];
                printf("\nStation %d, line %d", j,i);
			}
	}

void fastest_way()
	{
		f1[0] = e[0] + a[0][0];
        f2[0] = e[1] + a[1][0];
        int j;
        
		for(j = 1; j<n; ++j)
        	{
                if( (f1[j-1]+a[0][j]) <= (f2[j-1]+t[1][j-1]+a[0][j]) )
					{
						f1[j] = f1[j-1] + a[0][j];
						l[0][j] = 1;
					}
				else
					{
						f1[j] = f2[j-1] + t[1][j-1] + a[0][j];
						l[0][j] = 2;
					}
				if( (f2[j-1]+a[1][j]) <= (f1[j-1]+t[0][j-1]+a[1][j]) )
					{
						f2[j] = f2[j-1] + a[1][j];
						l[1][j] = 2;
					}
				else
					{
						f2[j] = f1[j-1] + t[0][j-1] + a[1][j];
						l[1][j] = 1;
					}
			}

		if( (f1[n-1] + x[0]) <= (f2[n-1] + x[1]) )
			{		
				fe = f1[n-1] + x[0];
				le = 1;
			}
		else
			{					
 				fe = f2[n-1] + x[1];
				le = 2;
			}
		printf("\nOptiomal cost: %d\n",fe);
		print_stations();
	}
	
int main()
	{	
		input_time_values();
		fastest_way();
		//getch();
		return 0;
	}
