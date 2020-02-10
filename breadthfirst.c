// breadthfirst.c was created by Mark Renard on 2/8/2020
// This file defines a function which traverses a file system in breadth-first order

#include "queue.h"
#include "options.h"
#include "visit.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void printErrorAndExit(char * path, const char * progName);
char * getPath(char *, struct dirent *);
int shouldFollow(char *, int);
int notSelfOrParent(char *);

// Prints selected info on files in breadth first order starting with root
void breadthfirst (char * root, Queue * q, Options opts, const char * progName){
	char * currentPath;		// The current absolute path
	DIR * currentDir;		// The current DIR
	struct dirent * nextDirent;	// The next dirent
	
	// Visits each file in breadth first order
	if (shouldFollow(root, opts.links)){
		enqueue(root, q);
	}

	while ((currentPath = dequeue(q)) != NULL){
		currentDir = opendir(currentPath);
		
		// Prints an error and exits if no such directory exists
		if (currentDir == NULL) printErrorAndExit(currentPath, progName);

		// Visits each file directly below currentPath
		while ( (nextDirent = readdir(currentDir)) ){

			// Retrieves the path to each file below currentDir
			char * nextPath = getPath(currentPath, nextDirent);
			if (notSelfOrParent(nextPath)){
				
				// Prints info on file as defined in visit.c
				visit(nextPath, opts); 

				// Equeues directories and links to them on -L
				if (shouldFollow(nextPath, opts.links)){
					enqueue(nextPath, q);
				}
			}
		}
	}
}

// Prints an error message and exists
void printErrorAndExit(char * path, const char * progName){
	char errMsg[100];

	sprintf(errMsg, "%s: Error:  Cannot open %s", progName, path);
	perror(errMsg);

	exit(1);
}
 
// Returns the name member of the dirent param appended to the path param
char * getPath(char * pathParam, struct dirent * direntParam){
	char * path; // The return value
	
	// Allocates memory for new path
	path = malloc(strlen(pathParam) + strlen(direntParam->d_name) + 2);

	// Appends file name to path
	strcpy(path, pathParam);
	strcat(path, "/");
	strcat(path, direntParam->d_name);

	return path;
}

// True if the file is a directory, or if -L was entered and it's a link to one 
int shouldFollow(char * path, int followLinks) {
	struct stat statbuf; // stat struct for passed path
	int statFlag = 0;    // Flag indicating that a stat struct was returned 

	// Determines whether to follow links based on -L option
	if (followLinks)
		statFlag = stat(path, &statbuf);
	else
		statFlag = lstat(path, &statbuf);

	// Returns true if stat struct returned and the file is a directory
	if (statFlag == -1)
		return 0;
	else
		return S_ISDIR(statbuf.st_mode);
}

// Returns true if the path does not end in /. or /..
int notSelfOrParent(char * path){
	int pathLength;	// The length of the path argument
	char * last2;	// The last 2 characters of the path
	char * last3;	// The last 3 characters of the path
	
	// Returns true if the path 
	pathLength = strlen(path);
	if (pathLength < 3) return 1;	

	// Returns false if the last to characters are /.
	last2 = (char *) malloc(3);
	strcpy(last2, &path[pathLength - 2]);	
	if (strcmp(last2, "/.") == 0) return 0;

	// Returns false if the last two characters are /..
	last3 = (char *) malloc(4);
	strcpy(last3, &path[pathLength - 3]);
	if (strcmp(last3, "/..") == 0) return 0;

	return 1;
}				
