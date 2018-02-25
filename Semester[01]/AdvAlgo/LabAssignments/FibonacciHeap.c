/**
*
* Author - Nitish Bhattacharjee
*
**/
#include<stdio.h>
#include<stdlib.h>

struct node {
	int key;
	struct node* left;
	struct node* right;
};

struct heap {
	struct node* min;
};

struct heap* make_heap();
struct node* make_node(int k);
void insert (struct heap* H, struct node* x);
struct node* minimum (struct heap* H);
struct heap* Union(struct heap* H1, struct heap* H2);
void Print_Root_List (struct heap* H);

int main()
{
	int i,n,k;
	struct node* x = NULL;
	struct heap* H1 = make_heap();
	struct heap* H2 = make_heap();
	printf("\nEnter the number of elements in the first fibonacci heap\n");
	scanf("%d",&n);
	if(n!=0)
	{
		printf("\nEnter the elements to be inserted into the 1st fibonacci heap.");
		printf("\n(after typing each element hit enter)..\n");
		for (i=0;i<n;i++)
		{	
			scanf("%d", &k); x=make_node(k);
			insert(H1,x);
		}
	}
	printf("\nRootlist for the first fibonacci heap\n");
	Print_Root_List(H1);
	x=minimum(H1);
	if(x){
		printf("\nMinimum key in first fibonacci heap is %d\n", x->key);
	} 
	else {
		printf("\nFirst fibonacci heap is empty\n");
	}	
	printf("\nEnter the number of elements in the second fibonacci heap\n");
	scanf("%d",&n);
	if(n!=0)
	{
		printf("\nEnter the elements to be inserted into the 2nd fibonacci heap.");
		printf("\n(after typing each element hit enter)..\n");
		for(i=0;i<n;i++)
		{
			scanf("%d",&k); x=make_node(k);
			insert(H2,x);
		}
	}
	printf("\nRootlist for the second fibonacci heap\n");
	Print_Root_List(H2);
	x = minimum(H2);
	if(x){
		printf("\nMinimum key in H2 is %d\n",x->key);
	} else {
		printf("\nH2 is empty\n");
	}
	printf("\nPerforming Union of the two fibonacci heaps\n");
	struct heap* H = Union(H1,H2);
	printf("\nRootlist for the union heap of two fibonacci heaps\n");
	Print_Root_List(H);	
	x = minimum(H);
	if(x){
		printf("\nMinimum key in union heap is %d\n", x->key);
	}
	return 0;
}

struct heap* make_heap(){
	struct heap* H = (struct heap* )malloc(sizeof(struct heap));
	H->min = NULL;
	return H;
}

struct node* make_node(int k){
	struct node* x = (struct node* )malloc(sizeof(struct node));
	x->key = k;
	return x;
}

void insert (struct heap* H, struct node* x){
	if(H->min){
	 	H->min->right->left = x; 
	 	x->left = H->min;
	 	x->right = H->min->right;
		H->min->right = x;
		if (x->key < H->min->key){
			H->min = x;
		}
	 } else {
	 	x->left = x;
		x->right = x;
	 	H->min = x;
	 }
}

struct node* minimum (struct heap* H){
	return H->min;;
}

struct heap* Union(struct heap* H1, struct heap* H2){
	struct heap* H = make_heap();
	if (H1->min&&H2->min){
		H->min = H1->min;
		H->min->left->right = H2->min->right; 
		H2->min->right->left = H->min->left;
		H->min->left = H2->min;
		H2->min->right = H->min;
		if ((H1->min == NULL) || ((H2->min) && (H2->min->key <= H1->min->key))) {
		   H->min = H2->min;
		   }
	} else if (H1->min) {
		H->min = H1->min;
	} else if (H2->min) {
		H->min = H2->min;
	}
	return H;
}

void Print_Root_List(struct heap* H){
	if(H->min){
		struct node* x_right = H->min->right;
		struct node* tmp = NULL;
		printf("%d ", x_right->left->key);
		while (x_right != H->min){
			  printf("%d ", x_right->key);
			  tmp = x_right->right;
			  x_right = tmp;
		}
		printf("\n");
	} else {
		printf("No elements\n");
	}
}
