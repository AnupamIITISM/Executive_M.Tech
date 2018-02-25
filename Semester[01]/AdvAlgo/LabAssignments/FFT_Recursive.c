/**
*
* Author - Nitish Bhattacharjee
*
**/
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
//#include<conio.h>

#define PI atan2(1,1)*4

typedef  struct cmplx{
   double real;
   double imaginary;
}cmplx;

int isPwrOfTwo(int);
cmplx mulComplx(cmplx,cmplx); 
cmplx addComplx(cmplx,cmplx);
cmplx subComplx(cmplx,cmplx);
cmplx * Recursive_FFT(cmplx *,int);
void printComplx(cmplx);

int main()
{
  int i,deg_bound;
  cmplx *CoEff,*y;
  
  while(1)
  {
  	printf("\nEnter the degree-bound of the polynomial(has to be a power of 2): ");
  	scanf("%d",&deg_bound);
  	if(!isPwrOfTwo(deg_bound))
  		printf("\nEntry has to be a power of 2...");
  	else
  		break;
  }
   
  CoEff=(cmplx *) malloc(deg_bound*sizeof(cmplx));
  y=(cmplx *) malloc(deg_bound*sizeof(cmplx));
  
  if((CoEff==NULL)||(y==NULL))                   
  {
  	printf("Error! memory not allocated.");
    exit(0);
  }
	
  printf("\nEnter the coefficients values for the polynomial: ");
  for(i=0;i<deg_bound;i++)
  {
  	printf("\nEnter the coefficient value for X^[%d] : ",i);
  	scanf("%lf",&CoEff[i].real);
  	CoEff[i].imaginary=0.0;
  }
   
  printf("\nThe polynomial entered is P(X)=");
  for(i=deg_bound-1;i>=0;i--)
  {
  	if(i==0)
  	  printf("%d",(int)CoEff[i].real);
	else if(i==1)
	  printf("%d.X+",(int)CoEff[i].real);
	else
      printf("%d.X[^%d]+",(int)CoEff[i].real,i);
  } 
  
  printf("\nHence the coefficient representation of the polynomial P(X)_coefficient=");	
  for(i=deg_bound-1;i>=0;i--)	
	  printf(" %d",(int)CoEff[i].real);
  
  y=Recursive_FFT(CoEff,deg_bound);
  printf("\nThrough FFT , the determined point-value representation of the polynomial P(X)_pt-value is :");
  for(i=0;i<deg_bound;i++)
  {
   	  printf("\n(w%d^[%d] , ",deg_bound,i);
   	  printComplx(y[i]);
   	  printf(")");
   	  
  } 	
  printf("\n-where w%d is the %d complex %dth roots of unity.All the other complex %dth roots of unity are powers of w%d",deg_bound,deg_bound,deg_bound,deg_bound,deg_bound);
  
  free(y);
  free(CoEff);
  //getch();	 
  return 0;
}

int isPwrOfTwo(int x)
{
	while (((x % 2) == 0) && x > 1)
		x /= 2;
	return (x == 1);
}	

cmplx * Recursive_FFT(cmplx *a,int n)
{
	cmplx *a0,*a1,*y0,*y1,*y;
	cmplx w,wn,t;
	int i,k;
	
	y=(cmplx *) malloc(n*sizeof(cmplx));

	if(n==1)
		return a;	
	
    wn.real=cos(2*PI/(double)n);
    wn.imaginary=sin(2*PI/(double)n);
   
    w.real=1.0 ;
    w.imaginary=0.0 ;

   	a0 = (cmplx *) malloc ((n/2)*sizeof(cmplx));
   	a1 = (cmplx *) malloc ((n/2)*sizeof(cmplx));
   	y0 = (cmplx *) malloc ((n/2)*sizeof(cmplx));
  	y1 = (cmplx *) malloc ((n/2)*sizeof(cmplx));

	for(i=0;i<(n/2);i++) 
	{
    	a0[i]=a[2*i];
    	a1[i]=a[2*i+1];
    }	

	y0=Recursive_FFT(a0,n/2);
    y1=Recursive_FFT(a1,n/2);
	
	for(k=0;k<(n/2);k++) 
	{
    	t=mulComplx(w,y1[k]);
		y[k]=addComplx(y0[k],t);
        y[k+n/2]=subComplx(y0[k],t);
		w=mulComplx(w,wn);
    }
    
    free(y0);
    free(y1);
    free(a0);
    free(a1);
		
	return y;
}

cmplx mulComplx(cmplx a,cmplx b) 
{
   cmplx mul;

   mul.real=(a.real*b.real)-(a.imaginary*b.imaginary);
   mul.imaginary=(a.real*b.imaginary)+(a.imaginary*b.real);

   return mul;
}

cmplx addComplx(cmplx a,cmplx b)
{
   cmplx add;

   add.real=a.real+b.real;
   add.imaginary=a.imaginary+b.imaginary;

   return add;
}

cmplx subComplx(cmplx a, cmplx b) 
{
   cmplx sub;

   sub.real=a.real-b.real;
   sub.imaginary=a.imaginary-b.imaginary;

   return sub;
}

void printComplx(cmplx a)
{
	printf("%lf+i*%lf",a.real,a.imaginary);
}

