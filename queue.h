// queue.h was created by Mark Renard on 2/5/2020
// This file defines function prototypes for a string queue structure

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
	char * string;
	struct Node * previous;
} Node;

typedef struct Queue {
	Node * back;
	Node * front;
} Queue;

Queue * newQueue();
void enqueue(char *, Queue * q);
char * dequeue(Queue * q);

#endif

