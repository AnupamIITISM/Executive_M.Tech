/**
*
* Author - Nitish Bhattacharjee
*
**/
#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
 
#define MAX 20

typedef struct node
{
    struct node *next;
    int vertex;
}node;
 
node *G[MAX];   
int visited[MAX];
int V;
void createGraph(); 
void printGraph();
void deleteGraph();
void DFS(int);
 
int main()
{
    int i,source;
    freopen("DFS_AdjacencyList.txt","w",stdout);
    printf("\n\t\tEnter how many vertices? :");
    scanf("%d",&V);
    
	createGraph(V);
    printGraph();  
     
 	printf("\n\n\t\tEnter the choosen source node for DFS traversal :");
	scanf("%d",&source);
	printf("\n\t\tDFS traversal result starting from node [%d] : ",source);
    DFS(source);
    deleteGraph();
    
	//getch();
    return 0;
}
 
void DFS(int s)
{
    node *p;
    printf("  [%d]",s);
    p=G[s];
    visited[s]=1;
    
    while(p!=NULL)
    {
       s=p->vertex;
       if(!visited[s])
            DFS(s);
        p=p->next;
    }
}
 
void createGraph()
{
    node *p,*q;
	int i,j,v,m;
   	
	printf("\n\t\tConsidering a DAG..hence has directed edges and cann't have cycles");
   	printf("\n\t\tNode names are numbered as 0,1,2,3...");
   	
	for(i=0;i<V;i++)
	{
		G[i]=NULL;
		visited[i]=0;
	}
        
    for(i=0;i<V;i++)
		{
    		q=NULL;
    		printf("\n\t\tEnter number of edges originating from [node %d] : ",i);
    		scanf("%d",&m);
    		for(j=0;j<m;j++)
				{
    				printf("\n\t\tEnter the #%d - th edge's destination node : ",j+1);
    				scanf("%d",&v);
    				p=(node*)malloc(sizeof(node));
    				p->vertex=v;
    				p->next=NULL;
    				if(G[i]==NULL)
    					G[i]=q=p;
    				else
    				{
    					q->next=p;
    					q=p;
					}
				}		
		}	
}

void printGraph()
{
	int i;
	node *p;
	
	printf("\n\t\tINPUT GRAPH : ");
	for(i=0;i<V;i++)
		{
    		p=G[i];
    		printf("\n\t\tAdjacency List [%d]->",i);
    		while(p!=NULL)
    			{
    				printf("%d->",p->vertex);
					p=p->next;		
    			}
    		printf("NULL");
		}
}

void deleteGraph()
{
	int i;
	for(i=0;i<V;i++)
		free(G[i]);
	//free(G);
}

