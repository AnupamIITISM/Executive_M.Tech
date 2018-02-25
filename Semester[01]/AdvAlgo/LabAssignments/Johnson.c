#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

float **graph,*distance; int V,**edge,k=0;
void createGraph();
void deleteGraph();
void printGraph(int);
int BellmanFord(int,int);
void reWeightEdges();
void Dijkstra(int);
int minDistance(float *,int *);
float maxDistance(float *);

int main(){    
 	int source,i,j,p;
 	printf("\nEnter the number of vertices in the graph: ");
 	scanf("%d",&V);
 	createGraph();
 	printf("\nCost Matrix of the given Graph:\n");
    printGraph(V);
	printf("\nCost Matrix for the modified graph:\n");
    printGraph(V+1);
	if(BellmanFord(V,k)==0){
		printf("\nNegative weight cycle present,exiting...");
		return 0;
	}
	reWeightEdges();
	for(p=0;p<V;p++){
		printf("\nShortest distance cost from source node[%d]:",p+1); 
		Dijkstra(p);		
	}	
    deleteGraph(); 
	return 0;
}

void createGraph(){
	int i,j,Y,eCount=0;
	graph = (float **)malloc((V+1) * sizeof(float *));
	for(i=0;i<V+1;i++)
         graph[i]=(float *)malloc((V+1)*sizeof(float));
    printf("\nConsidering a directed graph with costs associated with its edges..."); 
	printf("\nInput a few negative costs to test program's' adaptibility...");    
    for(i=0;i<V+1;i++){
			for(j=0;j<V+1;j++){
	  			if((i==j)||(i==V))	graph[i][j]=0.0;
	  			else if((j==V)&&(i!=V)) graph[i][j]=INT_MAX;
				else{
						printf("\nIs there an edge between node[%d] & node[%d]?:(Yes-1,No-0)",(i+1),(j+1));
						scanf("%d",&Y);
						if(Y==1){
								k++;
								printf("\nEnter the cost associated with this edge : ");
								scanf("%f",&graph[i][j]);
						}
						else	graph[i][j]=INT_MAX;
	  			}                	
			}
	}
	printf("\nTotal no. of edges in the graph = %d",k);
	edge=(int **)malloc(k*sizeof(int *));
	for(i=0;i<2;i++)
         edge[i]=(int *)malloc(2*sizeof(int));
	for(i=0;i<V;i++)
        for(j=0;j<V;j++){
            if(i!=j)
            	if(graph[i][j]!=INT_MAX)
                	{edge[eCount][0]=i;edge[eCount++][1]=j;}
        }
}

void deleteGraph(){
	int i;
	for (i=0;i<V;i++){
		free(graph[i]);
	}	
	free(graph);
}

void printGraph(int n){
	int i,j;
	for (i=0;i<n;i++){
    		printf("\n");
    		for (j=0;j<n;j++){
    				if(graph[i][j]==INT_MAX) printf("\t  X   ");
    				else printf("\t%.2f",graph[i][j]);
				}				
		}
}

int BellmanFord(int S,int E)
{
    int i,u,v,k;
    distance=(float *)malloc((V+1)*sizeof(float));
    for(i=0;i<V+1;i++){
    	 distance[i]=INT_MAX;
	}
    distance[S]=0;
    for(i=0;i<V;i++){
        for(k=0;k<E;k++){
            u=edge[k][0]; v=edge[k][1];
            if(distance[u]+graph[u][v]<distance[v])
                distance[v]=distance[u]+graph[u][v];
        }
    }
    for(k=0;k<E;k++){
            u=edge[k][0]; v=edge[k][1];
            if(distance[u]+graph[u][v]<distance[v])
                return 0;
        }
        return 1;
}

void reWeightEdges(){
	int i,j;
	for(i=0;i<V+1;i++)
        for(j=0;j<V+1;j++)
    		if(graph[i][j]!=0.0)
    			graph[i][j]=graph[i][j]+distance[i]-distance[j];
    printf("\n\nRe-Weighted edges after applying Bellmen-Ford...\n");
}

void Dijkstra(int src){
     float dist[V]; 
     int Visited[V],i,count,v;  
     for(i=0;i<V;i++) dist[i]=INT_MAX,Visited[i]=0;
     dist[src]=0.0;
     for(count=0;count<V-1;count++){
       int u = minDistance(dist,Visited);
       Visited[u]=1;
       for(v=0;v<V;v++)
         if(!Visited[v]&&graph[u][v]&&dist[u]!=INT_MAX&&dist[u]+graph[u][v]<dist[v])
            dist[v]=dist[u]+graph[u][v];
     }
	 for(i=0;i<V;i++){
		printf("\n\tTo node[%d] - ",i+1);
		if(dist[i]==INT_MAX) printf("Infinity");	
		else if(dist[i]<=maxDistance(dist))	printf("%f",dist[i]);
		else printf("Infinity");	
	 } 
}

int minDistance(float dist[], int Visited[]){
   int min=INT_MAX,min_index,v;
   for(v=0;v<V;v++)
     if(Visited[v]==0&&dist[v]<=min)
         {min=dist[v];min_index = v;}
  
   return min_index;
}

float maxDistance(float *dist){
	float max=0.0; int v;
	for(v=0;v<V;v++)
    	if(dist[v]>max)	max=dist[v];
	return max;	
}
