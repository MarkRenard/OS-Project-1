// visit.c was created by Mark Renard on 2/9/2020.
// This file contains an implimentation of the visit function which reads from
// an Options struct and prints optional information about a file along with its
// path to stdout, along with several static helper functions.

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
static void printNumLinksInInodeTable(struct stat *);
static void printUid(struct stat *);
static void printGid(struct stat *);
static void printSize(struct stat *);
static void printDateAndTimeModified(struct stat *);

// Reads from options, prints optional information and the path to a file
void visit(char * path, Options opts){
	struct stat * statPtr;  // Pointer to a stat structure

	// Gets reference to stat structure
	statPtr = getStats(path);	
	
	// Prints optional information	
	if (opts.type) printType(statPtr);
	if (opts.permissions) printPermissions(statPtr);
	if (opts.inodeLinks) printNumLinksInInodeTable(statPtr);
	if (opts.uid) printUid(statPtr);
	if (opts.gid) printGid(statPtr);
	if (opts.size) printSize(statPtr);
	if (opts.dateAndTimeModified) printDateAndTimeModified(statPtr);

	// Prints the path to the file
	printf(path);

	printf("\n");
}

// Returns a pointer to the stat struct for the file with the passed path
static struct stat * getStats(char * path){
	struct stat * statPtr = (struct stat *) malloc(sizeof(struct stat));

	if (lstat(path, statPtr) == -1){
		fprintf(stderr, "Couldn't get stats for %s\n", path);
	}

	return statPtr;
}

// Prints a letter indicating the type of the file
static void printType(struct stat * statPtr){
	char type[2];				// Type to be printed
	mode_t m = statPtr->st_mode;		// Mode member of stat struct

	// Sets a type character based on the type of the file
	if (S_ISBLK(m)) strcpy(type, "b");
	else if (S_ISCHR(m)) strcpy(type, "c");
	else if (S_ISDIR(m)) strcpy(type, "d");
	else if (S_ISFIFO(m)) strcpy(type, "p");
	else if (S_ISLNK(m)) strcpy(type, "l");
	else if (S_ISREG(m)) strcpy(type, "-");
	else if (S_ISSOCK(m)) strcpy(type, "s");
	else strcpy(type, " ");

	// Prints the type
	printf(type);
}

// Prints the file permissions using rwx notation
static void printPermissions(struct stat * statPtr){
	char permissions[11];        // buffer for permissions string
	mode_t m = statPtr->st_mode; // mode member for permission masking

	// Adds user permissions
	permissions[0] = (m & S_IRUSR ? 'r' : '-');
	permissions[1] = (m & S_IWUSR ? 'w' : '-');
	permissions[2] = (m & S_IXUSR ? 'x' : '-');
	
	// Adds group permissions
	permissions[3] = (m & S_IRGRP ? 'r' : '-');
	permissions[4] = (m & S_IWGRP ? 'w' : '-');
	permissions[5] = (m & S_IXGRP ? 'x' : '-');

	// Adds other permissions
	permissions[6] = (m & S_IROTH ? 'r' : '-');
	permissions[7] = (m & S_IWOTH ? 'w' : '-');
	permissions[8] = (m & S_IXOTH ? 'x' : '-');

	// Additional characters
	permissions[9] = ' ';
	permissions[10] = '\0';

	printf(permissions);
}

// Prints the number of links to the file
static void printNumLinksInInodeTable(struct stat * statPtr){
	printf("%d ", (int) statPtr->st_nlink);
}

// Prints the name of the user the file belongs to
static void printUid(struct stat * statPtr){
	struct passwd * pwPtr = getpwuid(statPtr->st_uid);
	
	char username[100];
	strcpy(username, pwPtr->pw_name);
	
	printf(username);
	printf(" ");
}

// Prints the name of the group the file belongs to	
static void printGid(struct stat * statPtr){
	struct group * groupPtr = getgrgid(statPtr->st_gid);
	printf(groupPtr->gr_name);
	printf(" ");
}

// Prints the size of the file in gigabytes, megabytes, kilobytes, or bytes
static void printSize(struct stat * statPtr){

	// Sizes to use for units
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

	printf("%4lu%c ", numUnits, unit);
}

// Prints the date and time of last modification
static void printDateAndTimeModified(struct stat * statPtr){
	char mtime[CTIME_SIZE];
	strncpy(mtime, ctime(&(statPtr->st_mtime)), CTIME_SIZE - 1);
	mtime[CTIME_SIZE - 2] = 0;
	printf(mtime);
	printf(" ");
}
	
