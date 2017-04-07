#include <stdio.h>
#include <stdlib.h>
#include "darray.h"
#include "binomial.h"
#include "integer.h"

int main(void)
{
	DArray *a = newDArray(displayInteger);
	insertDArray(a, newInteger(0));
	insertDArray(a, newInteger(1));
	insertDArray(a, newInteger(2));
	insertDArray(a, newInteger(3));
	insertDArray(a, newInteger(4));
	insertDArray(a, newInteger(0));
	insertDArray(a, newInteger(1));
	insertDArray(a, newInteger(2));
	insertDArray(a, newInteger(3));
	insertDArray(a, newInteger(4));
	insertDArray(a, newInteger(0));
	insertDArray(a, newInteger(1));
	insertDArray(a, newInteger(2));
	insertDArray(a, newInteger(3));
	insertDArray(a, newInteger(4));
	insertDArray(a, newInteger(2));
	insertDArray(a, newInteger(3));
	insertDArray(a, newInteger(4));
	insertDArray(a, newInteger(0));
	insertDArray(a, newInteger(1));
	insertDArray(a, newInteger(2));
	insertDArray(a, newInteger(3));
	insertDArray(a, newInteger(4));
	removeDArray(a);
	removeDArray(a);
	removeDArray(a);
	removeDArray(a);
	removeDArray(a);
	removeDArray(a);
	removeDArray(a);
	removeDArray(a);
	removeDArray(a);

	setDArray(a, 5, newInteger(80085));
	
	printf("size: %d\n",sizeDArray(a));

	displayDArray(stdout, a); 
	// printf("\n");

	// displayInteger(stdout, getDArray(a, 5));
	// printf("\n");
}