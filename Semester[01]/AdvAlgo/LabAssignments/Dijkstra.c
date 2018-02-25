/**
*
* Author - Nitish Bhattacharjee
*
**/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//#include<conio.h>

float **graph;
int V;
void createGraph();
void deleteGraph();
void printGraph();
void Dijkstra(int);
int minDistance(float *,int *);
float maxDistance(float *);

int main()
{    
 	int source;
 	//freopen("Dijkstra.txt","w",stdout);
	printf("\nEnter the number of vertices in the graph: ");
 	scanf("%d",&V);
 	createGraph();
 	printf("\nCost Matrix of the given Graph:\n");
    printGraph();
	
	printf("\nEnter the source node to calculate shortest path from : "); 
	scanf("%d",&source);
	Dijkstra(source-1);
    deleteGraph(); 
	    
	//getch();
	return 0;
}

void createGraph()
{
	int i,j,Y;
	graph = (float **)malloc(V * sizeof(float *));
	for (i=0; i<V; i++)
         graph[i] = (float *)malloc(V * sizeof(float));
    
	printf("\nConsidering a directed graph with non-negative costs associated with its edges...");    
    for (i=0;i<V;i++)
    	{
			for (j=0;j<V;j++)
	  			{
	  				if(i==j)
						graph[i][j]=0.0;
					else
						{
							printf("\nIs there an edge between node[%d] & node[%d]?:(Yes-1,No-0)",(i+1),(j+1));
							scanf("%d",&Y);
							if(Y==1)
								{
									printf("\nEnter the cost associated with this edge : ");
									scanf("%f",&graph[i][j]);
								}
							else
								graph[i][j]=INT_MAX;
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
    				if(graph[i][j]==INT_MAX)
    					printf("\t  X   ");
    				else
    				printf("\t%.2f",graph[i][j]);
				}				
		}
}

void Dijkstra(int src)
{
     float dist[V]; 
     int Visited[V],i,count,v;  
     for(i=0;i<V;i++)
        dist[i]=INT_MAX,Visited[i]=0;
     dist[src]=0.0;
     for(count=0;count<V-1;count++)
     {
       int u = minDistance(dist,Visited);
       Visited[u]=1;
       for(v=0;v<V;v++)
         if(!Visited[v]&&graph[u][v]&&dist[u]!=INT_MAX&&dist[u]+graph[u][v]<dist[v])
            dist[v]=dist[u]+graph[u][v];
     }
     printf("\nCosts for Single source shortest paths for the given graph using node[%d] as source are:",src+1);
	 for(i=0;i<V;i++)
	 {
		printf("\n\tTo node[%d] - ",i+1);
		if(dist[i]==INT_MAX)
			printf("Infinity");	
		else if(dist[i]<=maxDistance(dist))
			printf("%f",dist[i]);
		else
			printf("Infinity");	
	 } 
}

int minDistance(float dist[], int Visited[])
{
   int min=INT_MAX,min_index,v;
   for(v=0;v<V;v++)
     if(Visited[v]==0&&dist[v]<=min)
         {min=dist[v];min_index = v;}
  
   return min_index;
}

float maxDistance(float *dist)
{
	float max=0.0; int v;
	for(v=0;v<V;v++)
    	if(dist[v]>max)
    		max=dist[v];
	return max;	
}
