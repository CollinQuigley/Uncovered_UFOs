#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Sighting {

	int ID;
	string summary;
	string city;
	string state;
	string date_time;   //sigthing description
	string shape;
	string duration;
	string latitude;
	string longitude;

	Sighting();
	Sighting(int ID, string summary, string city, string state, string date_time, string shape, string duration, string latitude, string longitude);
};
