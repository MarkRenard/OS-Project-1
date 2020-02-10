// Main.c was created by Mark Renard on 2/5/2020.
// This file specifies the driver for a utility which traverses a file system
// in breadth first order beginning with either the current working directory
// or the argued directory. See README for details. 

#include "queue.h"
#include "breadthfirst.h"
#include "options.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char * const argv[]){
	char ** dir;	// Pointer to root directory string	
	Options opts;	// Struct that indicates selected options

	// Allocates memory for root directory string
	dir = (char**) malloc(sizeof(char**));

	// Parses options
	opts = parseOptions(argc, argv, dir);

	// Creates a new queue
	Queue * q = newQueue();

	// Traverses the file structure with root *dir in breadth frist order
	breadthfirst(*dir, q, opts, argv[0]);

	return 0;
}
