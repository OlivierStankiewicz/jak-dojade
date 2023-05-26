#include "City.h"
#include <iostream>

City::City(int x, int y, int distance) : Point(x, y), distanceFromSource(distance), name(NULL)
{}

City::City(int distance, char* name)
	:City(-1, -1, distance)
{
	this->name = name;
}

void City::getCityName(int mapWidth, int mapHeight, char** map)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (inBounds(x + i, y + j, mapWidth, mapHeight) && validNameCharacter(map[y + j][x + i]) && firstOrLast(x + i, y + j, mapWidth, mapHeight, map))
			{
				name = readName(x + i, y + j, mapWidth, mapHeight, map);
			}
		}
	}
}

bool City::validNameCharacter(char a)
{
	if (a >= 'A' && a <= 'Z')
		return true;

	if (a >= '0' && a <= '9')
		return true;

	return false;
}

bool City::firstOrLast(int x, int y, int mapWidth, int mapHeight, char** map)
{
	if (x == 0 || x == mapWidth - 1)
		return true;

	if (!validNameCharacter(map[y][x - 1]) || !validNameCharacter(map[y][x + 1]))
		return true;

	return false;
}

bool City::inBounds(int x, int y, int mapWidth, int mapHeight)
{
	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
		return true;

	return false;
}

char* City::readName(int x, int y, int mapWidth, int mapHeight, char** map)
{
	while (inBounds(x - 1, y, mapWidth, mapHeight) && validNameCharacter(map[y][x - 1]))
		x--;

	int start = x;

	while (inBounds(x + 1, y, mapWidth, mapHeight) && validNameCharacter(map[y][x + 1]))
		x++;

	char* newName = new char[x - start + 2];

	for (int i = start; i <= x; i++)
		newName[i - start] = map[y][i];
	newName[x - start +1] = '\0';

	return newName;
}

void City::checkNeighbor(Node<City*>*& listOfNeighbors, Node<City*>*& queue, int mapWidth, int mapHeight, bool** visited, char** map, int deltaX, int deltaY)
{
	City* n = new City(this->x + deltaX, this->y + deltaY, this->distanceFromSource + 1);
	if (this->inBounds(n->x, n->y, mapWidth, mapHeight) && !visited[n->y][n->x] && (map[n->y][n->x] == '*' || map[n->y][n->x] == '#'))
	{
			visited[n->y][n->x] = true;

			if (map[n->y][n->x] == '#')
				queue = queue->addLast(n);

			else
			{
				n->getCityName(mapWidth, mapHeight, map);
				listOfNeighbors = listOfNeighbors->addFirst(n);
			}
			return;
	}

	delete n;
}

bool City::isIsolated(int mapWidth, int mapHeight, char** map)
{
	if (this->inBounds(this->x - 1, this->y, mapWidth, mapHeight) && (map[this->y][this->x - 1] == '*' || map[this->y][this->x - 1] == '#'))
		return false;

	if (this->inBounds(this->x + 1, this->y, mapWidth, mapHeight) && (map[this->y][this->x + 1] == '*' || map[this->y][this->x + 1] == '#'))
		return false;

	if (this->inBounds(this->x, this->y - 1, mapWidth, mapHeight) && (map[this->y - 1][this->x] == '*' || map[this->y - 1][this->x] == '#'))
		return false;

	if (this->inBounds(this->x, this->y + 1, mapWidth, mapHeight) && (map[this->y + 1][this->x] == '*' || map[this->y + 1][this->x] == '#'))
		return false;

	return true;
}