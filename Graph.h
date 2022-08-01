
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <random>
#include <unordered_map>
#include <queue>
#include <stack>
#include <iomanip>
#include <cstring>
#include "Vertex.h"


class Graph {

	 map<int, Vertex> adjacencyList;
	 int numVertices;

public:
	Graph();
	void insertVertex(int sightingID, Sighting& currSighting);
	bool insertEdge(int fromID, int toID);
	float calculateWeight(int fromID, int toID);
	vector<string> getSightingDescription(const int caseID);
	vector<pair<int,int>> getAdjacentCaseIDS(const int caseID);
	void setEdges();
	void setVertexEdges(int sightingID);
	void printGraph();
	pair<int, int> dijkstra(int fromID, int toID);
	void searchLocationBFS(int sourceID, string city, string state);
	void searchShapeBFS(int sourceID, string shape);
	void searchKeyWordBFS(int sourceID, string keyWord);
	void searchLocationDFS(int sourceID, string city, string state);
	void searchID(int sightingID);
	void mostPopularCities(int n);
	int getNumVertices();
};



