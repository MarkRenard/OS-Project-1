// Main.c was created by Mark Renard on 2/5/2020.
// For now, this serves as a driver for a string queue implementation. 

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
	char ** dir = (char**) malloc(sizeof(char**));
	Options opts;
	
	opts = parseOptions(argc, argv, dir);
	Queue * q = newQueue();

	breadthfirst(*dir, q, opts);
}
