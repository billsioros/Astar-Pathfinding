//This is the menu.h file

#ifndef __MENU_H__
#define __MENY_H__

#include "GeneralTypes.h"

//Interface functions:
void Announcer_P();
void Announcer_M();
void Menu();
void Quit();

//General functions:
void RemoveNewline(String );

//Map functions:
Boolean ValidMapLine(MapLine );
Boolean ValidMap();
void ReadMap_Keyboard ();
void ReadMap_File ();
void AllocateMap();
void FreeMap();
void printMap();
void SolveMap();

#endif
