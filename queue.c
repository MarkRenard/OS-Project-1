// queue.c was created by Mark Renard on 2/5/2020
// This file defines functions that operate on a queue data structure.

#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char * string;
	struct Node * previous;
} Node;

typedef struct Queue {
	Node * back;
	Node * front;
} Queue;

static Queue q;

// Adds a string to the back of the queue
void enqueue(char * newString){
	// Creates a new node and assigns the new string
	Node * newNode = (Node *) malloc(sizeof(Node));
	newNode->string = malloc(strlen(newString));
	strcpy(newNode->string, newString);
	
	// Adds new node to queue	
	if (q.back != NULL){
		// Adds to back if queue is not empty
		q.back->previous = newNode;
		q.back = newNode;
	} else {
		// Adds to back and front if queue is empty
		q.back = newNode;
		q.front = newNode;		
	}
}

// Removes a string from the front of the queue and returns it
char * dequeue(){
	// Returns null if the queue is already empty
	if (q.front == NULL) return NULL;

	// Stores the return value
	char * returnVal = q.front->string;

	// Removes the front node from the queue
	Node * front = q.front;  // Temporary reference to front
	q.front = front->previous; // Assigns new front of queue
	free(front);

	// Returns string and the front of the queue
	return returnVal;
}
