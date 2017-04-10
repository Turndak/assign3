#include "vertex.h"
#include "scanner.h"
#include <limits.h>

Vertex *startVertex(DArray *);//locates the minimum value as the start vertex
void insertVertex(DArray *, int , int , int);//insert vertex into adjacecny list
Adjacent *findAdjacecny(DArray *, int);//finds requested value in an adjacecny list
Vertex *findVertex(DArray *, int);//finds a specified vertex in a list

Vertex *newVertex(int value)
{//initialize all paramters of a new Vertex
	Vertex *newV = malloc(sizeof(Vertex));
	newV->value = value;
	newV->visited = 0
	newV->ID = INT_MAX;//initializes all new vertice's keys to infinity(or as close to it as possible)
	newV->touched = 0;//visited vertices
	newV->prev = NULL;//allows us to show the previous value of a vertex
	newV->adjacentV = newDArray(displayInteger);//dynamic array of adjacent vertices
	newV->node = NULL;
	
	return newV;
}

Adjacent *newAdjacency(int vertex, int weight)
{
	Adjacent *a = malloc(sizeof(Adjacent));
	a->vertex = newVertex(vertex);
	a->weight = weight;

	return a;
}

void displayVertex(FILE *fp, void *value)
{
	Vertex *v = (Vertex *) value;
	fprintf(fp, "%d", v->value);
	if(v->prev != v && v->prev != NULL)//if vertex is not equal to itself and not NULL
	{
		//follow assign3 output specifications
		fprintf(fp, "(%d)", v->prev->value);
		fprintf(fp, "%d", v->ID);
	}
}

//get edge details from file
Edge *readData(FILE *fp)//Edge function that reads edge weight and associated vertices from a file
{
	char c = readChar(fp);
	if (c == EOF)
	{
		return NULL;
	}

	ungetc(c, fp);
	Edge *e = malloc(sizeof(Edge));
	e->from = readInt(fp);
	e->to = readInt(fp);

	//read in the next thing after vertex details
	//could be a ';' or a weight value
	char *unknown = readToken(fp);
	if(strcmp(unknown, ";"))
	{//if next value is not a ';' convert the token value to an integer
		e->weight = atoi(unknown);
		//free the now known value
		free(unknown);
		//and reset it for the next read
		unknown = readToken(fp);
	}
	else//if unknown value is equal to ';'
	{
		//set the edge weight to 1
		e->weight = 1;
		free(unknown);
	}	
	
	//return the edge details
	return e;
}

Vertex *startVertex(DArray *d)//locates the minimum value as the start vertex
{
	if(sizeDArray(d) == 0)
	{
		return NULL;
	}

	Vertex *minimum = (Vertex *) getDArray(d, 0);
	int i = 1;
	while(i < sizeDArray(d))
	{
		Vertex *v = getDArray(d, i);
		if(v->value < minimum->value)
		{
			minimum = v;//update minimum
		}
	}
	return minimum;
}

void insertVertex(DArray *d, int vert, int friend, int weight)//insert vertex into adjacecny list
{
	Vertex *v = findVertex(d, vert);//find vertex in list
	Adjacent *a = findAdjacecny(d, friend);//find neighbor in list

	if(v != NULL)//vertex is in list
	{
		//check if the adjacent vertex is in the adjacency list
		if(a != NULL)//neighbor is in list as well
		{
			//update the weight if it has changed
			if(a->weight > weight)
			{
				a->weight = weight;
			}
		}
		else//adjacent vertex(neighbor) not in the list, so add it
		{
			a = newAdjacency(friend, weight);//create a new adjacency with the value
			insertDArray(v->adjacentV, a);//add it to the vertex's neighbors
		}
	}
	else//v is NOT in the adjacency list
	{
		v = newVertex(vert);//creates a new vertex using the first value read in from the file
		Adjacent *adj = newAdjacency(friend, weight);
		//insert the new vertex and his friend into their respective arrays
		insertDArray(v->adjacentV, adj);
		insertDArray(d, v);
	}	
}

Vertex *findVertex(DArray *d, int vertex)//finds a specified vertex in a list
{
	int i=0;
	while(i < sizeDArray(d))
	{
		Vertex *v = getDArray(d, i);
		if(v->value == vertex)
		{
			return v;
		}
		++i;
	}
	return NULL;
}

Adjacent *findAdjacency(DArray *d, int vertex)//finds requested value in an adjacecny list
{
	int i=0;
	while(i < sizeDArray(d))
	{
		Adjacent *a = getDArray(d, i);
		if(a->vertex->value == vertex)//neighbor has a vertex element as a parameter
		{
			return a;
		}
		++i;
	}
	return NULL;
}

