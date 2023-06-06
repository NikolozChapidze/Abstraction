/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
using namespace std;

#include "set.h"
#include "hashmap.h"
#include "random.h"

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
///////////////////////
void getPath(Vector<Loc> &result, HashMap<Loc,pair<Loc,double>> childParent, Loc child, Loc start);
///////////////////////

Vector<Loc> shortestPath(Loc start, Loc end,Grid<double>& world,double costFn(Loc from, Loc to, Grid<double>& world),
						 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	TrailblazerPQueue<Loc> toVisit;
	Set<Loc> yellow;
	Set<Loc> green;
	Vector<Loc> result;
	// key child node, value pair of <parent, distance from start>
	HashMap<Loc,pair<Loc,double>> childParent;

	toVisit.enqueue(start,heuristic(start, end, world));
	childParent.put(start,make_pair(start,0.0));

	yellow.add(start);
	colorCell(world, start, YELLOW);

	while(!toVisit.isEmpty()){
		Loc curr = toVisit.dequeueMin();
		
		colorCell(world,curr, GREEN);
		yellow.remove(curr);
		green.add(curr);
		
		if(curr == end){
			break;
		}

		int startRow = (curr.row == 0) ? curr.row : curr.row-1;
		int startCol = (curr.col == 0) ? curr.col : curr.col-1;
		int endRow   = (curr.row == world.numRows() - 1) ? curr.row : curr.row+1;
		int endCol   = (curr.col == world.numCols() - 1) ? curr.col : curr.col+1;

		for(int x = startRow; x<=endRow; x++){
			for(int y = startCol; y<=endCol; y++){
				Loc v = makeLoc(x,y);
				double dist = childParent[curr].second + costFn(curr, v, world);
				
				if(green.contains(v)){continue;}

				if(yellow.contains(v)){
					if(dist<childParent[v].second){
						childParent[v] = make_pair(curr,dist);
						toVisit.decreaseKey(v, dist + heuristic(v, end, world));
					}
					continue;
				}
				//if gray	
				yellow.add(v);
				colorCell(world, v, YELLOW);

				childParent[v] = make_pair(curr,dist);
				toVisit.enqueue(v, dist + heuristic(v, end, world));
				//
			}
		}
	}

	getPath(result, childParent, end , start);

	return result;
}	

void getPath(Vector<Loc> &result, HashMap<Loc,pair<Loc,double>> childParent, Loc child, Loc start){
	Vector<Loc> temp;
	temp.add(child);
	while(child!=start){
		child=childParent[child].first;
		temp.add(child);
	}
	for(int i=temp.size()-1; i>=0; i-- ){
		result.add(temp.get(i));
	}
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> result;
	TrailblazerPQueue<Edge> queue;
	Unionfind unions(numCols * numRows);

	for(int i=0; i< numRows; i++){
		for(int j=0; j<numCols; j++){
			Loc curr = makeLoc(i,j);
			
			if( j != numCols-1){
				Loc right = makeLoc(i,j+1);
				queue.enqueue(makeEdge(curr,right), randomReal(0.0,10.0));
			}
			if( i != numRows-1){
				Loc down = makeLoc(i+1,j);
				queue.enqueue(makeEdge(curr,down), randomReal(0.0,10.0));
			}
		}
	}

	while(unions.remainingConnections()!=0){

		Edge next = queue.dequeueMin();	
		int idOfStarts = next.start.row * numCols + next.start.col; 
		int idOfEnd    = next.end.row * numCols + next.end.col;

		if(!unions.connected(idOfStarts,idOfEnd)){
			result.add(next);
			unions.unionGroups(idOfStarts,idOfEnd);
		}
	}
    return result;
}
