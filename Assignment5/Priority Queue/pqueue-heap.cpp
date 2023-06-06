/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

const int defQueueSize = 10;

HeapPriorityQueue::HeapPriorityQueue() {
	logicalLength = 0;
	allocatedLength = defQueueSize;
	queue = new string[allocatedLength];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] queue;
}

int HeapPriorityQueue::size() {
	return logicalLength;
}

bool HeapPriorityQueue::isEmpty() {
	return size()==0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(allocatedLength == logicalLength){
		grow();
	}
	queue[logicalLength] = value;
	bubbleUp(logicalLength);
	logicalLength++;
}

string HeapPriorityQueue::peek() {
	if(isEmpty()){ error("Queue is empty!");}
	return queue[0];
}

string HeapPriorityQueue::dequeueMin() {
	string result = peek();
	logicalLength--;
	queue[0] = queue[logicalLength];
	queue[logicalLength] = result;
	bubbleDown(0);
	return result;
}

void HeapPriorityQueue::bubbleUp(int index) {
	int parentIndex = ((index+1)%2 == 0) ? ((index+1)/2)-1 : (index/2)-1;
	if(parentIndex < 0){ return;}
	if(queue[parentIndex]>queue[index]){
		swap(parentIndex, index);
		bubbleUp(parentIndex);
	}
}

void HeapPriorityQueue::bubbleDown(int index) {
	
	int secondChild = (index+1)*2;
	int  firstChild = secondChild - 1;
	if(firstChild >= logicalLength){
		return;
	}
	if(queue[firstChild]<queue[index] && (queue[firstChild]<queue[secondChild] || secondChild>=logicalLength)){
		swap(firstChild,index);
		bubbleDown(firstChild);
	}else if(queue[secondChild] < queue[index] && secondChild <logicalLength){
		swap(secondChild,index);
		bubbleDown(secondChild);
	}
}
void HeapPriorityQueue::grow() {
	allocatedLength *= 2;
	string* temp = new string[allocatedLength];
	for(int i=0; i<logicalLength; i++ ){
		temp[i] = queue[i];
	}
	delete[] queue;
	queue = temp;
}
void HeapPriorityQueue::swap(int index1, int index2) {
	string temp   = queue[index1];
	queue[index1] = queue[index2];
	queue[index2] = temp;
}