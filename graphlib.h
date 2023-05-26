#pragma once
#include "TwoWayList.h"
#include "City.h"

int hash1(char* name, int arraySize);
void addCity(Node<City*>* cityWithNeighbors, int tabSize, Node<Node<City*>*>** tabOfNeighborLists);
Node<City*>* findNeighbors(City* main, int mapWidth, int mapHeight, char** map);
Node<City*>* getCityWithNeighbors(char* name, int tabSize, Node<Node<City*>*>** tabOfNeighborLists);
Node<Node<City*>*>** buildGraph(Node<City*>* listOfSuspectedCities, int numOfCities, char** map, int width, int height);
Node<Node<City*>*>** addFlights(Node<Node<City*>*>** cityGraph, int numOfCities);
Node<City*>* putIntoPQ(Node<City*>*& priorityQueue, City* newPath);
void updatePathsandPQ(Node<City*>** allDistances, Node<City*>** previousStops, City* prev, City* newPath, Node<City*>*& priorityQueue, int numOfCities);
void findShortestPaths(City* sourceCity, City* target, Node<Node<City*>*>** tabOfNeighborLists, int numOfCities, int type);
void printDistance(Node<City*>** allDistances, City* target, int numOfCities);
void printPath(Node<City*>** allDistances, Node<City*>** previousStops, City* target, int numOfCities);
void handleCommands(Node<Node<City*>*>** tabOfNeighborLists, int numOfCities);