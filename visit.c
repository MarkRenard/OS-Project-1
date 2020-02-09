// visit.c was created by Mark Renard on 2/9/2020.
// This file contains an implimentation of the visit function, which prints
// information about a file to stdout

#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static void addType(char *, struct stat *);

void visit(char * path, Options opts){
	char * line;		// The line to be printed
	struct stat * statPtr;  // Pointer to a stat structure

	// Initializes line
	line = (char *) malloc(10000);
	strcpy(line, "aaa");	
	printf("line:   %s\n", line);

	// Gets reference to stat structure
	lstat(path, statPtr);

	if (opts.type) addType(line, statPtr);

	printf("line:   %s\n", line);
	printf("path:   %s\n", path);
	strcat(line, path);
	printf("concat: %s\n\n", line);

}

static void addType(char * line, struct stat * statPtr){
	mode_t m = statPtr->st_mode;

	if (S_ISDIR(m)) strcat(line, "d");
	else if (S_ISREG(m)) strcat(line, "-");
}


