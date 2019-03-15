 
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

List::List(){
	head = NULL;
	engagedWith = 1;
	onTheLine = 1;
	isEngaged = false;
	count = 0;
}

bool List::isEmpty(){
	return head == NULL;
}


Node* List::createNode(char c){
	Node* newNode = new Node;
	newNode->data = c;
	newNode->next = NULL;
	return newNode;
}

void List::setEngagementStatus(bool status){
	isEngaged = status;
}
bool List::getEngagementStatus(){
	return isEngaged;
}
void List::insert(char c){
	if(!isEmpty()){
		Node* temp = head;
		while(temp->next){
			temp = temp->next;
		}
		temp->next = createNode(c);
	}else{
		head = createNode(c);
	}
	count++;
}

int List::getCount(){
	return count;
}

int List::getNodeIndex(char c){
	Node* temp = head;
	int t = 0;
	while(temp){
		t++;
		if(temp->data == c){
			return t;
		}
		temp =temp->next;
	}
	return 0;
}
Node* List::getNodeAtIndex(int index){
	if(index > 0 && index <= count && !isEmpty()){
		Node* temp = head;
		for (int i = 1; i < index; ++i)
		{
			temp = temp->next;
		}
		return temp;
	}else{
		return NULL;
	}
}

void List::setOnTheLine(){
	onTheLine++;
}
int List::getOnTheLine(){
	return onTheLine;
}
void List::setEngagedWith(int p){
	engagedWith = p;
}
int List::getEngagedWith(){
	return engagedWith;
}
void List::partner(){
	cout << getNodeAtIndex(engagedWith)->data << endl;
}

bool List::isMorePreferable(char old,char newf){
	if((getNodeIndex(newf) < getNodeIndex(old))){
		cout << newf << " is isMorePreferable to " << old << endl;
		return 1;
	}else{
		cout << newf << " is not isMorePreferable to " << old << endl;
		return 0;
	} 
}

void List::display(){
	Node* temp = head;

	while(temp){
		cout << temp->data;
		temp = temp->next;
		if(temp) cout << "->";
	}
	cout << endl;
}
//Graph Starts
Graph::Graph(){
	head = NULL;
	vertex = NULL; //AVOID holding gabbage values;
}
bool Graph::isEmpty(){
	return head==NULL;
}
GraphNode* Graph::createNode(char v,char e){
	GraphNode* newNode = new GraphNode;
	newNode->vertex = v;
	newNode->edges.insert(e);
	newNode->next = NULL;
	return newNode;
}


bool Graph::vertexExist(char v){
	GraphNode* temp = head;
	while(temp){
		if(temp->vertex == v){
			vertex = temp;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

void Graph::insert(char v,char e){
	if(!isEmpty()){
		if(vertexExist(v)){
			vertex->edges.insert(e);
		}else{
			GraphNode * temp = head;
			while(temp->next){
				temp = temp->next;
			}
			temp->next = createNode(v,e);
		}
	}else{
		head = createNode(v,e);
	}

}
bool Graph::allEngaged(){
	GraphNode* temp = head;
	while(temp){
		if(!temp->edges.getEngagementStatus()){
			return false;
		}
		temp = temp->next;
	}
	return true;
}
void Graph::stableMatch(Graph g){
	GraphNode* temp = this->head;
	while(!allEngaged()){

    	char proposer = temp->vertex;
    	// #List edges = temp->edges; Never try this dangerous snippet; it gives constructor values to edges.
    	int ontheline  = temp->edges.getOnTheLine();
    	cout << "on the line: " << ontheline << endl;
    	Node* scaleOfPreference = temp->edges.getNodeAtIndex(ontheline);
    	
    	char choice = scaleOfPreference->data;
    	
		if(!temp->edges.getEngagementStatus()){
		
	    	if(g.vertexExist(choice)){ //deliberate to reduce coding (:-
	    		
				cout << proposer << " is proposing to " << choice << endl;
	            int proposeePrefLevel = g.vertex->edges.getNodeIndex(proposer);
	
	           
	            if(!g.vertex->edges.getEngagementStatus()){//check if woman is not engaged
	
	            	if(!proposeePrefLevel){ //is proposer in proposee's wishlist
	
		            	if(temp->edges.getOnTheLine() <= temp->edges.getCount()){ //Proposers' pref is limted to getCount();
		            		temp->edges.setOnTheLine(); //increment the ontheline
		            		if(temp->edges.getOnTheLine() > temp->edges.getCount()){
		            			cout << "Unstable Matching.........!" << endl;
		            			exit(-1);
							}
		            		continue; //continue as it implies that you are not even among the wishlist )::
		            	}
		            }
		            g.vertex->edges.setEngagedWith(proposeePrefLevel);
		    		temp->edges.setEngagedWith(ontheline);
		    		g.vertex->edges.setEngagementStatus(true);
		    		temp->edges.setEngagementStatus(true);
	
		    		temp->edges.setOnTheLine(); //increment the ontheline
	
		    		cout << "Processing......" << endl;
		    		cout << choice << " now engaged with " << proposer << endl;
	
	            }else if(g.vertex->edges.isMorePreferable(
	            				g.vertex->edges.getNodeAtIndex(
	            					g.vertex->edges.getEngagedWith()
	            				)->data,
	            				proposer))
	            {
	            	
					char freed = g.vertex->edges.getNodeAtIndex(g.vertex->edges.getEngagedWith())->data;
	            	g.vertex->edges.setEngagedWith(g.vertex->edges.getNodeIndex(proposer));
		    		temp->edges.setEngagedWith(ontheline);
		    		temp->edges.setEngagementStatus(true);
	 	 	
		    		temp->edges.setOnTheLine(); //increment the ontheline
		    		
		    		cout << choice << " now engaged with " << proposer << endl;
							
		    		cout << "Preference order is measured now!!!!!" << endl;
	
		    		//now the previous fiance should propose to someone else ):-
		    		if(this->vertexExist(freed)){ //another deliberate attempt to avoid creating getNodeAtVertex
		    			temp = vertex; //now temp is set to the free man to try his chance again
		    			temp->edges.setEngagementStatus(false); //set previous fiance to be free;
		    			cout << temp->vertex << " is freed " << endl;
		    			continue;
		    		}else{
		    			cout << "Unstable Matching." << endl;
		    		}
	            }else{
	            	cout << "Rejections......." << endl;
	            	if(temp->edges.getOnTheLine() <= temp->edges.getCount()){ //Proposers' pref is limted to getCount();
		            	temp->edges.setOnTheLine(); //increment the ontheline
		            	if(temp->edges.getOnTheLine() > temp->edges.getCount()){
		            		cout << "Unstable Matching.........!" << endl;
		            		exit(-1);
						}
		            	continue; //continue as it implies that you are not even among the wishlist )::
		            }
	            }
	    		
	    	}else{
	    		cout << "Unstable Matching." << endl;
	    		exit(-1);
	    	}
    	}else{
    		cout << proposer << " is already engaged with " << temp->edges.getNodeAtIndex(temp->edges.getEngagedWith())->data << endl; 
		}
		temp = temp->next;
	}
}
void Graph::display(){
	GraphNode* temp = head;
	while(temp){
		cout << temp->vertex << ":"; temp->edges.display();
		temp = temp->next;
	}
}
void Graph::displayStableMatch(){
	GraphNode* temp = head;
	while(temp){
		cout << temp->vertex << ":" ;
		temp->edges.partner();
		temp = temp->next;
	}
}


struct m
{
	enum{
		Victor = 86,Wyatt,Xavier,Yancey,Zeus
	}; 
} ;
struct w
{
	enum {
		Amy = 97, Bertha,Clare,Diane,Erika	
	};
};

int main(){
	Graph gMen,gWomen;
	
	//Start Men's Preference Profile
	gMen.insert(m::Victor,w::Bertha);gMen.insert(m::Victor,w::Amy);gMen.insert(m::Victor,w::Diane);
	gMen.insert(m::Victor,w::Erika);gMen.insert(m::Victor,w::Clare);

	gMen.insert(m::Wyatt,w::Diane);gMen.insert(m::Wyatt,w::Bertha);gMen.insert(m::Wyatt,w::Amy);
	gMen.insert(m::Wyatt,w::Clare);gMen.insert(m::Wyatt,w::Erika);

	gMen.insert(m::Xavier,w::Bertha);gMen.insert(m::Xavier,w::Erika);gMen.insert(m::Xavier,w::Clare);
	gMen.insert(m::Xavier,w::Diane);gMen.insert(m::Xavier,w::Amy);

	gMen.insert(m::Yancey,w::Amy);gMen.insert(m::Yancey,w::Diane);gMen.insert(m::Yancey,w::Clare);
	gMen.insert(m::Yancey,w::Bertha);gMen.insert(m::Yancey,w::Erika);

	gMen.insert(m::Zeus,w::Bertha);gMen.insert(m::Zeus,w::Diane);gMen.insert(m::Zeus,w::Amy);
	gMen.insert(m::Zeus,w::Erika);gMen.insert(m::Zeus,w::Clare);

	//end of filling Men's Preference Profile

	//Begin Women's Preference Profile
	gWomen.insert(w::Amy,m::Zeus);gWomen.insert(w::Amy,m::Victor);gWomen.insert(w::Amy,m::Wyatt);
	gWomen.insert(w::Amy,m::Yancey);gWomen.insert(w::Amy,m::Xavier);

	gWomen.insert(w::Bertha,m::Xavier);gWomen.insert(w::Bertha,m::Wyatt);gWomen.insert(w::Bertha,m::Yancey);
	gWomen.insert(w::Bertha,m::Victor);gWomen.insert(w::Bertha,m::Zeus);

	gWomen.insert(w::Clare,m::Wyatt);gWomen.insert(w::Clare,m::Xavier);gWomen.insert(w::Clare,m::Yancey);
	gWomen.insert(w::Clare,m::Zeus);gWomen.insert(w::Clare,m::Victor);

	gWomen.insert(w::Diane,m::Victor);gWomen.insert(w::Diane,m::Zeus);gWomen.insert(w::Diane,m::Yancey);
	gWomen.insert(w::Diane,m::Xavier);gWomen.insert(w::Diane,m::Wyatt);

	gWomen.insert(w::Erika,m::Yancey);gWomen.insert(w::Erika,m::Wyatt);gWomen.insert(w::Erika,m::Zeus);
	gWomen.insert(w::Erika,m::Xavier);gWomen.insert(w::Erika,m::Victor);

	//end of filling Women's Preference Profile

	gMen.stableMatch(gWomen);

	cout << "Men's Marriage Partners" << endl;
	gMen.displayStableMatch();
	cout << "Women's Marriage Partners" << endl;
	gWomen.displayStableMatch();

	return 0;
}
