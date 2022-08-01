
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Sighting.h";

class Edge{

	int destID; //sighting ID of the adjacent node
	int edgeWeight; //approximate distance in miles between two connected vertices
public:
	Edge();
	Edge(int destID, int edgeWeight);
	int getDestID();
	int getEdgeWeight();
};

