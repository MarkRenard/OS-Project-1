// options.h was created by Mark Renard on 2/8/2020
// This file defines a struct used to indicate selected options
// and contians a prototype for a function that parses options.

#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct Options {
	int links;
	int type;
	int permissions;
	int inodeLinks;
	int uid;
	int gid;
	int size;
	int dateAndTimeModified;
} Options;

Options parseOptions(int argc, char * const argv[], char ** dir);

#endif

