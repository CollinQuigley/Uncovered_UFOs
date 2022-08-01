
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Edge.h"

class Vertex {


	int caseID;
	Sighting currSighting;  //the UFO sighting information the vertex holds
	vector<Edge> adjacentSightings; //adjacent sightings

public:

	Vertex();
	Vertex(int sightingID, Sighting& currSighting);
	int getSightingID();
	Sighting getCurrSighting();
	vector<Edge> getadjacentSightings();
	void addAdjacentNode(Edge newEdge);
	void printVertex();



};


