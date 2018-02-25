/**
*
* Author - Nitish Bhattacharjee
*
**/
#include<stdio.h>
#include<stdlib.h> 
//#include<conio.h>

int **graph;
int V;
void createGraph();
void deleteGraph();
void printGraph();
void topSortSourceRemoval();

int main()
{
  	freopen("TopologicalSort_SourceNodeRemoval.txt","w",stdout);
	printf("\nEnter the number of vertices in the graph: ");
 	scanf("%d",&V);
 	
 	createGraph();
 	printf("\nInitial Graph:\n");
    printGraph(); 
	topSortSourceRemoval(); 
    deleteGraph();
 
    return 0;
}

void topSortSourceRemoval()
{
	int i,j,k;
	int *indeg,*visited;
	
	indeg=(int *)malloc(V*sizeof(int));
	visited=(int *)malloc(V*sizeof(int));
	
	for(i=0;i<V;i++)
	{
        indeg[i]=0;
        visited[i]=0;
    }

    for(i=0;i<V;i++)
		for(j=0;j<V;j++)
           	indeg[i]=indeg[i]+graph[j][i];
          
 	j=0;
    printf("\nThe topological sorting order for the supplied graph is   ");
 
    while(j<V)
		{
    		for(k=0;k<V;k++)
				{
            		if((indeg[k]==0) && (visited[k]==0))
						{
                			printf("->%d",(k+1));
                			visited[k]=1;
            			}
            		for(i=0;i<V;i++)
						{
                			if(graph[i][k]==1)
                    		indeg[k]--;
            			}
        		}	
 			j++;
    	}
}

void createGraph()
{
	int i,j,Y;
	graph = (int **)malloc(V * sizeof(int *));
	
	for (i=0; i<V; i++)
        graph[i] = (int *)malloc(V * sizeof(int));

	printf("\nConsidering a DAG..hence has directed edges and cann't have cycles");
    
	for (i=0;i<V;i++)
    	{
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
