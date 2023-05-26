#pragma once
#include "TwoWayList.h"
#include "City.h"

Node<City*>* readMap(int width, int height, char** map);
char* getName(char* buffor, int bufforSize);
bool compareCharTab(char* a, char* b);