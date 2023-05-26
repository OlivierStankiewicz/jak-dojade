#pragma once
#include "Point.h"
#include "TwoWayList.h"

class City: public Point
{
public:
	City(int x, int y, int distance);
	City(int distance, char* name);
	void getCityName(int mapWidth, int mapHeight, char** map);
	bool inBounds(int x, int y, int mapWidth, int mapHeight);
	void checkNeighbor(Node<City*>*& listOfNeighbors, Node<City*>*& queue, int mapWidth, int mapHeight, bool** visited, char** map, int deltaX, int deltaY);
	bool isIsolated(int mapWidth, int mapHeight, char** map);

	int distanceFromSource;
	char* name;

private:
	bool validNameCharacter(char a);
	bool firstOrLast(int x, int y, int mapWidth, int mapHeight, char** map);
	char* readName(int x, int y, int mapWidth, int mapHeight, char** map);
};

