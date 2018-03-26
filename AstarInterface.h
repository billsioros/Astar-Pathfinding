//This is the AstarInterface.h File:

#ifndef ASTARIMP_H
#define ASTARIMP_H

#include "AstarTypes.h"

Map _map;
int lines, columns, start_i, start_j, end_i, end_j, current_i, current_j;
ShellMap AstarMap;

//Astar//
void AllocateShellMap();
void LocateSEnodes();
void InitShellMap();
void FindMinF();
Boolean WithinBoarders(int , int );
void ToClosedList(int , int );
void ToOpenList(int , int );
void Parent(int , int );
Boolean Diagonal(int , int );
void RecordGcost(int , int );
void RecordFcost(int , int );
Boolean BetterPathExists(int , int );
Boolean EmptyOpenList();
Boolean PathExists();
void DrawPath();
void AdjacentShellsOperations();
void AstarALG();

#endif
