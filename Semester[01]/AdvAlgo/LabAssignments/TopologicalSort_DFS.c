/**
*
* Author - Nitish Bhattacharjee
*
**/
#include<stdio.h>
#include<stdlib.h> 
//#include<conio.h>

int **graph;
int *visited,*finish_order;
int V,count=0;

void createGraph();
void deleteGraph();
void printGraph();
void DFS(int);
void topSortDFS();

int main()
{
  	freopen("TopologicalSort_DFSbased.txt","w",stdout);
	printf("\nEnter the number of vertices in the graph: ");
 	scanf("%d",&V);
 	
 	createGraph();
 	printf("\nInitial Graph:\n");
    printGraph(); 
	topSortDFS(); 
    deleteGraph();
	
	//getch();
    return 0;
}

void DFS(int u)
{
	int k;
	visited[u]=1;
	for(k=0;k<V;k++)
		if(!visited[k]&&graph[u][k])
			DFS(k);
	finish_order[count++]=u;
}

void topSortDFS()
{
	int s,p;
	printf("\n\nEnter the starting source node for DFS :");
	scanf("%d",&s);
	DFS(s-1);
	printf("\nThe topological sorting order for the supplied graph is ");
	for(p=0;p<V;p++)
		printf("->%d",(1+finish_order[V-1-p]));
}

void createGraph()
{
	int i,j,Y;
	graph = (int **)malloc(V * sizeof(int *));
	visited = (int *)malloc(V * sizeof(int *));
	finish_order = (int *)malloc(V * sizeof(int *));
		
	for (i=0; i<V; i++)
        graph[i] = (int *)malloc(V * sizeof(int));

	printf("\nConsidering a DAG..hence has directed edges and cann't have cycles");
    
	for (i=0;i<V;i++)
    	{
			visited[i]=0;finish_order[i]=0;
			for (j=0;j<V;j++)
	  			{
				  	if(i==j)
				  		graph[i][j]=0;
				  	else
				  		{
				  			if(graph[j][i]==1)
				  				graph[i][j]=0;
				  			else
				  				{
				  					printf("\nIs there an edge from node[%d] to node[%d]?:(Yes-1,No-0)",(i+1),(j+1));
				  					scanf("%d",&Y);
				  					if(Y==1)
				  						graph[i][j] = 1;
				  					else
				  						graph[i][j] = 0; 
								}	
				  		}	
				}
		}        
}

void deleteGraph()
{
	int i;
	for(i=0;i<V;i++)
		free(graph[i]);
	free(graph);
}

void printGraph()
{
	int i,j;
	for (i=0;i<V;i++)
    	{
    		printf("\n");
    		for (j=0;j<V;j++)
    			printf("\t%d",graph[i][j]);				
		}
}
