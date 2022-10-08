#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Node {
	string NAME;
	int ID;

	Node* leftchild;
	Node* rightchild;
	Node* parent;


	Node(string n, int i) {
		NAME = n;
		ID = i;
	}

	//FIXME: Destructor
	~Node() {

	}
};
