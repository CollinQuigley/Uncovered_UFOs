#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <queue>
#include <utility>
#include "Sighting.h"
using namespace std;

class Hashtable {
    //hashtable variables
    Sighting** arrayOfSightings;
    int numSightings;
    int numBuckets;
public:
    Hashtable();
    //Hashtable(int setTableSize);
    ~Hashtable();
    void printSighting(Sighting* sighting);
    int hashFunction(int hashID);
    void insertSighting(Sighting* aSighting);
    void searchByShape(string shapeName);
    void numSightingsInCity(string cityName, string stateName);
    void mostPopularCities(int N);
    void searchByKeyword(string keyword);
    void printHashtable();
    void findID(int _ID);
    int getLoadFactor();
    void reHash();
    int getNumSightings();
};