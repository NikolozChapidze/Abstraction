/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	start = NULL;
	length  = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Cell* temp = start;
	while(temp != NULL){
		Cell* del = temp;
		temp = temp->next;
		delete del;
	}
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Cell* toAdd = new Cell;
	toAdd->elem = value;
	toAdd->next = NULL;
	if(isEmpty()){
		start = toAdd;
		length++;
		return;
	}
	
	Cell* before = start;

	if(before->elem > value){
		toAdd->next = before;
		start = toAdd;
		length++;
		return;
	}
	while(before->next != NULL && (before->next)->elem < value){
		before = before->next;
	}
	toAdd->next = before->next;
	before->next = toAdd;
	length++;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("Queue is empty!");
	}
	return start->elem;
}

string LinkedListPriorityQueue::dequeueMin() {
	string result = peek();
	Cell* temp = start;
	start = start->next;
	delete temp;
	length--;
	return result;
}

