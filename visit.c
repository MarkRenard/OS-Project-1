// visit.c was created by Mark Renard on 2/9/2020.
// This file contains an implimentation of the visit function, which prints
// information about a file to stdout

#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

#define CTIME_SIZE 26
#define KILO 1024ULL
#define MEGA 1048576ULL
#define GIGA 1073741824ULL

static struct stat * getStats(char * path);
static void printType(struct stat *);
static void printPermissions(struct stat *);

static void printUid(struct stat *);
static void printGid(struct stat *);
static void printSize(struct stat *);
static void printDateAndTimeModified(struct stat *);

void visit(char * path, Options opts){
	struct stat * statPtr;  // Pointer to a stat structure

	// Gets reference to stat structure
	statPtr = getStats(path);	
	
	if (opts.type) printType(statPtr);
	if (opts.permissions) printPermissions(statPtr);

	if (opts.uid) printUid(statPtr);
	if (opts.gid) printGid(statPtr);
	if (opts.size) printSize(statPtr);
	if (opts.dateAndTimeModified) printDateAndTimeModified(statPtr);

	printf(path);
	printf("\n");
	fflush(stdout);
	
}

static struct stat * getStats(char * path){
	struct stat * statPtr = (struct stat *) malloc(sizeof(struct stat));

	if (lstat(path, statPtr) == -1){
		fprintf(stderr, "Couldn't get stats for %s\n", path);
	}

	return statPtr;
}

static void printType(struct stat * statPtr){
	char type[2];				// Type to be printed
	mode_t m = statPtr->st_mode;		// Mode member of stat struct

	if (S_ISDIR(m)) strcpy(type, "d");
	else if (S_ISREG(m)) strcpy(type, "-");

	printf(type);
}

static void printPermissions(struct stat * statPtr){
	char permissions[11];
	mode_t m = statPtr->st_mode;

	permissions[0] = (m & S_IRUSR ? 'r' : '-');
	permissions[1] = (m & S_IWUSR ? 'w' : '-');
	permissions[2] = (m & S_IXUSR ? 'x' : '-');
	permissions[3] = (m & S_IRGRP ? 'r' : '-');
	permissions[4] = (m & S_IWGRP ? 'w' : '-');
	permissions[5] = (m & S_IXGRP ? 'x' : '-');
	permissions[6] = (m & S_IROTH ? 'r' : '-');
	permissions[7] = (m & S_IWOTH ? 'w' : '-');
	permissions[8] = (m & S_IXOTH ? 'x' : '-');
	permissions[9] = ' ';
	permissions[10] = '\0';

	printf(permissions);
}



static void printUid(struct stat * statPtr){
	struct passwd * pwPtr = getpwuid(statPtr->st_uid);
	
	char username[100];
	strcpy(username, pwPtr->pw_name);
	
	printf(username);
	printf(" ");
}
	
static void printGid(struct stat * statPtr){
	struct group * groupPtr = getgrgid(statPtr->st_gid);
	printf(groupPtr->gr_name);
	printf(" ");
}

// Prints the size of the file in gigabytes, megabytes, kilobytes, or bytes
static void printSize(struct stat * statPtr){
	unsigned long KB = 1024UL;
	unsigned long MB = 1024UL * 1024UL;
	unsigned long GB = 1024UL * 1024UL * 1024UL;

	// Retrieves the size of the file from the stat struct 
	unsigned long numBytes = (unsigned long) statPtr->st_size;
	unsigned long numUnits = numBytes;
	char unit = ' ';

	if (numBytes > KB){
		numUnits = numBytes / KB;
		unit = 'K';
	} else if (numBytes > MB) {
		numUnits = numBytes / MB;
		unit = 'M';
	} else if (numBytes > GB) {
		numUnits = numBytes / GB;
		unit = 'G';
	}

	printf("%5lu%c ", numUnits, unit);
}

static void printDateAndTimeModified(struct stat * statPtr){
	char mtime[CTIME_SIZE];
	strncpy(mtime, ctime(&(statPtr->st_mtime)), CTIME_SIZE - 1);
	mtime[CTIME_SIZE - 2] = 0;
	printf(mtime);
	printf(" ");
}
	
