#include "Edge.h"
Edge::Edge() {

	destID = -1;
	edgeWeight = -1;

}

Edge::Edge(int destID, int edgeWeight) {
	//set the Dest ID and weight to this vertex
	this->destID = destID;
	this->edgeWeight = edgeWeight;
}

int Edge::getDestID() {
	return destID;
}

int Edge::getEdgeWeight() {
	return edgeWeight;
}