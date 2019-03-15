#include "proposeAndRejectAlgorithm.h"

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

