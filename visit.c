// visit.c was created by Mark Renard on 2/9/2020.
// This file contains an implimentation of the visit function, which prints
// information about a file to stdout

#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void visit(char * path, Options * opts){
	char ** line;		// The line to be printed
	struct stat * statPtr;  // Pointer to a stat structure

	// Initializes line
	line =(char**) malloc(sizeof(char**));
	*line = (char*) malloc(10000);
	strcpy(*line, "\0");

	printf("%s\n", path);
}


