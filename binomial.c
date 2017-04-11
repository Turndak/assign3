#include "binomial.h"
#include "integer.h"
#include "queue.h"
#include "darray.h"

static void consolidate(Binomial *, BinomialNode *);
static void merge (Binomial *,DArray *);
static BinomialNode *bubbleUp(Binomial *, BinomialNode *);
static BinomialNode *combine(Binomial *, BinomialNode *, BinomialNode *);
static BinomialNode *getSubHeap(DArray *, int);//int is an index
static void updateExtreme(Binomial *, BinomialNode *);
static void findNewExtreme(Binomial *);
static void levelOrderTraversal(FILE *, BinomialNode *);

/*******************************BinomialNode*******************************/

//supplied by the assign3 description
struct BinomialNode
{
	void *value;
	DArray *children;
	struct BinomialNode *parent;
	void (*display)(FILE *,void *);
};

BinomialNode *newBinomialNode(void (*display)(FILE *,void *),void *value)
{
	BinomialNode *n = malloc(sizeof(BinomialNode));
	n->value = value;
	n->children = newDArray(display);//why do we pass display as a parameter?
	n->parent = n;
	n->display = display;

	return n;
}

//returns the node size (degree)
static int nodeDegree(BinomialNode *n)
{
	return sizeDArray(n->children);
}

void displayBinomialNode(FILE *fp,BinomialNode *n)
{
	n->display(fp, n->value);
	fprintf(fp, "-%d", nodeDegree(n));
	if(n != n->parent)
	{
		fprintf(fp, "(");
		n->parent->display(fp, n->parent->value);
		fprintf(fp, "-%d)", nodeDegree(n->parent));
	}

}

/*******************************Binomial***********************************/

//supplied by the assign3 description
struct Binomial
{
	DArray *rootlist;
	int (*compare)(void *,void *);
	void (*update)(void *,BinomialNode *);
	BinomialNode *extreme;
	int size;
	void (*display)(FILE *,void *);
};

Binomial *newBinomial(
    void (*d)(FILE *,void *),        //display
    int (*c)(void *,void *),         //comparator
    void (*u)(void *,BinomialNode *) //updater
    )
{
	Binomial *b = malloc(sizeof(Binomial));
	b->display = d;
	b->compare = c;
	b->update = u;
	b->rootlist = newDArray(d); //still confused why display is passed in
	b->extreme = NULL;
	b->size = 0;

	return b;
}

BinomialNode *insertBinomial(Binomial *b,void *value)
{
	//set parent of n to n && set children pointer of n to a new dynamic array
	BinomialNode *n = newBinomialNode(b->display, value);

	updateExtreme(b,n);

	//consolidate b and new node (n)
	consolidate(b, n);

	//increment b's size
	b->size++;

	//return n
	return n;
	printf("here\n");
}

int sizeBinomial(Binomial *b)
{
	return b->size;
}

void deleteBinomial(Binomial *b,BinomialNode *n)
{
	decreaseKeyBinomial(b, n, NULL);
	(void) extractBinomial(b);
}

void decreaseKeyBinomial(Binomial *b,BinomialNode *n,void *value)
{
	n->value = value;
	BinomialNode *vp =  bubbleUp(b, n);
	updateExtreme(b, vp);
}

void *extractBinomial(Binomial *b)
{
	BinomialNode *y = b->extreme;

	int i = 0;
	while(sizeDArray(b->rootlist) > i)
	{
		if(getDArray(b->rootlist, i)==y)
		{
			setDArray(b->rootlist, i, NULL);
		}
		++i;
	}
	merge(b, y->children);
	b->size--;
	void *temp = y->value;
	free(y);
	findNewExtreme(b);
	return temp;
}

//formats the output and calls the level order traversal for the actual display
void displayBinomial(FILE *fp,Binomial *b)
{
	if(sizeBinomial(b) == 0)
	{
		fprintf(fp, "0:\n");
        return;
	}
	int i = 0;
	while(i < sizeDArray(b->rootlist))
	{
		if(getSubHeap(b->rootlist, i) != NULL)
		{
			levelOrderTraversal(fp, (BinomialNode *) getSubHeap(b->rootlist, i));
			fprintf(fp, "----\n");
		}
		++i;
	}
}

/****************************************************************/
/***************************HELPERS******************************/
/****************************************************************/

static void levelOrderTraversal(FILE *fp, BinomialNode *n)
{
	queue *newQ = newQueue(n->display);
	enqueue(newQ, n);//enqueue root and a null character to represent first level
	enqueue(newQ, NULL);

	BinomialNode *x;

	int breadthLevel = 0;
	fprintf(fp, "%d: ", breadthLevel);
	while (sizeQueue(newQ)) //while the queue is not empty 
	{
		x = dequeue(newQ); //begin dequeue
		if(sizeQueue(newQ) == 0)
		{
			fprintf(fp, "\n");
			break;
		}

		else if(x == NULL)	//if the dequeue value is null
		{
			fprintf(fp,"\n");
			enqueue(newQ, NULL);	//enqueue null to represent end of level
			breadthLevel++;
			if(sizeQueue(newQ) > 0)
			{
				fprintf(fp, "%d: ", breadthLevel);
			}
		}
		else
		{			
			displayBinomialNode(fp, x);
			
			if(peekQueue(newQ) != NULL) 
			{
				fprintf(fp, " ");
			}

			for(int i = 0; i < sizeDArray(x->children); i++)
			{
				enqueue(newQ, (BinomialNode *) getSubHeap(x->children, i));
			}
		}
	}
}

static void updateExtreme(Binomial *b, BinomialNode *n)
{
	if (b->extreme == NULL)
	{
		b->extreme = n;
	}
	else if(b->compare(b->extreme->value, n->value) > 0) //if b's extreme value is greater than n's value, then update the extreme value to n
	{
		b->extreme = n;
	}
}

static void findNewExtreme(Binomial *b)
{
	b->extreme = NULL;
	BinomialNode *n = NULL;
	//traverse the subheap and find the new extreme value
	for(int i=0; i < sizeDArray(b->rootlist); i++)
	{
		n = getSubHeap(b->rootlist, i);
		if(n != NULL)
		{
			updateExtreme(b, n);
		}
	}
}

static BinomialNode *getSubHeap(DArray *a, int degree)//degree is the index
{
	if(degree > sizeDArray(a))
	{
		fprintf(stderr, "Fatal error\n");
		exit(-1);
	}
	else if(degree == sizeDArray(a))
	{
		return NULL;
	}

	return getDArray(a, degree);
}

static void consolidate(Binomial *b, BinomialNode *n)
{
	//set a variable named degree to the number of n's children using array size
	int degree = nodeDegree(n);

	while (getSubHeap(b->rootlist, degree) != NULL)
	{
		//set n to the combination of n and the subtree stored at the index
		n = combine(b, n, getSubHeap(b->rootlist, degree));
		setDArray(b->rootlist, degree, NULL);//set slot at index(degree) to null, since that slot is now empty
		degree++;

		//if index is equal to the size of the heaps rootlist
		//then insert NULL into the rootlist at index
		if(degree == sizeDArray(b->rootlist))
		{
			insertDArray(b->rootlist, NULL);
		}
	}
	setDArray(b->rootlist, degree, n);
}

static void merge(Binomial *b, DArray *donor)
{
	for(int index = 0; index < sizeDArray(donor); index++)
	{
		//Binomial node n set to an array cast to a binomial node
		BinomialNode *n = (BinomialNode *) getDArray(donor, index);
		n->parent = n;
		consolidate(b, n);
	}
	free(donor);
}

static BinomialNode *bubbleUp(Binomial *b, BinomialNode *n)
{
	if(n->parent == n)
	{
		return n;
	}
	else if(b->compare(n->parent->value, n->value) < 0)
	{
		return n;
	}
	else
	{
		b->update(n->value, n->parent);
		b->update(n->parent->value, n);

		void *temp = n->value;
		n->value = n->parent->value;
		n->parent->value = temp;

		return bubbleUp(b, n->parent);
	}
}


static BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y)
{
	int i = 0;
	if(b->compare(x->value, y->value) < 0)
	{
		i = nodeDegree(y);
		setDArray(x->children, i, y);//sets y into x's child array @ index i
		y->parent = x;

		return x;
	}
	else
	{
		i = nodeDegree(x);
		setDArray(y->children, i, x);//place x in y's child array at index i
		x->parent = y;

		return y;
	}
}
