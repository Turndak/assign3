#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "darray.h"
#include "binomial.h"
#include "integer.h"
#include "vertex.h"

static void displayForest(FILE *, queue *);

static void dijkstra(FILE *fp, Binomial *h, DArray *list)
{
	Vertex *minVert = startVertex(list);//get the minimum value from the adjacency list
	
	//reset some of the Vertex pointers
	minVert->prev = minVert;
	minVert->ID = 0;
	queue *nodesVisited = newQueue(displayVertex);

	//following is straight from David McCoy's pseudoCode from Basic Outline of Dijkstra
	while(sizeBinomial(h) != 0)
	{
		Vertex *u = (Vertex *) extractBinomial(h);//extract from heap vertex u
		if(u->prev == NULL)
		{
			u->ID = 0;
			displayForest(fp, nodesVisited);
			//clear visited vertices queue
			nodesVisited = newQueue(displayVertex);
		}
		enqueue(nodesVisited, u);//add u to nodes visited
		u->visited = 1; //marks u as visited
		//for each vertex adjacent with u(go through its neighbors)
		for(int i = 0; i < sizeDArray(u->adjacentV); ++i)
		{
			//Let v be the vertex adjacent with u
			Adjacent *a = (Adjacent *) getDArray(u->adjacentV, i);
			Vertex *v = findVertex(list, a->vertex->value);
			// if (v has not been visited)
			if(v->visited != 1)
			{			
				// 	if (v does not have a parent or u.key + e.weight < v.key)
				if((u->ID + a->weight) < v->ID || v->prev == NULL)
				{
					//Set v's parent to u
					v->prev = u;
					//Update v's key to the new lower distance
					v->ID = (u->ID + a->weight);
					//Update the number of steps for v to be its parent's + 1
					v->touched = v->prev->touched + 1;
					//Call decreaseKey on v's binomial node pointer "position"
					decreaseKeyBinomial(h, v->node, v);
				}						
			}
		}
	}
	//display the visited vertices queue (guaranteed to have stuff in it)
	displayForest(fp, nodesVisited);
}	

static void displayForest(FILE *fp, queue *branch)
{
	if(sizeQueue(branch) == 0)
	{
		return;
	}

	//displaying the subgraphs pseudocode taken from david Mccoy's post on the Basic Outline of Dijkstra
	/*you can display a subgraph with the visited vertices queue 
	by inserting everything in the queue into a heap and then 
	pulling them out to sort them, and you should make an array 
	of queues where each index of the array has a queue which 
	holds vertices with that number of steps. so you extract 
	verts out of your new heap and add them into the appropriate 
	queue by the number of steps in the array, and then go through 
	each queue in the queue array and dequeue and print whatcha gotta 
	print. the number of steps represents the level each vertex is at 
	in the graph, so for each queue you can print the line number, and 
	then print the vertices in it!*/

	Binomial *priority = newBinomial(displayVertex, compareVertex, update);
	Vertex *v = NULL;//declare a vertex to be used in the heap

	//step through the size of the queue, dequeuing setting each dequeued value to a Vertex
	//then insert this Vertex into a binomial heap

	int i = 0, stepSize = 0, size = sizeQueue(branch);
	
	while(i < size)
	{
		void *q = dequeue(branch);
		v = q;//(Vertex *) dequeue(branch);
		if(v->touched > stepSize)//if the number of visited(or touched nodes) is greater than the step size
		{
			stepSize = v->touched; //then set the step size to the number of visited nodes
		}
		insertBinomial(priority, v);//insert the vertex into the heap
		i++;
	}

	//make an array of queues where each index of the array has a 
	//queue which holds vertices with that number of steps
	//then extract vertices out of the new heap and add them to 
	//the appropriate queue based on the number of steps in the array
	//the number of steps represents the level
	queue *levelOrder[stepSize];
	i = 0;//reset i
	while(i <= stepSize)
	{
		levelOrder[i] = newQueue(displayVertex);
		i++;
	}

	i=0;//reset i
	while(i < size)
	{
		v = (Vertex *) extractBinomial(priority);
		enqueue(levelOrder[v->touched], v);
		i++;
	}

	//go through each queue in the array and dequeue and print 
	i = 0;
	while(i <= stepSize)
	{
		fprintf(fp, "%d : ", i);
		while(sizeQueue(levelOrder[i]) != 0)
		{
			v = (Vertex *) dequeue(levelOrder[i]);
			displayVertex(stdout, v);
			if(sizeQueue(levelOrder[i]) > 0)
			{
				fprintf(fp, " ");
			}
		}
		fprintf(fp, "\n");
		i++;
	}
	fprintf(fp, "----\n");
}


int main(int argc, char **argv)
{
	if(argc < 2 || argc >=3)
	{
		fprintf(stderr, "Incorrect amount of arguments\n");
	}
	//use the following to fill the adjacency list
	FILE *fp = fopen(argv[1], "r");
	DArray *list = newDArray(displayVertex);
	// fillAdjList(list, fp);

	Edge *e = readData(fp);
	while (e != NULL)
	{
		// printf(" v1: %d\n", e->from);
		// printf("v2: %d\n", e->to);
		// printf("weight: %d\n", e->weight);

		insertVertex(list, e->from, e->to, e->weight);
		insertVertex(list, e->to, e->from, e->weight);
		free(e);
		e = readData(fp);
	}

	Binomial *heap = newBinomial(displayVertex, compareVertex, update);
	
	int i = 0;
	while(i < sizeDArray(list))
	{

		Vertex *v = getDArray(list, i);
		v->node = insertBinomial(heap, v);
		++i;
	}	
	dijkstra(stdout, heap, list);

	fclose(fp);
}