#include "GeneralFunctions.h"

Node<City*>* readMap(int width, int height, char** map)
{
	Node<City*>* listOfCities = NULL;
	getchar();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			map[y][x] = getchar();
			if (map[y][x] == '*')
			{
				City* c = new City(x, y, 0);
				listOfCities = listOfCities->addFirst(c);
			}
		}
		getchar();
	}

	return listOfCities;
}


char* getName(char* buffor, int bufforSize)
{
	int nameLen=0;
	for(int i=0; i<bufforSize; i++)
	{
		char input = getchar();

		if (input == ' ')
		{
			buffor[i] = '\0';
			nameLen = i + 1;
			break;
		}

		else
			buffor[i] = input;
	}

	char* name = new char[nameLen];

	for (int i = 0; i < nameLen; i++)
		name[i] = buffor[i];

	return name;
}

bool compareCharTab(char* a, char* b)
{
	int i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (a[i] != b[i])
			return false;
		i++;
	}

	return true;
}