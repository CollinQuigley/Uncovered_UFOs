#include "Sighting.h"
Sighting::Sighting() {

	this->ID = -1;
	this->summary = "uninitialized";
	this->city = "uninitialized";
	this->state = "uninitialized";
	this->date_time = "uninitialized"; //default
	this->shape = "uninitialized";
	this->duration = "uninitialized";
	this->latitude = "uninitialized";
	this->longitude = "uninitialized";


}

Sighting::Sighting(int ID, string summary, string city, string state, string date_time, string shape, string duration, string latitude, string longitude) {

	this->ID = ID;
	this->summary = summary;
	this->city = city;
	this->state = state;
	this->date_time = date_time; //sighting descitption
	this->shape = shape;
	this->duration = duration;
	this->latitude = latitude;
	this->longitude = longitude;
	
}