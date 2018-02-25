/**
*
* Author - Nitish Bhattacharjee
*
**/
#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>

int Random(int p,int r)
{
    int q;
	srand(time(NULL)); //Intializes random number generator
	q=rand();
	q=(q%r)+p;
	
	return q;
}
 
void Exchange(int *a,int i,int j)
{
    int c;
    c=a[i];a[i]=a[j];a[j]=c;
}


int Partition(int *a,int p,int r)
{
	int x=a[r],i=p-1,j;
	for(j=p;j<=r-1;j++)
	{
		if(a[j]<=x)
		{
			i++;
			Exchange(a,i,j);
		}
	}
	Exchange(a,i+1,r);
	return (i+1);
}

int Randomized_Partion_Lomuto(int *a,int p,int r)
{
	int i=Random(p,r);
	Exchange(a,p,i);
	return Partition(a,p,r);	
}
 
void Randomized_Quicksort(int *a,int p,int r)
{
    int q;
    if (p<r)
    {
        q=Randomized_Partion_Lomuto(a,p,r);
        printf("\nIndex of pivot element : %d",q);
        Randomized_Quicksort(a,p,q-1);
        Randomized_Quicksort(a,q+1,r);
    }
}
int main()
{
    int i,n;
    int *array;
    printf("\nHow many elements to sort ? :");
    scanf("%d",&n);
    array=(int *)malloc(n*sizeof(int));
    
	printf("\nEnter the elements....");
    printf("\n(each separated with a space,hit enter to terminate)..");
    
    for(i=0;i<n;i++)
        scanf("%d",&array[i]);
    printf("\nOriginal Array : ");
    for(i= 0;i<n;i++)
        printf("%d  ",array[i]);
    printf("\nChoosing index of pivot element randomly..");
	printf("\nListed each successive pivot locations..");   
    Randomized_Quicksort(array,0,n-1);
  	printf("\nSorted list : ");
    for (i= 0;i<n;i++)
        printf("%d  ",array[i]);
        
    //getch();    
    return 0;
}
