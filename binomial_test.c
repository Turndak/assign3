#include "darray.h"
#include "binomial.h"
#include "integer.h"

int main(void)
{

	DArray *array = newDArray(displayInteger);
	insertDArray(array,newInteger(3));
	removeDArray(array);
	displayDArray(stdout,array);
	insertDArray(array,newInteger(4));
	insertDArray(array,newInteger(7));
	insertDArray(array,newInteger(2));
	displayDArray(stdout,array);
	for (int i = 0; i < 5000; i++) insertDArray(array,newInteger(7));
	for (int i = 0; i < 4999; i++) removeDArray(array);
	displayDArray(stdout,array);
	fprintf(stdout,"%d\n",getInteger(getDArray(array,0)));

	printf("\n");
	Binomial *heap = newBinomial(displayInteger,compareInteger,NULL);
	fprintf(stdout,"Inserting...\n");
	(void) insertBinomial(heap,newInteger(4));
	displayBinomial(stdout,heap);


	fprintf(stdout,"Inserting...\n");
	(void) insertBinomial(heap,newInteger(8));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Inserting...\n");
	(void) insertBinomial(heap,newInteger(16));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Inserting...\n");
	(void) insertBinomial(heap,newInteger(5));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Inserting...\n");
	(void) insertBinomial(heap,newInteger(1));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Extracting...\n");
	(void) extractBinomial(heap);
	displayBinomial(stdout,heap);
	fprintf(stdout,"Extracting...\n");
	(void) extractBinomial(heap);
	displayBinomial(stdout,heap);
	fprintf(stdout,"Extracting...\n");
	(void) extractBinomial(heap);
	displayBinomial(stdout,heap);
}