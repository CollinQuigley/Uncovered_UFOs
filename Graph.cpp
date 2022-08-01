
#include "Graph.h"

Graph::Graph() {

	numVertices = 0;
}

void Graph::insertVertex(int sightingID, Sighting& currSighting) {

	//check if sighting ID already exists in the graph
	if (adjacencyList.find(sightingID) == adjacencyList.end()) {
		Vertex newVertex(sightingID, currSighting);
		adjacencyList[sightingID] = newVertex;
		numVertices++;
	}

}

bool Graph::insertEdge(int fromID, int toID) {

	
	bool valid = true;
	//check if the edge is valid, no loops, no parellel edges, vertexes exist
	if (fromID == toID) {
		cout << "Case IDs are the same," << " try a different case ID" << endl;
		valid = false;
		cout << endl;
	}
	if (adjacencyList.find(fromID) == adjacencyList.end()){
		cout << "Vertex for case ID: " << fromID << " does not exist" << endl;
		cout << endl;
		valid = false;
	}
	if (adjacencyList.find(toID) == adjacencyList.end()) {
		cout << "Vertex for case ID: " << toID << " does not exist" << endl;
		cout << endl;
		valid = false;
	}


	
	for (unsigned int i = 0; i < adjacencyList[fromID].getadjacentSightings().size(); i++) {
		//find if edge already exists
		if (adjacencyList[fromID].getadjacentSightings().at(i).getDestID() == toID) {
			cout << "Edge already exists between case ID: " << fromID << " and " << toID << endl;
			cout << endl;
			valid = false;
			break;
		}

	}

	if (valid == false) {
		
		return valid;
	}
	else {
		//if valid insert two edges into graph since directed
		float distance = calculateWeight(fromID, toID);
		Edge newEdge1(toID, distance);
		Edge newEdge2(fromID, distance);
		adjacencyList[fromID].addAdjacentNode(newEdge1);
		adjacencyList[toID].addAdjacentNode(newEdge2);
	}

	return valid;
}

float Graph::calculateWeight(int fromID, int toID) {
	//caluclate distance between 2 vertices based on their coordinates
	float x2 = stoi(adjacencyList[fromID].getCurrSighting().longitude);
	float x1 = stoi(adjacencyList[toID].getCurrSighting().longitude);
	float y2 = stoi(adjacencyList[fromID].getCurrSighting().latitude);
	float y1 = stoi(adjacencyList[toID].getCurrSighting().latitude);
	float factor = 54.39032827;
	float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) * factor;
	return distance;

}

vector<string> Graph::getSightingDescription(const int caseID) {
	vector<string> sightingDescription;

	//return -1 if sighting ID not found
	if (adjacencyList.find(caseID) == adjacencyList.end()) {
		sightingDescription.push_back("-1");
		return sightingDescription;
	}

	string description = "";
	//get full description of the sighting
	description += "| Case ID: " + caseID;
	description += " | Summary: " + adjacencyList[caseID].getCurrSighting().summary;
	description += " | Location: " + adjacencyList[caseID].getCurrSighting().city + ", " + adjacencyList[caseID].getCurrSighting().state;
	description += " | Date/Time: " + adjacencyList[caseID].getCurrSighting().date_time;
	description += " | Shape: " + adjacencyList[caseID].getCurrSighting().shape;
	description += " | Duration: " + adjacencyList[caseID].getCurrSighting().duration;
	description += " | Coordinates: " + adjacencyList[caseID].getCurrSighting().latitude + " latitude, " + adjacencyList[caseID].getCurrSighting().longitude + " longitude";
	sightingDescription.push_back(description);
	sightingDescription.push_back(adjacencyList[caseID].getCurrSighting().latitude);
	sightingDescription.push_back(adjacencyList[caseID].getCurrSighting().longitude);
	sightingDescription.push_back(adjacencyList[caseID].getCurrSighting().shape);
	//return vector with sighting description latitude and longitude
	return sightingDescription;


}

vector<pair<int,int>> Graph::getAdjacentCaseIDS(const int caseID){
	vector<pair<int, int>> adjacents;
	for (unsigned int i = 0; i < adjacencyList[caseID].getadjacentSightings().size(); i++) {
		adjacents.push_back(make_pair(adjacencyList[caseID].getadjacentSightings().at(i).getDestID(), adjacencyList[caseID].getadjacentSightings().at(i).getEdgeWeight()));
	}
	//return vector with adjacent vetices 
	return adjacents;
}

void Graph::setEdges() {

	std::random_device rd;

	//Random number generator 
	std::default_random_engine generator(rd());

	//Distribution on which to apply the generator 
	std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);


	for (int i = 0; i < adjacencyList.size(); i++) {
		set<int> currentEdges;
		int numAdjacentEdges = 0;
		//randomly generate five edges to connect each vertex too
		while (numAdjacentEdges < 5) {
			int randomEdge = distribution(generator) % numVertices;
			if (currentEdges.find(randomEdge) == currentEdges.end()) {
				if (insertEdge(i, randomEdge)) {
					currentEdges.insert(randomEdge);
					numAdjacentEdges++;
				}
			}
		}
	}
	//connect each vertex to the next vertex with the next sighting ID to ensure the graph stays connected
	for (int i = 0; i < adjacencyList.size(); i++) {

		if (i != 0) {
			insertEdge(i - 1, i);
		}
		if (i == adjacencyList.size() - 1) {
			insertEdge(i, 0);
		}
	}



}

void Graph::setVertexEdges(int sightingID) {
	set<int> currentEdges;
	int numAdjacentEdges = 0;
	std::random_device rd;

	//Random number generator 
	std::default_random_engine generator(rd());

	//Distribution on which to apply the generator 
	std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);

	//randomly generate five edges to connect each vertex too
	while (numAdjacentEdges < 5) {
		int randomEdge = distribution(generator) % numVertices;
		if (currentEdges.find(randomEdge) == currentEdges.end()) {
			if (insertEdge(sightingID, randomEdge)) {
				currentEdges.insert(randomEdge);
				numAdjacentEdges++;
			}
		}

	}
}
void Graph::printGraph() {
	for (auto it = adjacencyList.begin(); it !=  adjacencyList.end(); it++) {
		//print each vertex's description
		cout << "Case ID: " << it->second.getSightingID() << endl;
		cout << "Summary: " << it->second.getCurrSighting().summary << endl;
		cout << "Location: " << it->second.getCurrSighting().city << ", " << it->second.getCurrSighting().state << endl;
		cout << "Date/Time: " << it->second.getCurrSighting().date_time << endl;
		cout << "Shape: " << it->second.getCurrSighting().shape << endl;
		cout << "Duration: " << it->second.getCurrSighting().duration << endl;
		cout << "Coordinates: " << it->second.getCurrSighting().latitude << " Latitude, " << it->second.getCurrSighting().longitude << " Longitude" << endl;
		cout << endl;

		cout << "________________________Adjacent Vertices________________________" << endl;
		cout << "                                |                                " << endl;
		cout << "                                |                                " << endl;
		cout << "                                |                                " << endl;
		cout << "                                V                               " << endl;
		cout << endl;
		
		//Print each vertex's adjacent vertices
		if (it->second.getadjacentSightings().size() != 1) {
			cout << it->second.getadjacentSightings().size() << " Adjacent Vertices" << endl;
		}
		else {
			cout << it->second.getadjacentSightings().size() << " Adjacent Vertex" << endl;
		}
	    cout << endl;
		for (unsigned int j = 0; j < it->second.getadjacentSightings().size(); j++) {

			cout <<  "Destination ID:" << it->second.getadjacentSightings().at(j).getDestID() << endl;
			cout << "Weight:" <<  it->second.getadjacentSightings().at(j).getEdgeWeight() << endl;
			cout << "Summary: " << adjacencyList[it->second.getadjacentSightings().at(j).getDestID()].getCurrSighting().summary << endl;
			cout << endl;
			
		}

		
	    cout << "_________________________________________________________________" << endl;
		
		cout << endl;
	}
}



pair<int, int> Graph::dijkstra(int fromID, int toID) {
	
	//check if valid ID numbers
	bool valid = true;
	if (adjacencyList.find(fromID) == adjacencyList.end()) {
		cout << "CaseID: " << fromID << " does not exist" << endl;
		valid = false;
	}
	if (adjacencyList.find(toID) == adjacencyList.end()) {
		cout << "CaseID: " << toID << " does not exist" << endl;
		valid = false;
	}

	if (!valid) {
		return make_pair(-1, -1);
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	map<int, pair<int, int>> dist;
	//set each node to max distacne and previous to -1
	for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
		dist[it->second.getSightingID()] = make_pair(INT_MAX, -1);
	}
	//push source node to priority queue
	pq.push(make_pair(0, fromID));
	dist[fromID] = make_pair(0, -1);

	while (!pq.empty()) {

		pair<int, int> current = pq.top();
		pq.pop();
		int u = current.second;
		//loop through current's adjacents 
		for (unsigned int i = 0; i < adjacencyList[u].getadjacentSightings().size(); i++) {

			int v = adjacencyList[u].getadjacentSightings().at(i).getDestID();
			int weight = adjacencyList[u].getadjacentSightings().at(i).getEdgeWeight();
			//relax the edges
			if (dist[v].first > dist[u].first + weight) {

				int temp = dist[u].first + weight;
				dist[v] = make_pair(temp, u);
				pq.push(make_pair(dist[v].first, v));
			}		
		}
	}
	//push path to stack
	stack<int> shortestPath;
	int previous = dist[toID].second;
	shortestPath.push(toID);
	shortestPath.push(previous);


	while (previous != -1) {
		previous = dist[previous].second;
		if (previous != -1) {
			shortestPath.push(previous);
		}
		
	}

	cout << "Shortest distance from case ID: " << fromID << " to case ID: " << toID << endl;
	cout << endl;
	cout << dist[toID].first << endl;
	cout << endl;
	cout << "Shortest path from case ID: " << fromID << " to case ID: " << toID << endl;
	cout << endl;

	//pop the stack to get the exact path for the shortest distance
	while (!shortestPath.empty()) 
	{	
		cout << "Case ID: " << shortestPath.top() <<  endl;
	
		shortestPath.pop();
		if (!shortestPath.empty()) {
			cout << "    |" << endl;
			cout << "    V" << endl;
		}
	}

	return dist[toID];
}

void Graph::searchLocationBFS(int sourceID, string city, string state) {
	//check if Vertex with specified ID exists in the graph
	if (adjacencyList.find(sourceID) == adjacencyList.end()) {
		cout << "Case ID: " << sourceID << "does not exist" << endl;
		return;
	}
	int numTargets = 0;
	set<int> visitedIDs;
	queue<int> queue;

	//push source node
	visitedIDs.insert(sourceID);
	queue.push(sourceID);
	while (!queue.empty()) {
		int current = queue.front();
		queue.pop();
		if (adjacencyList[current].getCurrSighting().city == city && adjacencyList[current].getCurrSighting().state == state) {
			adjacencyList[current].printVertex();
			numTargets++;
		}
		//loop through current's adjacents
		for (unsigned int i = 0; i < adjacencyList[current].getadjacentSightings().size(); i++) {
			int currentID = adjacencyList[current].getadjacentSightings().at(i).getDestID();
			//add to queue if not visited yet
			if (visitedIDs.find(currentID) == visitedIDs.end()) {
				queue.push(currentID);
				visitedIDs.insert(currentID);
			}

		}
	}
	//calculate the percentage of mathches divided by the number of vertices
	float percentage = (float)numTargets / numVertices * 100.0;
	cout << numTargets << " of " << numVertices << " UFO sightings were reported in " << city << ", " << state << endl;
	cout << percentage << "% " << endl;
	cout << endl;

}

void Graph::searchShapeBFS(int sourceID, string shape) {
	//check if Vertex with specified ID exists in the graph
	if (adjacencyList.find(sourceID) == adjacencyList.end()) {
		cout << "Case ID: " << sourceID << "does not exist" << endl;
		return;
	}
	int numTargets = 0;
	set<int> visitedIDs;
	queue<int> queue;
	//push source node
	visitedIDs.insert(sourceID);
	queue.push(sourceID);
	while (!queue.empty()) {
		int current = queue.front();
		queue.pop();
		if (adjacencyList[current].getCurrSighting().shape == shape) {
			adjacencyList[current].printVertex();
			numTargets++;
		}
		//loop through current's adjacents
		for (unsigned int i = 0; i < adjacencyList[current].getadjacentSightings().size(); i++) {
			int currentID = adjacencyList[current].getadjacentSightings().at(i).getDestID();
			//add to queue if not visited yet
			if (visitedIDs.find(currentID) == visitedIDs.end()) {
				queue.push(currentID);
				visitedIDs.insert(currentID);
			}

		}
	}
	//calculate the percentage of mathches divided by the number of vertices
	float percentage = (float)numTargets / numVertices * 100.0;
	cout << "There are " << numTargets << " UFO sightings of " << numVertices << " that describe the UFO shape as a " << shape << endl;
	cout << "The sightings described as a " << shape << "account for " << fixed << setprecision(2) << (numTargets / (float)numVertices) * 100 << '%' << " of the total number of reported sightings." << endl;
	cout << endl;

}

void Graph::searchKeyWordBFS(int sourceID, string keyword) {
	//check if Vertex with specified ID exists in the graph
	if (adjacencyList.find(sourceID) == adjacencyList.end()) {
		cout << "Case ID: " << sourceID << "does not exist" << endl;
		return;
	}
	int numTargets = 0;
	set<int> visitedIDs;
	queue<int> queue;
	//push source node
	visitedIDs.insert(sourceID);
	queue.push(sourceID);
	while (!queue.empty()) {
		int current = queue.front();
		queue.pop();
		if (adjacencyList[current].getCurrSighting().summary.find(keyword) != std::string::npos){
			adjacencyList[current].printVertex();
			numTargets++;
		}
		//loop through current's adjacents
		for (unsigned int i = 0; i < adjacencyList[current].getadjacentSightings().size(); i++) {
			int currentID = adjacencyList[current].getadjacentSightings().at(i).getDestID();
			if (visitedIDs.find(currentID) == visitedIDs.end()) {
				queue.push(currentID);
				visitedIDs.insert(currentID);
			}

		}
	}
	//calculate the percentage of mathches divided by the number of vertices
	float percentage = (float)numTargets / numVertices * 100.0;
	cout << "The keyword, " << keyword << ", was found in " << numTargets << " of " << numVertices << " sighting summaries, which accounts for " << fixed << setprecision(2) << (numTargets / (float)numVertices) * 100 << '%' << " of the total number of reported sightings." << endl;
	cout << endl;

}

void Graph::searchLocationDFS(int sourceID, string city, string state) {
	//check if Vertex with specified ID exists in the graph
	if (adjacencyList.find(sourceID) == adjacencyList.end()) {
		cout << "Case ID: " << sourceID << "does not exist" << endl;
		return;
	}
	int numTargets = 0;
	set<int> visitedIDs;
	stack<int> stack;
	//push source node
	visitedIDs.insert(sourceID);
	stack.push(sourceID);
	while (!stack.empty()) {
		int current = stack.top();
		stack.pop();
		if (adjacencyList[current].getCurrSighting().city == city && adjacencyList[current].getCurrSighting().state == state) {
			adjacencyList[current].printVertex();
			numTargets++;
		}
		//loop through current's adjacents
		for (unsigned int i = 0; i < adjacencyList[current].getadjacentSightings().size(); i++) {
			int currentID = adjacencyList[current].getadjacentSightings().at(i).getDestID();
			if (visitedIDs.find(currentID) == visitedIDs.end()) {
				stack.push(currentID);
				visitedIDs.insert(currentID);
			}

		}
	}
	//calculate the percentage of mathches divided by the number of vertices
	float percentage = (float)numTargets / numVertices * 100.0;
	cout << numTargets << " of " << numVertices << " UFO sightings were reported in " << city << ", " << state << endl;
	cout << percentage << "% " << endl;
	cout << endl;

}

void Graph::searchID(int sightingID) {
	//search for ID
	if (adjacencyList.find(sightingID) == adjacencyList.end()) 
	{
		cout << "Case ID: " << sightingID << " does not exist" << endl;

	}
	else
	{
		adjacencyList[sightingID].printVertex();
		

	}
}

void Graph::mostPopularCities(int n) {

	//map for pair for string city and state and number of UFO sightings
	map<pair<string, string>, int> mp; 

	
	int numTargets = 0;
	set<int> visitedIDs;
	queue<int> queue;

	visitedIDs.insert(0);
	queue.push(0);
	//breadth First Search
	while (!queue.empty()) {
		int current = queue.front();
		queue.pop();
		pair<string, string> u = make_pair(adjacencyList[current].getCurrSighting().city, adjacencyList[current].getCurrSighting().state);
		if (mp.find(u) == mp.end()) {
			//put in map and set to one if no previous UFO sighting found
			mp[u] = 1;
		}
		else {
			//increment number of sightings in city if previous sightings found
			mp[u]++;
		}
		//loop through current's adjacents
		for (unsigned int i = 0; i < adjacencyList[current].getadjacentSightings().size(); i++) {
			int currentID = adjacencyList[current].getadjacentSightings().at(i).getDestID();
			
			if (visitedIDs.find(currentID) == visitedIDs.end()) {
				queue.push(currentID);
				visitedIDs.insert(currentID);
			}

		}
	}
	//min heap that is based on the number of occurances of UFO citings in a location
	priority_queue<pair<int,pair<string,string>>, vector<pair<int, pair<string, string>>>, greater<pair<int, pair<string, string>>> > min;
	
	//keep N elements in min heap at once. If greater number is found push that number and pop
	for (auto it = mp.begin(); it != mp.end(); it++) {

		if (min.size() == n && it->second < min.top().first) {
			continue;
		}
		min.push(make_pair(it->second, it->first));
		if (min.size() > n) {
			min.pop();
		}	
	}
	//add elements for min heap to vector for traversal
	vector<pair<int, pair<string, string>>> mostPopularCities;
	for (int i = 0; i < n; i++) {
		pair<int, pair<string, string>> temp = min.top();
		min.pop();
		mostPopularCities.push_back(temp);
		
	}
	//print N most popular cities for UFO sightings
	cout << "The " << n << " cities with the most sightings are: " << endl;
	for (int i = mostPopularCities.size() - 1; i >= 0; i--) {
		cout << n - i << ". " << mostPopularCities.at(i).second.first << ", " << mostPopularCities.at(i).second.second << " with " << mostPopularCities.at(i).first;
		cout << " sightings, which accounts " << fixed << setprecision(2) << (mostPopularCities.at(i).first / (float)numVertices) * 100 << '%' << " of the total number of reported sightings." << endl;
	}

}

int Graph::getNumVertices() {
	//return the number of vertices in the graph
	return numVertices;
}