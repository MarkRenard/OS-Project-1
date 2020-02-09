// breadthfirst.c was created by Mark Renard on 2/8/2020
// This file defines a function which traverses a file system in breadth-first order

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

char * getPath(char *, struct dirent *);
void visit(char *);
int isADirectory(char *);

void breadthfirst (char * root, Queue * q){
	char * currentPath;		// The current absolute path
	DIR * currentDir;		// The current DIR

	struct dirent * nextDirent;	// The next dirent
	
	// Visits each file in breadth first order
	enqueue(root, q);
	while ((currentPath = dequeue(q)) != NULL){
		currentDir = opendir(currentPath);

		// Visits each file directly below currentPath
		while (nextDirent = readdir(currentDir)){
			char * nextPath = getPath(currentPath, nextDirent);
			if (notSelfOrParent(nextPath)){
				visit(nextPath);
				if (isADirectory(nextPath)){
					enqueue(nextPath, q);
				}
			}
		}
	}
}

// Returns the name member of the dirent param appended to the path param
char * getPath(char * pathParam, struct dirent * direntParam){
	char * path = malloc(strlen(pathParam) + strlen(direntParam->d_name) + 1);

	strcpy(path, pathParam);
	strcat(path, "/");
	strcat(path, direntParam->d_name);

	return path;
}

// Prints the path
void visit(char * path) {
	printf("%s\n", path);
}

// Returns true if path is a direcoty. Adapted from Unix Systems Programming p. 157
int isADirectory(char * path) {
	struct stat statbuf;

	if (stat(path, &statbuf) == -1)
		return 0;
	else
		return S_ISDIR(statbuf.st_mode);
}

// Returns true if the path does not end in /* or /**
int notSelfOrParent(char * path){
	int pathLength = strlen(path);
	if (pathLength < 3) return 1;	

	char * last2 = (char *) malloc(3);
	strcpy(last2, &path[pathLength - 2]);	
	if (strcmp(last2, "/.") == 0) return 0;

	char * last3 = (char *) malloc(4);
	strcpy(last3, &path[pathLength - 3]);
	if (strcmp(last3, "/..") == 0) return 0;

	return 1;
}				
