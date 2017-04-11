#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sll.h"
#include "queue.h"
#include "integer.h"
#include "binomial.h"
#include "darray.h"

#ifndef __VERTEX_INCLUDED__
#define __VERTEX_INCLUDED__

//supplied by jarobinson on the 201 forums
typedef struct Edge
{
	int from, to;
	int weight;
} Edge;


typedef struct Vertex
{
	int value;//int value
	int visited;//yee or nahh
	int ID;//key value
	int touched;//visited vertices
	struct Vertex *prev;//allows us to show the previous value of a vertex
	DArray *adjacentV;//dynamic array of adjacent vertices
	BinomialNode *node;
} Vertex;

typedef struct Adjacent
{
	//has a vertex element & a weight
	Vertex *vertex;
	int weight;
} Adjacent; 


extern Vertex *newVertex(int);
extern Adjacent *newAdjacency(int, int);
extern void displayVertex(FILE *, void *);
extern Edge *readData(FILE *);
extern Vertex *startVertex(DArray *);
extern void insertVertex(DArray *, int , int, int );//insert vertex into adjacecny list
extern Adjacent *findAdjacency(DArray *, int );//finds requested value in an adjacecny list
extern Vertex *findVertex(DArray *, int );//finds a specified vertex in a list
extern int compareVertex(void *, void *);
extern void update(void *, BinomialNode *);

#endif