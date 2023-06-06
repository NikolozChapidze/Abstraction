/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	length =0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Node* temp = head;
	while(temp != NULL){
		Node* toDel = temp;
		temp = temp->next;
		delete toDel;
	}
}

int DoublyLinkedListPriorityQueue::size() {	
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* toAdd  = new Node;
	toAdd->prev  = NULL;
	toAdd->value = value;

	if(isEmpty()){
		toAdd->next = NULL;
	}else{
		toAdd->next = head;
		head->prev = toAdd;
	}
	length++;
	head = toAdd;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("Queue is empty!");	
	}

	string result = head->value;
	Node* temp = head;
	while(temp != NULL){
		if(temp->value < result){
			result = temp->value;
		}
		temp = temp->next;
	}
	return result;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	string result = peek();
	Node* toDel = head;
	while(toDel->value != result){
		toDel = toDel->next;
	}
	length--;
	if(isEmpty()){
		head = NULL;
	}else if(toDel->prev == NULL){
		head = toDel->next;
		head->prev = NULL;
	}else if(toDel->next == NULL){
		toDel->prev->next = NULL;
	}else{
		toDel->prev->next=toDel->next;
		toDel->next->prev=toDel->prev;
	}
	delete toDel;
	return result;
}

