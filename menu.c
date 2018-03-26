//This is the menu.c file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AstarInterface.h"
#include "menu.h"
#define BUFF 2000
#define _KEYBOARD_ 1
#define _FILE_ 2
#define _QUIT_ 3

//Interface functions:
void Announcer_P()
{
	printf("\n&&-----------&&\n  PATHFINDING\n&&-----------&&\n");
}

void Announcer_M()
{
	printf("\n&&----&&\n  MENU\n&&----&&\n");
}

void Menu()
{
	Announcer_M();
	
	_map = NULL;
	printf("\n/Input Methods/\n-----------\n|1|. KEYBOARD\n|2|. FILE\n|3|. Quit\n-----------\n\n");
	int answer;
	do {
		printf("|Please enter an integer between 1 and 3|: ");
		scanf("%d", &answer);
		fflush(stdin);
	} while (answer < 1 || answer > 3);
	
	switch (answer) {
		case _KEYBOARD_:
			ReadMap_Keyboard();
			break;
		case _FILE_:
			ReadMap_File();
			break;
		case _QUIT_:
			Quit();
			break;
	}
	
	if (_map != NULL) {
		if (!ValidMap()) {
			printf("\n|Attention|:\n");
			printf("|1|. /Valid Symbols/: '%c', '%c', '%c', '%c'\n", START_N, END_N, OPEN_N, WALL_N);
			printf("|2|. The Map must contain one starting and one finishing node EXACTLY!['%c','%c']\n", START_N, END_N);
			printf("|3|. The number of lines and columns must be integers with a value of 1 to 1000\n\n");
			FreeMap();
		}
	}
	
	if (_map != NULL) {
		SolveMap();
		FreeMap();
	}
	
	if (answer != _QUIT_) Menu();
}

void Quit()
{
	fflush(stdin);
}

//General functions:
void RemoveNewline(String str)
{
	char *pos = strchr(str, '\n');
	if(pos != NULL)	*pos = '\0';
}

//Map functions:
Boolean ValidMapLine(MapLine str)
{
	while (*str != '\0') {
		if (*str != WALL_N && *str != OPEN_N && *str != START_N && *str != END_N) return False;
		str++;
	}
	
	return True;
}

Boolean ValidMap()
{
	int i, countS = 0, countE = 0;
	for (i = 0; i < lines; i++) {
		if (strchr(_map[i], START_N) != NULL) countS++;
		if (strchr(_map[i], END_N) != NULL) countE++;
	}

	if(countS != 1 || countE != 1) return False;
	for (i = 0; i < lines; i++) {
		if(!ValidMapLine(_map[i])) return False;
	}
	
	if(lines < 1 || columns < 1 || lines > 1000 || columns > 1000) return False;
}

void ReadMap_Keyboard ()
{	
	printf("---------------------------------------------\n");
	printf("\n|Attention|:\n");
	printf("|1|. /Valid Symbols/: '%c', '%c', '%c', '%c'\n", START_N, END_N, OPEN_N, WALL_N);
	printf("|2|. The Map must contain one starting and one finishing node EXACTLY!['%c','%c']\n", START_N, END_N);
	printf("|3|. The number of lines and columns must be integers with a value of 1 to 1000\n\n");
	do {
		printf("|Please enter an integer between 1 and 1000|: ");
		scanf("%d", &lines);
		fflush(stdin);
	} while (lines < 1 || lines > 1000);
	
	printf("\n/Columns/\n");
	do {
		printf("|Please enter an integer between 1 and 1000|: ");
		scanf("%d", &columns);
		fflush(stdin);
	} while (columns < 1 || columns > 1000);
	
	AllocateMap();
	
	printf("\n/Map/:\n\n");
	MapLine tempStr = (MapLine) malloc(sizeof(MapElement) * BUFF);
	int i = 0;
	while (i < lines) {
		fgets(tempStr, BUFF, stdin);
		RemoveNewline(tempStr);
		strcpy(_map[i++], tempStr);
	}
}

void ReadMap_File ()
{
	String tempStr = (String) malloc(sizeof(char) * BUFF);
	
	printf("|Please specify the .txt file you would like to open|: ");
	fgets(tempStr, BUFF, stdin);
	RemoveNewline(tempStr);
	
	FILE *fptr = fopen (tempStr, "r");
	if (fptr == NULL ) {
		printf("|ERROR|: Unable to open the specidied .txt folder\n");
		return;
	}
	
	fgets(tempStr, BUFF, fptr);
	RemoveNewline(tempStr);
	lines = atoi(tempStr);
	
	fgets(tempStr, BUFF, fptr);
	RemoveNewline(tempStr);
	columns = atoi(tempStr);
		
	AllocateMap();
	
	int i = 0;
	while (i < lines) {
		fgets(tempStr, BUFF, fptr);
		RemoveNewline(tempStr);
		strcpy(_map[i++], tempStr);
	}
}

void AllocateMap()
{	
	_map = (Map) malloc(sizeof(MapLine) * lines);
	if (_map == NULL) {
		printf("|ERROR: The system is exhausted!|\n");
		return;
	}
	
	int i;
	for (i = 0; i < lines; i++) {
		_map[i] = (MapLine) malloc(sizeof(MapElement) * columns);
		if (_map[i] == NULL) {
			printf("|ERROR: The system is exhausted!|\n");
			return;
		}
	}
}

void FreeMap()
{
	int i;
	for (i = 0; i < lines; i++) {
		free(_map[i]);
		_map[i] = NULL;
	}
	
	free(_map);
	_map = NULL;
}

void printMap()
{
	int i, j;
	printf("Map/:\n\n");
	
	printf("     +");
	for (i = 0; i < 2*columns - 1; i++)	printf("-");
	printf("+");
	printf("\n");
	
	for (i = 0; i < lines; i++) {
		printf("%.4d |", i);
		for (j = 0; j < columns; j++) {
			if (j < columns - 1)
				printf("%c ", _map[i][j]);
			else
				printf("%c", _map[i][j]);
		}
		printf("|\n");
	}
	
	printf("     +");
	for (i = 0; i < 2*columns - 1; i++)	printf("-");
	printf("+");
	printf("\n");
}

void SolveMap()
{
	printf("--------------------------------------------------------------------------------------\n");
	Announcer_P();
	
	printf("/Unsolved ");
	printMap();
	printf("\n/Running The A* Pathfinding Algorithm/\n");
	system("PAUSE");
	
	AllocateShellMap();
	LocateSEnodes();
	InitShellMap();
	AstarALG();
	
	printf("--------------------------------------------------------------------------------------\n");
	if (PathExists()) {
		DrawPath();
		printf("/Solved ");
		printMap();
		printf("\n/The Path consists of the '+' nodes/\n");
	} else {
		printf("/There is no Valid Path/\n");
	}
}
