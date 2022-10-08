#include <string>
#include <iostream>
#include <vector>
#include "Node.cpp"
using namespace std;

class Tree {
	Node* root;
	int height;

	void insertNode(string n, int id) {
		Node node(n, id);

		if (root == nullptr) {
			root -> node;
		}
	}
};