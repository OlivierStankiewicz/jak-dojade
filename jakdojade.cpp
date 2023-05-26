#include "TwoWayList.h"
#include "Point.h"
#include "City.h"
#include "GraphLib.h"
#include "GeneralFunctions.h"

int main()
{
	int width, height;
	cin >> width >> height;
	char** map = new char* [height];
	for (int i = 0; i < height; i++)
		map[i] = new char[width];
	
	Node<City*>* listOfCities = readMap(width, height, map);
	int numOfCities = listOfCities->getListLen();
	Node<Node<City*>*>** tabOfNeighborLists = buildGraph(listOfCities, numOfCities, map, width, height);

	handleCommands(tabOfNeighborLists, numOfCities);

	for (int y = 0; y < height; y++)
		delete[] map[y];
	delete[] map;

	return 0;
}