//This is the GeneralTypes.h

#ifndef _GENERAL_H
#define _GENERAL_H

#define START_N 'S'
#define END_N 'E'
#define WALL_N '#'
#define OPEN_N ' '
#define PATH_N '.'

typedef enum { False, True } Boolean;

typedef char* String;

//Definition of Map:
typedef char MapElement;
typedef char* MapLine;
typedef char** Map;

#endif
