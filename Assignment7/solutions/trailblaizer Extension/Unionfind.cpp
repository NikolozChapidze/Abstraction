#include "Unionfind.h"

Unionfind::Unionfind(int size){
	idOfCluster	= new int[size];
	amount		= size-1;

	for(int i=0; i<size; i++){
		idOfCluster[i]   = i;
	}
}

Unionfind::~Unionfind(void){
	delete[] idOfCluster; 
}

int Unionfind::remainingConnections(){
	return amount;
}

bool Unionfind:: connected(int firstID, int secondID){
	if(find(firstID) == find(secondID)){
		return true;
	}
	return false;
} 

void Unionfind:: unionGroups(int firstID, int secondID){
	int p1 = find(firstID);
	int p2 = find(secondID);

	idOfCluster[p1] = p2;
	amount--;
}

int Unionfind:: find(int id){
	while(id != idOfCluster[id]){
		id = idOfCluster[id];
	}
	return id;
}
