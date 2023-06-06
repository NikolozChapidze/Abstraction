#ifndef Unionfind_Included
#define Unionfind_Included

class Unionfind{
public:
	Unionfind(int size);
	~Unionfind();
	void unionGroups(int firstID, int secondID);
	int find(int id);
	bool connected(int firstID, int secondID);
	int remainingConnections();
private:
	int* idOfCluster;
	int amount;
};

#endif