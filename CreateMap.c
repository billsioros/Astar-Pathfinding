//This is the CreateMap.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "GeneralTypes.h"

Map AllocateMap(int , int );
void WriteMapToFile(Map , int, int );

int main(void)
{
	//Get the Dimensions and the Concentration of the Map:
	int lines, columns, concentration;
	
	printf("\n/CREATE RANDOM MAP/\n---------------------------------------------\n");
	printf("\n/Lines/\n");
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
	
	printf("\n/Concentration of Walls/\n");
	do {
		printf("|Please enter an integer between 0 and 100|: ");
		scanf("%d", &concentration);
		fflush(stdin);
	} while (concentration < 0 || concentration > 100);
	
	//Allocate Memory for the Map:
	Map _map = AllocateMap(lines, columns);
	
	//Create Kinda-Random Map:
	srand(time(NULL));
	
	//Insert Open and Closed Nodes Randomly into the Map:
	int i, j;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			if ((rand() % 100) + 1 <= concentration)
				_map[i][j] = WALL_N;
			else
				_map[i][j] = OPEN_N;
		}
	}
	
	//Set the position of the S and E nodes:
	_map[rand() % lines][rand() % columns] = START_N;
	
	int random_x, random_y;
	do {
		random_x = rand() % lines;
		random_y = rand() % columns;
	} while (_map[random_x][random_y] == START_N);
	_map[random_x][random_y] = END_N;
	
	//Write Map to File:
	WriteMapToFile(_map, lines, columns);

	return 0;
}

Map AllocateMap(int lines, int columns)
{	
	Map _map = (Map) malloc(sizeof(MapLine) * lines);
	if (_map == NULL) {
		printf("|ERROR: The system is exhausted!|\n");
		return NULL;
	}
	
	int i;
	
	for (i = 0; i < lines; i++) {
		_map[i] = (MapLine) malloc(sizeof(MapElement) * columns);
		if (_map[i] == NULL) {
			printf("|ERROR: The system is exhausted!|\n");
			return NULL;
		}
	}
	
	return _map;
}

void WriteMapToFile(Map _map, int lines, int columns)
{
	int M_code;
	String M_name = (String) malloc(20 *sizeof(char));
	
	do {
		//Create Random File Name:
		M_code = rand() % 1000;
		sprintf(M_name, "RandomMap%.3d.txt", M_code);
		
		//Try to access the .txt file:
	} while (access(M_name, F_OK) != -1);
	
	FILE *fptr = fopen(M_name, "w");
	
	if (fptr == NULL) {
		printf("|ERROR|: Failed to open the specified .txt File\n\n");
		return;
	}
	
	//Write Map To File:
	fprintf(fptr, "%d\n%d\n", lines, columns);
	
	int i, j;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			fprintf(fptr, "%c", _map[i][j]);
		}
		fprintf(fptr, "%c", '\n');
	}
}
