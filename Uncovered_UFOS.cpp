#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Hashtable.h"
#include "Graph.h"
#include "Bridges.h"
#include "GraphAdjList.h"
#pragma warning(disable : 4996)
using namespace std;
using namespace bridges;


//Test
void shuffleIDs(vector<int>& randomIDs) {
	
	for (unsigned int i = 0; i < 110099; i++) {
		randomIDs.push_back(i);
	}

	std::random_device rd;

	//Random number generator 
	std::default_random_engine generator(rd());

	//Distribution on which to apply the generator 
	std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);

	//shuffle IDs to randomly assign IDs to each sighting
	for (unsigned int i = 0; i < randomIDs.size(); i++) {

		int random = distribution(generator) % 110099;
		int temp = randomIDs.at(random);
		randomIDs.at(random) = randomIDs.at(i);
		randomIDs.at(i) = temp;
	}


}

void setShape(GraphAdjList<string>& bridgesGraph, vector<string>& sightingDescription) {

	//set the shapes for each sighting
	if (sightingDescription.at(3) == "circle") {
		bridgesGraph.getVertex(sightingDescription.at(0))->setShape(CIRCLE);
	}
	else if (sightingDescription.at(3) == "triangle") {
		bridgesGraph.getVertex(sightingDescription.at(0))->setShape(TRIANGLE);
		bridgesGraph.getVertex(sightingDescription.at(0))->setColor("green");
	}
	else if (sightingDescription.at(3) == "rectangle") {
		bridgesGraph.getVertex(sightingDescription.at(0))->setShape(SQUARE);
		bridgesGraph.getVertex(sightingDescription.at(0))->setColor("red");
	}
	else if (sightingDescription.at(3) == "diamond") {
		bridgesGraph.getVertex(sightingDescription.at(0))->setShape(DIAMOND);
		bridgesGraph.getVertex(sightingDescription.at(0))->setColor("orange");
	}
	else if (sightingDescription.at(3) == "fireball") {
		bridgesGraph.getVertex(sightingDescription.at(0))->setShape(STAR);
		bridgesGraph.getVertex(sightingDescription.at(0))->setColor("yellow");
	}
	else if (sightingDescription.at(3) == "light") {
		bridgesGraph.getVertex(sightingDescription.at(0))->setShape(STAR);
		bridgesGraph.getVertex(sightingDescription.at(0))->setColor("yellow");
	}
	else if (sightingDescription.at(3) == "cross") {
		bridgesGraph.getVertex(sightingDescription.at(0))->setShape(CROSS);
		bridgesGraph.getVertex(sightingDescription.at(0))->setColor("white");
	}
}

void readFile(string fileName, Graph& graph, Hashtable& hashtable, const vector<int>& randomIDs) {
	
	string lineFromFile;
	//open the file
	ifstream inFile("nuforc_reports.csv");
	getline(inFile, lineFromFile);
	int i = 0;
	//read all the data 
	while (getline(inFile, lineFromFile)) {
		istringstream stream(lineFromFile);
		string summary, city, state, date_time, shape, duration, stats, reportLink, posted, latitude, longitude;
		//get the data for each sighting
		getline(stream, summary, '|');
		getline(stream, city, '|');
		getline(stream, state, '|');
		getline(stream, date_time, '|');
		getline(stream, shape, '|');
		getline(stream, duration, '|');
		getline(stream, stats, '|');
		getline(stream, reportLink, '|');
		getline(stream, posted, '|');
		getline(stream, latitude, '|');
		getline(stream, longitude, '|');

		if (latitude != "" && longitude != "") {
			//create each sighting object and insert into directed graph and unoredered map/ hastable
			Sighting currSighting(randomIDs.at(i), summary, city, state, date_time, shape, duration, latitude, longitude);
			graph.insertVertex(randomIDs.at(i), currSighting);
			Sighting* dynamicSighting = new Sighting(randomIDs.at(i), summary, city, state, date_time, shape, duration, latitude, longitude);
			hashtable.insertSighting(dynamicSighting);
			i++;

		}

	}
	//randomly assign insert edges throughout the entire undirected graph to ensure it is connected
	graph.setEdges();
}


int main()
{

	Graph graph;
	Hashtable hashtable;

	vector<int> randomIDs;

	shuffleIDs(randomIDs);
	readFile("nuforc_reports.csv", graph, hashtable, randomIDs);

	
	cout << "Welcome to UFO Sightings Simulator!" << endl;

	bool toContinue = true;
	do {
		//main menu
		cout << "Please enter a command: " << endl;
		cout << " 1 - Undirected Graph implementation" << endl;
		cout << " 2 - Unordered Map/Hashtable implementation" << endl;
		cout << " 3 - Report a UFO sighting" << endl;
		cout << " 4 - Quit" << endl;
		string input;
		cout << endl;
		getline(cin, input);
		int command = stoi(input);
		cout << endl;
		
		// check if valid command
		while (command < 1 || command > 3) {
			cout << "Invalid command" << endl;
			cout << "Please enter a command: " << endl;
			
		}

		if (command == 1) {
			do {
				// menu for graph implementation
				cout << "Undirected Graph implementation" << endl;
				cout << "Please choose a command: " << endl;
				cout << " 1 - Search UFO sighting by sighting ID " << endl;
				cout << " 2 - Search UFO sighting by location " << endl;
				cout << " 3 - Search UFO sighting by shape " << endl;
				cout << " 4 - Search UFO sighting by keyword " << endl;
				cout << " 5 - List N Most popular cities for UFO sightings " << endl;
				cout << " 6 - Visualize Graph " << endl;
				cout << " 7 - Print Graph " << endl;
				cout << " 0 - Back to main menu " << endl;
				cout << endl;
				getline(cin, input);
				command = stoi(input);
				cout << endl;
				
				if(command < 0 || command > 7) {
					cout << "Invalid command" << endl;
					cout << endl;
					continue;
				}

				if (command == 1) {
					//search by sighting ID
					string sightingID;
					cout << "Enter a sighting ID: " << endl; 
					cout << endl;
					getline(cin, sightingID);
					auto start = chrono::high_resolution_clock::now();
					graph.searchID(stoi(sightingID));
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
					
				}
				else if (command == 2) {
					// search by location
					string city, state;
					cout << "Enter a city name: (Capitialize first letter in every word, Ex: New York) " << endl;
					getline(cin, city);
					cout << "Enter the state: (Use Abbreivations, Ex: FL) " << endl;
					getline(cin, state);
					auto start = chrono::high_resolution_clock::now();
					graph.searchLocationBFS(0, city, state);
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;



				}
				else if (command == 3) {
					//search by shape
					string shape;
					cout << "Enter a shape: " << endl;
					cout << endl;
					getline(cin, shape);
					auto start = chrono::high_resolution_clock::now();
					graph.searchShapeBFS(0, shape);
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
				}
				else if (command == 4) {
					//search by keyword
					string keyword;
					cout << "Enter a keyword: " << endl;
					getline(cin, keyword);
					auto start = chrono::high_resolution_clock::now();
					graph.searchKeyWordBFS(0, keyword);
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
				
				}
				else if (command == 5) {
					//find N most popular cities with UFO sightings
					string N;
					cout << "Enter the N most popular cities for UFO sightings as an integer. (20 means top 20 cities)" << endl;
					cout << endl;
					getline(cin, N);
					auto start = chrono::high_resolution_clock::now();
					graph.mostPopularCities(stoi(N));
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
				}
				else if (command == 6) {
					//visualize graph. create graph of specified vertex and its adjacents using bridges api
					string caseID;
					cout << "Enter a case ID/vertex to visualize" << endl;
					cout << endl;
					getline(cin, caseID);

					Bridges bridges(0, "Collin_Quigley", "245463415583");

					bridges.setTitle("Uncovered_UFOS");

					bridges.setDescription("UFO Report Database");
					bridges.setCoordSystemType("equirectangular");
					bridges.setMapOverlay(true);
					bridges.setWindow(0, 180, 0, 90);

					//create bridges object for bridges api
					GraphAdjList<string> bridgesGraph;
					bridges.setDataStructure(&bridgesGraph);


					vector<string> sightingDescription = graph.getSightingDescription(stoi(caseID));


					if (sightingDescription.at(0) == "-1") {
						cout << "Invlaid Case ID: " << endl;;
						cout << endl;

					}
					else {
						//insert specified vertex by user and all of its adjacents vertices into bridges graph object
						bridgesGraph.addVertex(sightingDescription.at(0));
						bridgesGraph.getVertex(sightingDescription.at(0))->setLocation(stof(sightingDescription.at(2)), stof(sightingDescription.at(1)));

						bridgesGraph.getVertex(sightingDescription.at(0))->setSize(1);
						setShape(bridgesGraph, sightingDescription);

						cout << endl;
						vector<pair<int, int>> adjacents = graph.getAdjacentCaseIDS(stoi(caseID));
						for (int i = 0; i < adjacents.size(); i++) {

							vector<string> insertVertex = graph.getSightingDescription(adjacents.at(i).first);
							bridgesGraph.addVertex(insertVertex.at(0));
							bridgesGraph.getVertex(insertVertex.at(0))->setLocation(stof(insertVertex.at(2)), stof(insertVertex.at(1)));
							bridgesGraph.getVertex(insertVertex.at(0))->setSize(1);
							setShape(bridgesGraph, insertVertex);
							bridgesGraph.addEdge(sightingDescription.at(0), insertVertex.at(0));
							bridgesGraph.getEdge(sightingDescription.at(0), insertVertex.at(0)).setLabel(to_string(adjacents.at(i).second));
							bridgesGraph.getEdge(sightingDescription.at(0), insertVertex.at(0)).setColor("black");
							bridgesGraph.getEdge(sightingDescription.at(0), insertVertex.at(0)).setThickness(1);
						}
					}
					//print a link for the user to use to see the visualization of the graph
					bridges.visualize();
					cout << endl;

				}
				else if (command == 7) {
					//print each vertex and it's adjacents
					graph.printGraph();
					cout << endl;
				}
			} while (command != 0);
			// end of graph implementation
		}
		else if (command == 2) {

		     do {
				// menu for hashtable implementation
				cout << "Unoredered Map/Hashtable implementation" << endl;
				cout << "Please choose a command: " << endl;
				cout << " 1 - Search UFO sighting by sighting ID " << endl;
				cout << " 2 - Search UFO sighting by location " << endl;
				cout << " 3 - Search for a sighting by shape " << endl;
				cout << " 4 - Search UFO sighting by keyword " << endl;
				cout << " 5 - List N Most popular cities for UFO sightings " << endl;
				cout << " 6 - Print Hashtable " << endl;
				cout << " 0 - Back to main menu " << endl;
				cout << endl;
				getline(cin, input);
				cout << endl;
				command = stoi(input);
				// check if valid command
				if(command < 0 || command > 6) {

					cout << "Invalid command" << endl;
					cout << endl;
					continue;
				}

				// add a sighting
				if (command == 1) {
					//search by sightingID
					string sightingID;
					cout << "Enter a sighting ID: " << endl;
					cout << endl;
					getline(cin, sightingID);
					cout << endl;
					auto start = chrono::high_resolution_clock::now();
					hashtable.findID(stoi(sightingID));
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
					
				}
				else if (command == 2) {
					//search by location
					string city, state;
					cout << "Enter a city name: (Capitialize first letter in every word, Ex: New York) " << endl;
					getline(cin, city);
					cout << endl;
					cout << "Enter the state: (Use Abbreivations, Ex: FL) " << endl;
					getline(cin, state);
					auto start = chrono::high_resolution_clock::now();
					hashtable.numSightingsInCity(city, state);
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
				}
				else if (command == 3) {
					// search by shape
					string shape;
					cout << "Enter a shape: " << endl;
					cout << endl;
					getline(cin, shape);
					cout << endl;
					auto start = chrono::high_resolution_clock::now();
					hashtable.searchByShape(shape);
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
					
				}
				else if (command == 4) {
					//search by keyword
					string keyword;
					cout << "Enter a keyword: " << endl;
					getline(cin, keyword);
					cout << endl;
					auto start = chrono::high_resolution_clock::now();
					hashtable.searchByKeyword(keyword);
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
					
				}
				else if (command == 5) {
					//find N most popular ciites with UFO sightings
					string N;
					cout << "Enter the N most popular cities for UFO sightings as an integer. (20 means top 20 cities)" << endl;
					cout << endl;
					getline(cin, N);
					cout << endl;
					auto start = chrono::high_resolution_clock::now();
					hashtable.mostPopularCities(stoi(N));
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;

				}
				else if (command == 6) {
					//print hashtable
					auto start = chrono::high_resolution_clock::now();
					hashtable.printHashtable();
					auto end = chrono::high_resolution_clock::now();
					cout << endl;
					chrono::duration<float> duration = end - start;
					cout << "This executed in " << duration.count() << " seconds" << endl;
					cout << endl;
				}
						
			} while (command != 0);
		}
		else if (command == 3) {
		     //ask the user to input information on the UFO sighting they want to report
		     cout << "Please enter a summary: " << endl;
		     string summary;
		     getline(cin, summary);
			 cout << endl;
		     cout << "Please enter a city: " << endl;
		     string city;
		     getline(cin, city);
			 cout << endl;
		     cout << "Please enter a state: " << endl;
		     string state;
		     getline(cin, state);
			 cout << endl;
		     cout << "Please enter the date and time: " << endl;
		     string date_time;
		     getline(cin, date_time);
			 cout << endl;
		     cout << "Please enter the shape: " << endl;
		     string shape;
		     getline(cin, shape);
			 cout << endl;
		     cout << "Please enter the duration: " << endl;
		     string duration;
		     getline(cin, duration);
			 cout << endl;
		     cout << "Please enter the latitude: " << endl;
		     string latitude;
		     getline(cin, latitude);
			 cout << endl;
		     cout << "Please enter the longitude: " << endl;
		     string longitude;
		     getline(cin, longitude);
			 cout << endl;
		     Sighting currSighting(graph.getNumVertices(), summary, city, state, date_time, shape,
			  duration, latitude, longitude);
			 Sighting* dynamicSighting = new Sighting(hashtable.getNumSightings(), summary, city, state, date_time, shape, duration, latitude, longitude);
		// insert user UFO sighting into graph
			 cout << "UFO sighting reported with sighting ID: " << graph.getNumVertices();
		     graph.insertVertex(graph.getNumVertices(), currSighting);
			 graph.setVertexEdges(graph.getNumVertices() - 1);
			 hashtable.insertSighting(dynamicSighting);
			 if (hashtable.getLoadFactor() > 0.85) {
				 hashtable.reHash();
			 }
		     cout << endl;

		    
		
		}
		//exit the program
		else if (command == 4) {
		    toContinue = false;
        }
	} while (toContinue);

	return 0;
}