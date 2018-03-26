//This is the AstarTypes.h File

#ifndef ASTARTYPES_H
#define ASTARTYPES_H

#include "GeneralTypes.h"

//Definition of struct Shell:
typedef enum { None = -1, Closed, Open } List;

typedef struct ShellTag* Shellptr;

typedef struct ShellTag {
	List list;
	Boolean Walkable;
	int i;
	int j;
	int h;
	int g;
	int f;
	Shellptr parent;
} Shell;

typedef Shellptr* ShellMap;

#endif
