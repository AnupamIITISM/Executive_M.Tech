/**
*
* Author - Nitish Bhattacharjee
*
**/
#include <stdio.h>
#include <stdlib.h>
//#include<conio.h>

#define INF 999.0

float **graph,**dist;
int V,handleINF=0;
void createGraph();
void deleteGraph();
void printGraph();
void FloydWarshall();

int main()
{    
 	int source;
 	freopen("FloydWarshall.txt","w",stdout);
	printf("\nEnter the number of vertices in the graph: ");
 	scanf("%d",&V);
 	createGraph();
 	printf("\nCost Matrix of the given Graph:\n");
    printGraph();
	FloydWarshall();
    deleteGraph(); 
	    
	//getch();
	return 0;
}

void createGraph()
{
	int i,j,Y;
	graph = (float **)malloc(V * sizeof(float *));
	dist = (float **)malloc(V * sizeof(float *));
	for (i=0; i<V; i++)
	{
		graph[i] = (float *)malloc(V * sizeof(float));
		dist[i] = (float *)malloc(V * sizeof(float));
	}
        
	printf("\nConsidering a directed graph with only non-negative cost cycle associated with its edges...");    
    for (i=0;i<V;i++)
    	{
			for (j=0;j<V;j++)
	  			{
	  				if(i==j)
						graph[i][j]=dist[i][j]=0.0;
					else
						{
							printf("\nIs there an edge between node[%d] & node[%d]?:(Yes-1,No-0)",(i+1),(j+1));
							scanf("%d",&Y);
							if(Y==1)
								{
									printf("\nEnter the cost associated with this edge : ");
									scanf("%f",&graph[i][j]);
									dist[i][j]=graph[i][j];
									if(graph[i][j]<0)
										handleINF+=graph[i][j];
								}
							else
								graph[i][j]=dist[i][j]=INF;
	  					}
				}
		}
}

void deleteGraph()
{
	int i;
	for (i=0;i<V;i++)
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
    				if(graph[i][j]>=INF+handleINF)
    					printf("\t  X   ");
    				else
    				printf("\t%.2f",graph[i][j]);
				}				
		}
}

void FloydWarshall()
{
  int i,j,k;
  
  for(k=0;k<V;k++) 
  	for(i=0;i<V;i++) 
    	for(j=0;j<V;j++)
        	if(dist[i][j]>dist[i][k]+dist[k][j]) 
          		dist[i][j]=dist[i][k]+dist[k][j];

  for(i=0;i<V;i++)
  	if(dist[i][i]<0)
    	printf("\nNegative-weight cycle found.");
      
  for(i=0;i<V;i++)
  	for(j=0;j<V;j++)
	{
		printf("\n\tFrom node[%d] to node[%d] - ",i+1,j+1);
		if(dist[i][j]>=INF+handleINF)
			printf("Infinite");
		else
			printf("%f",dist[i][j]);
	}
}

