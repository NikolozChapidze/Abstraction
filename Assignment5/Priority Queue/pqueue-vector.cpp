/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
#include "vector.h"
#include "strlib.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
	minIndex = -1;
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	
	return priorQueue.size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return priorQueue.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	priorQueue.add(value);
}

string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	if(priorQueue.size()==0){
		error("Queue is empty");
	}
	string result = priorQueue.get(0);
	minIndex = 0;
	for(int i=1; i<priorQueue.size(); i++){
		if(result > priorQueue.get(i)){
			result = priorQueue.get(i);
			minIndex = i;
		}
	}
	return result;
}

string VectorPriorityQueue::dequeueMin() {
	string result = peek();
	priorQueue.remove(minIndex);
	return result;
}

