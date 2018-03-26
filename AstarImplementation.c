//This is the AstarImplementation.c File

#include "AstarInterface.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX(A,B) ((A > B) ? (A) : (B))

//Astar//

void AllocateShellMap()
{
	int i;
	AstarMap = (ShellMap) malloc(sizeof(Shellptr)*lines);
	if (AstarMap == NULL) {
		printf("|ERROR|: The system is exhausted!\n");
		return;
	}
	for (i = 0; i < lines; i++) {
		AstarMap[i] = (Shellptr) malloc(sizeof(Shell)*columns);
		if (AstarMap[i] == NULL) {
			printf("|ERROR|: The system is exhausted!\n");
			return;
		}
	}
}

void LocateSEnodes()
{
	int i, j, found = 0;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			if (_map[i][j] == START_N) {
				start_i = i;
				start_j = j;
				found++;
			}
			if (_map[i][j] == END_N) {
				end_i = i;
				end_j = j;
				found++;
			}
			if (found == 2) return;
		}
	}
}

void InitShellMap()
{
	int i, j;
	for (i = 0; i < lines; i++) {
		for ( j = 0; j < columns; j++) {
			AstarMap[i][j].list = None;
			AstarMap[i][j].Walkable = ((_map[i][j] != WALL_N) ? True : False);
			AstarMap[i][j].i = i;
			AstarMap[i][j].j = j;
			AstarMap[i][j].h = (MAX(end_i - i, i - end_i) + MAX(end_j - j, j - end_j)) * 10;
			AstarMap[i][j].g = 0;
			AstarMap[i][j].f = 0;
			AstarMap[i][j].parent = NULL;
		}
	}
}

void FindMinF()
{
	int i, j, min_F = 10000;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			if (AstarMap[i][j].list == Open && AstarMap[i][j].f <= min_F) {
				current_i = i;
				current_j = j;
				min_F = AstarMap[i][j].f;
			}
		}
	}
}

Boolean WithinBoarders(int i, int j)
{
	if (i < 0 || j < 0 || i >= lines || j >= columns)
		return False;
	else
		return True;
}

void ToClosedList(int i, int j)
{
	AstarMap[i][j].list = Closed;
}

void ToOpenList(int i, int j)
{
	AstarMap[i][j].list = Open;
}

void Parent(int i, int j)
{
	AstarMap[i][j].parent = &( AstarMap[current_i][current_j] );
}

Boolean Diagonal(int i, int j)
{
	if(current_i != i && current_j != j)
		return True;
	else
		return False;
}

void RecordGcost(int i, int j)
{
	AstarMap[i][j].g = AstarMap[current_i][current_j].g + ((Diagonal(i,j)) ? 15 : 10);
}

void RecordFcost(int i, int j)
{
	AstarMap[i][j].f = AstarMap[i][j].g + AstarMap[i][j].h;
}

Boolean BetterPathExists(int i, int j)
{
	if (AstarMap[current_i][current_j].g + ((Diagonal(i,j)) ? 15 : 10) < AstarMap[i][j].g)
		return True;
	else
		return False;
}

Boolean EmptyOpenList()
{
	int i, j;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			if (AstarMap[i][j].list == Open) return False;
		}
	}
	
	return True;
}

Boolean PathExists()
{
	if (AstarMap[end_i][end_j].list == Closed)
		return True;
	else
		return False;
}

void DrawPath()
{
	Shellptr CurrentShell = AstarMap[end_i][end_j].parent;
	while (CurrentShell->parent != NULL) {
		_map[CurrentShell->i][CurrentShell->j] = PATH_N;
		CurrentShell = CurrentShell->parent;
	}
}

void AdjacentShellsOperations()
{
	//I added the !Diagonal(i, j) function in the first if statement
	//so that only the horizontal and vertical moves are considered legal
	int i, j;
	for (i = current_i - 1; i <= current_i + 1; i++)
		for(j = current_j - 1; j <= current_j + 1; j++)
			if (WithinBoarders(i, j) && !Diagonal(i, j))
				if (AstarMap[i][j].Walkable == True && AstarMap[i][j].list != Closed)
					if (AstarMap[i][j].list != Open) {
						ToOpenList(i, j);
						Parent(i, j);
						RecordGcost(i, j);
						RecordFcost(i, j);
					} else {
						if (BetterPathExists(i, j)) {
							Parent(i, j);
							RecordGcost(i, j);
							RecordFcost(i, j);
						}
					}
}

void AstarALG()
{
	current_i = start_i, current_j = start_j; 
	AstarMap[current_i][current_j].list = Open;
	
	do {
		FindMinF();
		ToClosedList(current_i, current_j);
		AdjacentShellsOperations();
	} while(!PathExists() && !EmptyOpenList());
}
