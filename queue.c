// queue.c was created by Mark Renard on 2/5/2020
// This file defines functions that operate on a queue data structure.

#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include <stdio.h>

Queue * newQueue(){
	Queue * qPtr = malloc(sizeof(Queue));
	qPtr->front = NULL;
	qPtr->back = NULL;
	return qPtr;
}

// Adds a string to the back of the queue
void enqueue(char * newString, Queue * q){
	// Creates a new node and assigns the new string
	Node * newNode = (Node *) malloc(sizeof(Node));
	newNode->string = malloc(strlen(newString));
	strcpy(newNode->string, newString);
	newNode->previous = NULL;
	
	// Adds new node to queue	
	if (q->back != NULL){
		// Adds to back if queue is not empty
		q->back->previous = newNode;
		q->back = newNode;
	} else {
		// Adds to back and front if queue is empty
		q->back = newNode;
		q->front = newNode;
	}
}

// Removes a string from the front of the queue and returns it
char * dequeue(Queue * q){
	// Returns null if the queue is already empty
	if (q->front == NULL) return NULL;

	// Stores the string to be returned
	char * returnVal = malloc(strlen(q->front->string) + 1);
	strcpy(returnVal, q->front->string);

	// Removes the front node from the queue
	Node * front = q->front;  // Temporary reference to front
	q->front = front->previous; // Assigns new front of queue
	free(front);
	
	// Sets queue back to null if empty
	if(q->front == NULL) q->back = NULL;
	
	// Returns string and the front of the queue
	return returnVal;
}
