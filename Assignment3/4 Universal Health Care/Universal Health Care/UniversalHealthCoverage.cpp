/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "simpio.h"
#include "set.h"
#include "vector.h"
#include "console.h"
#include "foreach.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

void getInformation(Set<string> &cities, Vector<Set<string>> &locations, int &n);

int main() {
    /* TODO: Add testing code here! */
	Set<string>			cities;
	Vector<Set<string>> locations;
	int					n;

	getInformation(cities,locations,n);

	Vector< Set<string> > result;
	if(canOfferUniversalCoverage(cities,locations, n,result)){
		cout<<"It is possible :)"<<endl;
		cout<<result<<endl;
	}else{
		cout<<"It is impossible :("<<endl; 
	}
    return 0;
}

void getInformation(Set<string> &cities, Vector<Set<string>> &locations, int &n){
	Set<string>	loc;

	cout<<"input cities: ";
	string s = getLine("");
	for(int i=0; i < s.length(); i++){
		cities.add(s.substr(i,1));
	}
	cout<<"input locations: ";
	s = getLine("");
	while( s != "-1"){
		for(int i=0; i<s.length(); i++){
			loc.add(s.substr(i,1));
		}
		locations.add(loc);
		loc.clear();
		s = getLine("");
	}

	//cout<<locations<<endl;
	cout<<"input number of hospitals: ";
	n = getInteger("");
}

bool checkEqual(Set<string> cities, Vector< Set<string> > result){
	Set<string> potential;
	foreach(Set<string> city in result){
		potential+=city;
	}
	return cities == potential;
}

bool canOfferUniversalCoverage(Set<string>& cities,Vector< Set<string> >& locations,int numHospitals,Vector< Set<string> >& result){
	if(result.size() == numHospitals || locations.size()==0){
		return checkEqual(cities, result);
	}
	Set<string> temp = locations.get(locations.size()-1);
	locations.remove(locations.size()-1);
	if(canOfferUniversalCoverage(cities,locations,numHospitals,result) ||  canOfferUniversalCoverage(cities,locations,numHospitals,(result+=temp))){
		return true;
	}
	result.remove(result.size()-1);
	locations.add(temp);
	return false;
}
