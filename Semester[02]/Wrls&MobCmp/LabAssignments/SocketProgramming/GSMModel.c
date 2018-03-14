/**
*
*@n1t1shb
*
**/
#include<stdio.h>
#include<math.h>

int main()
{
	int i,j,k,N,cell,radius;
	printf("\n*****=====GSM Architecture=====*****");
	printf("\n[User Input] Enter total number of frequency allorted to the GSM network : "); scanf("%d",&k);
	printf("\nReuse factor(N) may have the following values:-");
	printf("\nI\tJ\tN=I^2+J^2");
	printf("\n--\t--\t--------");
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i==j)
				continue;
			else{
			N=((i*i)+(j*j)+(i*j));
			printf("\n%d\t%d\t%d",i,j,N);
			}
		}
	}
	printf("\netc..........");
	printf("\n[User Input] Enter your choosen reuse factor(cluster size) from the above suggested list : "); scanf("%d",&N);
	printf("[User Input] Enter total number of cells present in the GSM network : "); scanf("%d",&cell);
	printf("[User Input] Enter total radius of each cell in the GSM network(in KMs) : "); scanf("%d",&radius);
	printf("\n[GSM] Specifications for the suggested GSM Architecture: -");
	printf("\n[GSM] Total Area Coverage : %f KMs.",1.5*radius*radius*sqrt(3)*cell);
	printf("\n[GSM] Number of frequencies/channels per cell : %d",(int)(k/N));
	printf("\n[GSM] Frquency re-use ratio(D/R) : %f",sqrt(3*N));
	printf("\n[GSM] Total channel capacity/Maximum numer of concurrent calls possible : %d",(int)(k/N)*cell);
	printf("\n[GSM] Distance between to adjacent cells(d) : %f Kms",radius*sqrt(3));
	printf("\n[GSM] Minimum distance between centers of co-channels(cells using same frequecy band) D = : %f Kms",radius*sqrt(3*N));
	return 0;
}