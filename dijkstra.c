#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "darray.h"
#include "binomial.h"
#include "integer.h"
#include "vertex.h"

//updates the node pointer when bubble up is called
void update(void *value, BinomialNode *n)
{
	Vertex *v = (Vertex *) value;
	v->node = n;
}

/*void dijkstra(FILE *fp, )
{

	//freeform layout

	DArray* edges = newDArray(NULL);
	DArray* vertices = newDArray(NULL);

	// read in the data
	readData(fp, edges, vertices, );

	// create an array to save the old vertex values
	int length = sizeDArray(vertices);
	int* transform = malloc(sizeof(int) * length);

	// save the vertex value
	for(int i = 0 ; i < length; ++i) 
	{
		transform[i] = *(int*)getDArray(vertices);
	}

	// convert all the vertex values to their array index
	for(int i = 0 ; i < sizeDArray(edges); ++i) 
	{
		Edge* e = (Edge*)getDArray(edges);
		e->to = indexOf(e->to, transform);    // iterate through transform and return index found
		e->from = indexOf(e->to, transform);
	}
}
*/
int main(int argc, char **argv)
{
	//use the following to fill the adjacency list
	FILE *fp = fopen(argv[1], "r");
	Edge *e = readData(fp);
	while (e != NULL)
	{
		printf("from: %d\n", e->from);
		printf("to: %d\n", e->to);
		printf("weight: %d\n", e->weight);
		free(e);
		e = readData(fp);
	}
	/*if(argc < 2 || argc >=3)
	{
		fprintf(stderr, "Incorrect amount of arguments\n", );
	}

	//read in graph details from file
	FILE *fp = fopen(argv[1], "r");

*/

	return 0;
}