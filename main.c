// Main.c was created by Mark Renard on 2/5/2020.
// This file is the driver for an application that..

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const int argv){
	// Test driver for queue data structure
	enqueue("One\n\0");
	enqueue("Two\n\0");

	// Dequeues test strings and prints them
	char * line = dequeue();
	while (line != NULL){
		printf(line);
		fflush(stdin);
		line = dequeue();
	}

	printf("Sup\n");

}
