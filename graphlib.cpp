#include "GraphLib.h"
#include "GeneralFunctions.h"
const int BUFFOR_SIZE = 10;
const int MY_INFINITY = 2147483647;

int hash1(char* name, int arraySize)
{
	int i = 0, key = 0;
	while (name[i] != '\0')
	{
		key += name[i] * 433;
		key %= arraySize;
		i++;
	}
	return key;
}

void addCity(Node<City*>* cityWithNeighbors, int tabSize, Node<Node<City*>*>** tabOfNeighborLists)
{
	int index = hash1(cityWithNeighbors->data->name, tabSize);
	tabOfNeighborLists[index] = tabOfNeighborLists[index]->addFirst(cityWithNeighbors);
}

Node<City*>* findNeighbors(City* main, int mapWidth, int mapHeight, char** map)
{
	if (main->isIsolated(mapWidth, mapHeight, map))
		return NULL;

	Node<City*>* listOfNeighbors = NULL;
	Node<City*>* queue = NULL;
	bool** visited = new bool* [mapHeight];
	for (int y = 0; y < mapHeight; y++)
	{
		visited[y] = new bool[mapWidth];
		for (int x = 0; x < mapWidth; x++)
			visited[y][x] = false;
	}

	visited[main->y][main->x] = true;
	queue = queue->addLast(main);
	while (queue)
	{
		City* c = queue->getFirst()->data;
		queue = queue->removeFirst();

		c->checkNeighbor(listOfNeighbors, queue, mapWidth, mapHeight, visited, map, -1, 0);
		c->checkNeighbor(listOfNeighbors, queue, mapWidth, mapHeight, visited, map, 1, 0);
		c->checkNeighbor(listOfNeighbors, queue, mapWidth, mapHeight, visited, map, 0, -1);
		c->checkNeighbor(listOfNeighbors, queue, mapWidth, mapHeight, visited, map, 0, 1);
	}

	for (int y = 0; y < mapHeight; y++)
		delete[] visited[y];
	delete[] visited;

	return listOfNeighbors;
}


Node<City*>* getCityWithNeighbors(char* name, int tabSize, Node<Node<City*>*>** tabOfNeighborLists)
{
	Node<Node<City*>*>* tmp = tabOfNeighborLists[hash1(name, tabSize)];

	while (tmp != NULL)
	{
		if (compareCharTab(tmp->data->getFirst()->data->name, name))
			return tmp->data;
		tmp = tmp->next;
	}

	return NULL;
}

Node<Node<City*>*>** buildGraph(Node<City*>* listOfCities, int numOfCities, char** map, int width, int height)
{
	Node<Node<City*>*>** cityGraph = new Node<Node<City*>*>*[numOfCities];
	for (int i = 0; i < numOfCities; i++)
		cityGraph[i] = NULL;

	for (int i = 0; i < numOfCities; i++)
	{
		Node<City*>* listOfNeighbors = findNeighbors(listOfCities->data, width, height, map);
		listOfCities->data->getCityName(width, height, map);
		listOfNeighbors = listOfNeighbors->addFirst(listOfCities->data);
		addCity(listOfNeighbors, numOfCities, cityGraph);
		listOfCities = listOfCities->next;
	}

	cityGraph = addFlights(cityGraph, numOfCities);

	return cityGraph;
}

Node<Node<City*>*>** addFlights(Node<Node<City*>*>** cityGraph, int numOfCities)
{
	int numOfFlights, distance;
	char* sourceName;
	char* destName;
	cin >> numOfFlights;
	char buffor[BUFFOR_SIZE];
	for (int i = 0; i < numOfFlights; i++)
	{
		getchar();
		sourceName = getName(buffor, BUFFOR_SIZE);
		destName = getName(buffor, BUFFOR_SIZE);
		cin >> distance;

		City* destCity = new City(distance, destName);
		Node<City*>* sourceCityWithNeighbors = getCityWithNeighbors(sourceName, numOfCities, cityGraph);
		sourceCityWithNeighbors = sourceCityWithNeighbors->insertAfter(sourceCityWithNeighbors, destCity);
	}

	return cityGraph;
}

Node<City*>* putIntoPQ(Node<City*>*& priorityQueue, City* newPath)
{
	Node<City*>* tmp = priorityQueue;
	while (tmp && tmp->data->distanceFromSource > newPath->distanceFromSource)
		tmp = tmp->next;

	if (tmp == NULL)
		priorityQueue = priorityQueue->addLast(newPath);
	else
		priorityQueue = priorityQueue->insertBefore(tmp, newPath);

	return priorityQueue;
}

void updatePathsandPQ(Node<City*>** allDistances, Node<City*>** previousStops, City* prev, City* newPath, Node<City*>*& priorityQueue, int numOfCities)
{
	int index = hash1(newPath->name, numOfCities);
	Node<City*>* tmp = allDistances[index];
	Node<City*>* tmp2 = previousStops[index];

	while (tmp != NULL)
	{
		if (compareCharTab(tmp->data->name, newPath->name))
		{
			if (newPath->distanceFromSource < tmp->data->distanceFromSource)
			{
				tmp->data = newPath;
				tmp2->data = prev;
				priorityQueue = putIntoPQ(priorityQueue, newPath);
			}
			return;
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}

	allDistances[index] = allDistances[index]->addFirst(newPath);
	previousStops[index] = previousStops[index]->addFirst(prev);
	priorityQueue = putIntoPQ(priorityQueue, newPath);
}

void findShortestPaths(City* sourceCity, City* target, Node<Node<City*>*>** tabOfNeighborLists, int numOfCities, int type)
{
	Node<City*>* priorityQueue = NULL;

	Node<City*>** allDistances = new Node<City*>*[numOfCities];
	for (int i = 0; i < numOfCities; i++)
		allDistances[i] = NULL;

	Node<City*>** previousStops = new Node<City*>*[numOfCities];
	for (int i = 0; i < numOfCities; i++)
		previousStops[i] = NULL;

	updatePathsandPQ(allDistances, previousStops, NULL, sourceCity, priorityQueue, numOfCities);

	while (priorityQueue)
	{
		City* city = priorityQueue->getLast()->data;
		priorityQueue = priorityQueue->removeLast();

		Node<City*>* cityAndNeighbors = getCityWithNeighbors(city->name, numOfCities, tabOfNeighborLists);
		cityAndNeighbors = cityAndNeighbors->next;
		while (cityAndNeighbors)
		{
			City* neighbor = cityAndNeighbors->data;
			City* newPath = new City(city->distanceFromSource + neighbor->distanceFromSource, neighbor->name);
			updatePathsandPQ(allDistances, previousStops, city, newPath, priorityQueue, numOfCities);
			cityAndNeighbors = cityAndNeighbors->next;
		}
	}

	printDistance(allDistances, target, numOfCities);

	if (type == 1)
		printPath(allDistances, previousStops, target, numOfCities);

	else
		cout << endl;

	for (int i = 0; i < numOfCities; i++)
		while (allDistances[i])
			allDistances[i] = allDistances[i]->removeFirst();

	for (int i = 0; i < numOfCities; i++)
		while (previousStops[i])
			previousStops[i] = previousStops[i]->removeFirst();
}

void printDistance(Node<City*>** allDistances, City* target, int numOfCities)
{
	Node<City*>* tmp = allDistances[hash1(target->name, numOfCities)];
	while (tmp)
	{
		if (compareCharTab(tmp->data->name, target->name))
		{
			cout << tmp->data->distanceFromSource;
			return;
		}
		tmp = tmp->next;
	}
}

void printPath(Node<City*>** allDistances,  Node<City*>** previousStops, City* target, int numOfCities)
{
	Node<City*>* path = NULL;
	int index = hash1(target->name, numOfCities);
	Node<City*>* previousCity = previousStops[index];
	Node<City*>* currentCity = allDistances[index];
	char* nextName = target->name;
	while (previousCity && previousCity->data)
	{
		while (currentCity)
		{
			if (compareCharTab(currentCity->data->name, nextName))
				break;
			currentCity = currentCity->next;
			previousCity = previousCity->next;
		}

		if (!previousCity->data)
			break;

		nextName = previousCity->data->name;
		path = path->addFirst(previousCity->data);
		index = hash1(previousCity->data->name, numOfCities);
		previousCity = previousStops[index];
		currentCity = allDistances[index];
	}

	
	while (path && path->next)
	{
		path = path->next;
		cout << ' ' << path->data->name;
	}
	cout << endl;
}

void handleCommands(Node<Node<City*>*>** tabOfNeighborLists, int numOfCities)
{
	int numOfCommands, type;
	char* sourceName;
	char* destName;
	cin >> numOfCommands;
	char buffor[BUFFOR_SIZE];
	for (int i = 0; i < numOfCommands; i++)
	{
		getchar();
		sourceName = getName(buffor, BUFFOR_SIZE);
		destName = getName(buffor, BUFFOR_SIZE);
		cin >> type;
		City* sourceCity = getCityWithNeighbors(sourceName, numOfCities, tabOfNeighborLists)->data;
		City* destCity = getCityWithNeighbors(destName, numOfCities, tabOfNeighborLists)->data;
		findShortestPaths(sourceCity, destCity, tabOfNeighborLists, numOfCities, type);
	}
}