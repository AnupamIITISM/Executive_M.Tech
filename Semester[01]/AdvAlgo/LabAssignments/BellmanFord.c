#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
 
typedef struct Edge
{
	int source,destination;
	float weight;
}Edge;
 
typedef struct Graph
{
    int V,E;
    Edge *edge;
}Graph;
 
Graph * createGraph(int V,int E)
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->V=V; graph->E=E; graph->edge=(Edge*)malloc(graph->E*sizeof(Edge));
    return graph;
}
 
void BellmanFord(Graph* graph,int source)
{
    int V=graph->V,E=graph->E,i,j,u,v;
    float StoreDistance[V],weight,maxEdgeCost=0.0;
    for (i=0;i<V;i++)
        StoreDistance[i]=INT_MAX;
    StoreDistance[source]=0.0;

    for(i=1;i<=V-1;i++)
    {
        for(j=0;j<E;j++)
        {
            u=graph->edge[j].source; v=graph->edge[j].destination;
            weight=graph->edge[j].weight;
            if(StoreDistance[u]+weight<StoreDistance[v])
                StoreDistance[v]=StoreDistance[u]+weight;
        }
    }
     
    for(i=0;i<E;i++)
    {
        u=graph->edge[i].source; v=graph->edge[i].destination;
        weight=graph->edge[i].weight;
        if(StoreDistance[u]+weight<StoreDistance[v])
        	printf("\nThis graph contains negative edge cycle\n");
    }
    
	for(i=0;i<E;i++)
        if(maxEdgeCost<graph->edge[i].weight)
                maxEdgeCost=graph->edge[i].weight;
    printf("\nMinimum path costs from source vertex[%d] are :",source); 
    for(i=0;i<V;i++){
    	if(StoreDistance[i]>maxEdgeCost)
    		printf("\n\tfor vertex[%d] : Infinity",i); 
    	else
	 		printf("\n\tfor vertex[%d] : %f",i,StoreDistance[i]); 
	}
	return;
}
 
int main()
{
    int V,E,S,i; 
    freopen("Bellmenford.txt","w",stdout);
    printf("\nEnter number of vertices in graph : "); scanf("%d",&V);
    printf("\nEnter number of edges in graph : "); scanf("%d",&E);
    printf("\nEnter your source vertex from where minimum costs are to be calculated : "); scanf("%d",&S);
     
    Graph *graph=createGraph(V,E);
    for(i=0;i<E;i++){
        printf("\nEnter the following values for the %d-th edge",i+1);
        printf("\tSource Vertex ? :"); scanf("%d",&graph->edge[i].source);
        printf("\tDestination Vertex ? :"); scanf("%d",&graph->edge[i].destination);
        printf("\tAssociated Weight ? :"); scanf("%f",&graph->edge[i].weight);
    }
 
    BellmanFord(graph,S); 
    return 0;
}
