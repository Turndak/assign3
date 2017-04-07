/*///////////////////////////////////////////
///										///
///	 string.c for CS201 assignment 1	///
///										///
///		Dakota Turner February 2017		///
		
	creates a string class in c
///										///
///////////////////////////////////////////*/
#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>
#include <string.h>
#include "string.h"

string *
newString(char *x)
{
	string *p = malloc(sizeof(string));
	p -> value = malloc(strlen(x) + 1);
	strcpy(p -> value, x);
	return p;
}

char * getString(string *v)
{
	return v -> value;
}

char *setString(string *v, char *x)
{
	char *old = malloc(sizeof(strlen(v -> value)));
	strcpy(old, v -> value);
	v -> value = malloc(sizeof(strlen(x)));
	strcpy(v ->value, x);
	return old;
}

void displayString(FILE *fp, void *v)
{
	fprintf(fp, "\"%s\"", getString(v));
}