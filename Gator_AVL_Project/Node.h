#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	string NAME;
	int ID;

	Node* leftChild; //Left child of node, initialized to nullptr
	Node* rightChild; //right child of node, initialized to nullptr
	Node* parent; //parent of node, initialized to nullptr

	Node(string n, int i) {
		NAME = n;
		ID = i;

		leftChild = nullptr;
		rightChild = nullptr;
		parent = nullptr;
	}

	Node& operator=(const Node& otherNode) {
		NAME = otherNode.NAME;
		ID = otherNode.ID;

		leftChild = otherNode.leftChild;
		rightChild = otherNode.rightChild;
		parent = otherNode.parent;

		return *this;
	}

	~Node() {

	}

	string getName() {
		return NAME;
	}

	int getID() {
		return ID;
	}

	Node* getParent() {
		return parent;
	}

	Node* getLeftChild() {
		return leftChild;
	}

	Node* getRightChild() {
		return rightChild;
	}
};
