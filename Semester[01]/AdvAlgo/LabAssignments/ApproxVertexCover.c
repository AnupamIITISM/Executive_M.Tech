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
void createGraph();
void deleteGraph();
void printGraph();
void approxVertexCover();
void removeAdjcents(int,int);

int main()
{    
 	printf("\nEnter the number of vertices in the graph: ");
 	scanf("%d",&V);
 	
 	createGraph();
 	printf("\nInitial Graph:\n");
    printGraph(); 
    printf("\n\nMarked edges in the graph:\n");
    approxVertexCover();
    deleteGraph(); 
	    
	//getch();
	return 0;
}

void createGraph()
{
	int i,j,Y;
	graph = (int **)malloc(V * sizeof(int *));
	for (i=0; i<V; i++)
         graph[i] = (int *)malloc(V * sizeof(int));
         
    for (i=0;i<V;i++)
    	for (j=0;j<V;j++)
    		graph[i][j]=0;
 
    for (i=0;i<V;i++)
    	{
			for (j=0;j<V;j++)
	  			{
	  				if(i>=j)
						continue;
					else
						{
							printf("\nIs there an edge between node[%d] & node[%d]?:(Yes-1,No-0)",(i+1),(j+1));
							scanf("%d",&Y);
							if(Y==1)
								{
									graph[i][j] = 1;
									graph[j][i] = 1;
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
    			{
    				if(graph[i][j]==999)
    					printf("\tX");
    				else
    				printf("\t%d",graph[i][j]);
				}				
		}
}

void approxVertexCover()
{
  int i,j,visited[V];
  
  for(i=0;i<V;i++)
  	visited[i]=0;
  for(i=0;i<V;i++)
    for(j=0;j<V;j++)
    	if(graph[i][j]==1)
    		removeAdjcents(i,j);

  for(i=0;i<V;i++)
    for(j=0;j<V;j++)
    	if(graph[i][j]==999)
    	   visited[i]=1;
	
  printf("\n");  
  printGraph();
  printf("\nOne possible approx vertex cover: "); 	
  for(i=0;i<V;i++)
  	{
		if(visited[i]==1)
			printf("[Node %d] ",(i+1)); 	
  	}	   	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          	
}


void removeAdjcents(int i,int j)
{
	int k;
	for(k=0;k<V;k++)
    	{
    		graph[i][k]=0;
    		graph[k][j]=0;
		}
	graph[i][j]=999;
	graph[j][i]=0;
}

