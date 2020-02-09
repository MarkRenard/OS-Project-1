// options.c was created by Mark Renard on 2/8/2020
// This file defines a function which parses arguments and
// returns a struct indicating which options have been selected

#include "options.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

Options parseOptions(int argc, char * const argv[], char ** dir){
	// Creates string for help and error messages
	char * usageFormat = "Usage: %s [-h] [-L -d -g -i -p =s =t =u | -l] [dirname]\n";
	char * usageMsg = malloc(strlen(usageFormat) + strlen(argv[0]));
	sprintf(usageMsg, usageFormat, argv[0]);

	int option; // Stores each option from getopt
	Options opts = { 0, 0, 0, 0, 0, 0, 0, 0 }; // Initializes options structure


	while((option = getopt(argc, argv, "hLtpiugsdl")) != -1){
		switch(option){
		case 'h':
			printf("%s\n", usageMsg);
			exit(0);
		case 'L':
			opts.links = 1;
			break;
		case 't':
			opts.type = 1;
			break;
		case 'p':
			opts.permissions = 1;
			break;
		case 'i':
			opts.inodeLinks = 1;
			break;
		case 'u':
			opts.uid = 1;
			break;
		case 'g':
			opts.gid = 1;
			break;
		case 's':
			opts.size = 1;
			break;
		case 'd':
			opts.dateAndTimeModified = 1;
			break;
		case 'l':
			opts.type = 1;
			opts.permissions = 1;
			opts.inodeLinks = 1;
			opts.uid = 1;
			opts.gid = 1;
			opts.size = 1;
			opts.dateAndTimeModified = 1;
			break;
		default:
			fprintf(stderr, "Invalid option!\n%s", usageMsg);
			exit(1);
		}
		
	}

	if(argc > optind){
		*dir = malloc(strlen(argv[optind]) + 1);
		strcpy(*dir, argv[optind]);
	} else {
		*dir = malloc(2);
		sprintf(*dir, ".");
		printf("%s\n", *dir);
		fflush(stdout);
	}

	return opts;
}


