/**
*
* Author - Nitish Bhattacharjee
*
**/
#include <stdio.h>
#include <stdlib.h>
//#include<conio.h>

int **graph;
int V;
int *visited;

void createGraph();
void deleteGraph();
void printGraph();
void DFS(int);
     
int main()
{
	freopen("DFS_Output.txt","w",stdout);
	printf("\nEnter the number of vertices in the graph: ");
 	scanf("%d",&V);
 	
 	createGraph();
 	printf("\nInitial Graph:\n");
    printGraph(); 
    printf("\nDFS traversal starting from node[1] is: \n");
    DFS(0);
    deleteGraph(); 
	    
	//getch();
	return 0;
}
 
void createGraph()
{
	int i,j,Y;
	graph = (int **)malloc(V * sizeof(int *));
	visited = (int *)malloc(V * sizeof(int));
	
	for (i=0; i<V; i++)
        graph[i] = (int *)malloc(V * sizeof(int));

	printf("\nConsidering a DAG..hence has directed edges and cann't have cycles");
    
	for (i=0;i<V;i++)
    	{
			visited[i]=0;
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

void DFS(int i)
{
    int j;
    printf("\t%d",i+1);
    visited[i]=1;
    
    for(j=0;j<V;j++)
       if(!visited[j]&&graph[i][j]==1)
            DFS(j);
}
