/**
*
* Author - Nitish Bhattacharjee
*
**/
#include<stdio.h>
#include<stdlib.h>

typedef struct heapNode
{
    int n,degree;
    struct heapNode *parent,*child,*sibling;
}heapNode;

heapNode * createBinHeap();
void linkBinHeap(heapNode *, heapNode *);
heapNode * createNode(int);
heapNode * unionBinHeap(heapNode *,heapNode *);
heapNode * insertBinHeap(heapNode *,heapNode *);
heapNode * mergeBinHeap(heapNode *, heapNode *);
heapNode * extractMinBinHeap(heapNode *);
void revertList(heapNode *);
void display(heapNode *);
heapNode * findNode(heapNode *, int);
int decreseKeyBinHeap(heapNode *, int, int);
int deleteBinHeap(heapNode *, int);

int count = 1;
heapNode *H=NULL;
heapNode *Hr = NULL;
 
int main() 
{
    int i,n,m,l;
    heapNode *p,*np;
    char ch;

    printf("\nEnter how many elements ? : ");
    scanf("%d",&n);
    printf("\nEnter the elements(hit enter after entering each element):\n");
    for(i=1;i<=n;i++) 
	{
        scanf("%d",&m);
        np=createNode(m);
        H=insertBinHeap(H,np);
    }

    display(H);

    do 
	{
        printf("\nMake a choice..\n");
        printf("\n1)Insert an element\n2)Extract the minimum key node\n3)Decrease a node key\n4)Delete a node\n5)Quit\n");
        scanf("%d",&l);

        switch(l)
		{
        	case 1:
	            do 
				{
	                printf("\nEnter the element to be inserted :");
                	scanf("%d",&m);
                	p=createNode(m);
                	H=insertBinHeap(H,p);
                	printf("\nUpdated heap\n");
                	display(H);
                	printf("\nWant to insert more(y/Y)? =\n");
                	fflush(stdin);
                	scanf("%c", &ch);
            	}while(ch=='Y'||ch=='y');

            	break;

        	case 2:
	            do 
				{
	                printf("\nExtracting the minimum key node..");
	                p = extractMinBinHeap(H);
	                if(p!=NULL)
						printf("\nThe extracted node is %d",p->n);
	                printf("\nUpdated heap\n");
	                display(H);
	                printf("\nWant to extract more(y/Y) ? \n");
	                fflush(stdin);
	                scanf("%c",&ch);
	            }while(ch=='Y'||ch=='y');

            	break;

        	case 3:
				do 
				{
	                printf("\nEnter the key of the node to be decreased :");
	                scanf("%d",&m);
	                printf("\nEnter the new key : ");
	                scanf("%d",&l);
	                decreseKeyBinHeap(H,m,l);
	                printf("\nUpdated heap\n");
	                display(H);
	                printf("\nWant to decrease more(y/Y) ? : \n");
	                fflush(stdin);
	                scanf("%c", &ch);
	            }while(ch=='Y'||ch=='y');

            	break;

        	case 4:
				do 
				{
	                printf("\nEnter the key to be deleted : ");
	                scanf("%d",&m);
	                deleteBinHeap(H,m);
	                display(H);
	                printf("\nWant to delete more (y/Y) ? \n");
	                fflush(stdin);
	                scanf("%c",&ch);
	            }while(ch=='y'||ch=='Y');
	
    	        break;
	
	        case 5:
			    break;
	
	        default:
	            printf("\nInvalid entrey...try again....\n");
        }
    }while(l!=5);
	
	return 0;
}

heapNode * createBinHeap()
{
    heapNode *np; np = NULL;
    
	return np;
}

void linkBinHeap(heapNode *y,heapNode *z) 
{
    y->parent=z;
    y->sibling=z->child;
    z->child=y;
    z->degree=(z->degree)+1;
}

heapNode * createNode(int k) 
{
	heapNode *p;
    p=(heapNode *)malloc(sizeof(heapNode));
    p->n=k;
    return p;
}

heapNode * unionBinHeap(heapNode *H1,heapNode *H2) 
{
	heapNode *prev_x,*next_x,*x;
	heapNode *H=createBinHeap();

    H=mergeBinHeap(H1,H2);

    if(H==NULL)
        return H;

    prev_x=NULL; x=H; next_x=x->sibling;

    while(next_x!=NULL) 
	{
        if((x->degree!=next_x->degree)||((next_x->sibling!=NULL)&&(next_x->sibling)->degree==x->degree))
		{
	        prev_x=x; x=next_x;
        } 
		else
		{
            if(x->n<=next_x->n) 
			{
	            x->sibling=next_x->sibling; linkBinHeap(next_x,x);
            } 
			else
			{
	            if(prev_x==NULL)
                    H=next_x;
                else
                    prev_x->sibling=next_x;
                linkBinHeap(x,next_x);
                x=next_x;
            }
        }
		
		next_x = x->sibling;
    }

    return H;
}

heapNode * insertBinHeap(heapNode *H,heapNode *x)
{
    heapNode *H1=createBinHeap();
    x->parent=NULL; x->child=NULL; x->sibling=NULL; x->degree=0;
    H1 = x;
    H=unionBinHeap(H,H1);
    
	return H;
}

heapNode * mergeBinHeap(heapNode *H1,heapNode *H2)
{
    heapNode *H=createBinHeap();
    heapNode *y,*z,*a,*b;
    y=H1; z=H2;

    if(y!=NULL) 
	{
        if((z!=NULL)&&(y->degree<=z->degree))
            H = y;
        else if((z!=NULL)&&(y->degree>z->degree))
            H=z;
        else
            H=y;
    } 
	else
        H=z;

    while(y!=NULL&&z!=NULL)
	{
        if(y->degree<z->degree) 
			y=y->sibling; 
		else if(y->degree==z->degree) 
		{
            a=y->sibling;
            y->sibling=z;
            y=a;
        } 
		else
		{
            b=z->sibling;
            z->sibling=y;
            z=b;
        }
	}	
	
    return H;
}

void display(heapNode *H)
{
    heapNode *p;
    if(H==NULL) 
	{
        printf("\nHeap is Empty..");
        return;
    }

    printf("\nThe Root List is : \n");
    p = H;
    while(p!=NULL) 
	{
        printf("%d",p->n);
        if (p->sibling!=NULL)
            printf("-->");
        p=p->sibling;
    }
    printf("\n");
}

heapNode * extractMinBinHeap(heapNode *H1)
{
    int min;
    heapNode *t=NULL,*x=H1,*Hr,*p;
    Hr = NULL;

    if(x==NULL)
	{
	    printf("\nNo element to extract..");
        return x;
    }

    p = x;
    while(p->sibling!=NULL)
	{
        if((p->sibling)->n<min) 
		{
            min=(p->sibling)->n; t=p; x=p->sibling;
        }
        p=p->sibling;
    }

    if(t==NULL&&x->sibling==NULL)
        H1 = NULL;
    else if(t==NULL)
        H1=x->sibling;
    else if(t->sibling==NULL)
        t = NULL;
    else
        t->sibling=x->sibling;
    
	if(x->child!=NULL)
	{
	    revertList(x->child); (x->child)->sibling=NULL;
    }
	H=unionBinHeap(H1,Hr);

    return x;
}

void revertList(heapNode *y) 
{
    if(y->sibling!=NULL) 
	{
        revertList(y->sibling); (y->sibling)->sibling = y;
    } 
	else
		Hr=y;
}

heapNode * findNode(heapNode *H, int k) 
{
    heapNode *x=H,*p=NULL;

    if(x->n==k) 
	{
        p = x;
        return p;
    }

    if(x->child!=NULL&&p==NULL)
		p=findNode(x->child, k);

    if(x->sibling!=NULL&&p==NULL) 
        p=findNode(x->sibling, k);

    return p;
}

int decreseKeyBinHeap(heapNode *H,int i,int k) 
{
    int temp;
    heapNode *p,*y,*z;
    p=findNode(H,i);
    
    if(p==NULL) 
	{
        printf("\nInvalid choice of Key to be reduced.....");
        return 0;
    }

    if(k>p->n) 
	{
        printf("\nThe new Key value is  greater than current one..");
        return 0;
    }

    p->n=k; y=p; z=p->parent;

    while(z!=NULL&&y->n<z->n)
	{
        temp=y->n; y->n=z->n; z->n=temp; y=z; z=z->parent;
    }

    printf("\nKey reduced successfully !!..");
    return 1;
}

int deleteBinHeap(heapNode *H,int k) 
{
    heapNode *np;
    if(H==NULL)
	{
        printf("\nHeap is Empty...");
        return 0;
    }

    decreseKeyBinHeap(H,k,-1000);
    np=extractMinBinHeap(H);

    if(np!=NULL)
        printf("\nNode deleted sucessfully...");
        
    return 1;
}
