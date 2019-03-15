
#ifndef Propose_Reject_Algo
#define Propose_Reject_Algo 
#include <iostream>
#include <cstdlib>

using namespace std;

struct Node{
	char data;
	Node*  next;
};

class List
{
private:
	Node* head;
	Node* createNode(char);
	int onTheLine;
	int engagedWith;
	int count;
	bool isEngaged;
public:
	List();
	
	Node* getNodeAtIndex(int);	
	void insert(char c);
	bool isEmpty();
	void display();
	void partner();
	int getNodeIndex(char); //get the index of the nodes
	void setOnTheLine();
	int getOnTheLine();
	void setEngagedWith(int);
	int getEngagedWith();
	bool isMorePreferable(char,char);
	void setEngagementStatus(bool);
	bool getEngagementStatus();
	int getCount();
};

struct GraphNode
{
	char vertex;
	List edges;
	GraphNode* next;
};

class Graph
{
private:
	GraphNode* head;
	GraphNode* vertex; //holds vertex at a specific index
	GraphNode* createNode(char,char);
	bool vertexExist(char);
public:
	Graph();
	bool isEmpty();
	void insert(char,char);
	bool allEngaged();
	void stableMatch(Graph g);
	void display();
	void displayStableMatch();
};

#endif
