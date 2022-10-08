#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

class Tree {
public:
	Node* root;

	Tree() {
		root = nullptr;
	}

	~Tree() {

	}

	//currNode will update recursively as it iterates through tree, newNode is the node that will be created in main when an insert is requested
	void insertNode(Node *currNode, Node *newNode) {

		if (currNode == nullptr) {
			root = newNode; //If no root yet exists, newNode will become root
			cout << "successful" << endl;
			return;
		}
		else if (newNode->ID < currNode->ID) { //Check if newNode value is less than current
			if (currNode->leftChild == nullptr) { //If the leftChild is null, place the newNode in that location
				currNode->leftChild = newNode;
				newNode->parent = currNode;

				performRotations(newNode);
				cout << "successful" << endl;
				return;
			}
			else { //Otherwise, recursively call the fuction
				insertNode(currNode->leftChild, newNode);
			}
		}
		else if (newNode->ID > currNode->ID) { //Check if new node value is greater than currNode value
			if (currNode->rightChild == nullptr) { //If currNode does not have right child, new node will become its right child
				currNode->rightChild = newNode;
				newNode->parent = currNode;

				performRotations(newNode);
				cout << "successful" << endl;
				return;
			}
			else {
				insertNode(currNode->rightChild, newNode);
			}
		}
	}

	//Will be passed a newly inserted node and will perform rotations if necessary, otherwise will do nothing
	void performRotations(Node* node) {
		//Not necessary if node does not have a parent and grandparent
		if (node->parent == nullptr || node->parent->parent == nullptr) {
			return;
		}
		Node* Grandparent = node->parent->parent;
		Node* Parent = node->parent;
		if (findBalanceFactor(Grandparent) == 2) { //If tree is left heavy
			if (findBalanceFactor(Parent) == 1) { //Perform right rotation
				Grandparent->parent->leftChild = Parent; //Modify great Grandparents child

				Parent->parent = Grandparent->parent; //Modify the parent's parent and child
				Parent->rightChild = Grandparent;

				Grandparent->parent = Parent; //Modify grandparent's parent and leftchild
				Grandparent->leftChild = nullptr;
			}
			else if (findBalanceFactor(Parent) == -1) {//Perform left right rotation
				//Left rotation
				Grandparent->leftChild = node; //Change grandparent left child to node

				Parent->rightChild = nullptr; //Modify the node's parent's pointers
				Parent->parent = node;

				node->parent = Grandparent; //Change node's parent and leftchild
				node->leftChild = Parent;

				//Right rotation
				node->rightChild = Grandparent; //Change node's parent and rightChild
				node->parent = Grandparent->parent;

				Grandparent->parent = node; //Change grandparent's parent and child nodes
				Grandparent->leftChild = nullptr;
			}
		}
		else if (findBalanceFactor(Grandparent) == -2) { //If tree is right heavy
			if (findBalanceFactor(Parent) == 1) { //Perform right left rotation
				//Right rotation
				Grandparent->rightChild = node; //Change grandparent right child to node

				Parent->leftChild = nullptr; //Modify the node's parent's pointers
				Parent->parent = node;

				node->parent = Grandparent; //Change node's parent and leftchild
				node->rightChild = Parent;

				//Left rotation
				node->leftChild = Grandparent; //Change node's parent and rightChild
				node->parent = Grandparent->parent;

				Grandparent->parent = node; //Change grandparent's parent and child nodes
				Grandparent->rightChild = nullptr;
			}
			else if (findBalanceFactor(Parent) == -1) {//Perform left rotation
				Grandparent->parent->rightChild = Parent; //Modify great Grandparents child

				Parent->parent = Grandparent->parent; //Modify the parent's parent and child
				Parent->leftChild = Grandparent;

				Grandparent->parent = Parent; //Modify grandparent's parent and leftchild
				Grandparent->rightChild = nullptr;
			}
		}
	}

	// Find and return the balance factor of any given node
	int findBalanceFactor(Node* node) {
		int leftside = findLevelCount(node->leftChild);
		int rightside = findLevelCount(node->rightChild);

		return (leftside - rightside);
	}

	//Return the Level Count by recursively finding height of each branch starting with root node and return the maximum value found
	int findLevelCount(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return max(findLevelCount(node->leftChild), findLevelCount(node->rightChild)) + 1; //Add one on each call to account for the levels as we go deeper
	}

	//If user tries to printInOrder, call this function with root node of Tree
	void storeInOrder(Node* node, vector <string>& names) {
		if (node == nullptr) {
			return;
		}

		storeInOrder(node->leftChild, names);

		names.push_back(node->getName());

		storeInOrder(node->rightChild, names);
	}

	//If user tries to printPreOrder, call this function with root node of Tree
	void storePreOrder(Node* node, vector <string>& names) {
		if (node == nullptr) {
			return;
		}
		names.push_back(node->NAME);

		storeInOrder(node->leftChild, names);

		storeInOrder(node->rightChild, names);
	}

	//If user tries to printPostOrder, call this function with root node of Tree
	void storePostOrder(Node* node, vector <string>& names) {
		if (node == nullptr) {
			return;
		}

		storeInOrder(node->leftChild, names);

		storeInOrder(node->rightChild, names);

		names.push_back(node->NAME);
	}

	//Will print values stored in "names" vector with commas between each value, then clears vector
	void printNames(vector <string>& names) {
		for (int i = 0; i < names.size() - 1; i++) {
			cout << names[i] << ", ";
		}
		cout << names.at(names.size() - 1) << endl;
		names.clear();
	}

	//return id associated with name. If not found, return -1
	int searchName(string n, Node* node) { //node will start with root node
		if (node == nullptr) {
			return -1;
		}

		else if (node->NAME == n) { //If the given name is found, return that node's ID number
			return node->ID;
		}
		int searchLeft = searchName(n, node->leftChild);
		if (searchLeft != -1) { //If a value other than -1 is returned, then return that value
			return searchLeft;
		}

		int searchRight = searchName(n, node->rightChild);
		if (searchRight != -1) { //If a value other than -1 is returned, then return that value
			return searchRight; 
		}

		return -1; //If name is not found, return -1
	}

	//Search for a given ID, and print the name if found or unsuccessful if not found
	void searchID(int id, Node* node) {
		if (node == nullptr) {//If node equals nullptr, then ID does not exist
			cout << "Unsuccessful" << endl;
		}
		else if (node->ID == id) { //If id is equal to nodes ID, print the name of that node
			cout << node->NAME << endl;
		}
		else if (id < node->ID) { //If id is less than nodes ID, recursive call with nodes left child
			searchID(id, node->leftChild);
		}
		else {	//If none of above, then id must be greater than node ID, so recursive call with nodes right child
			searchID(id, node->rightChild);
		}
	}

	//Search for a given ID, and remove it if found. Also, print successful or unsuccessful
	void removeID(int id, Node* node) {
		if (node == nullptr) {//If node equals nullptr, then ID does not exist
			cout << "Unsuccessful" << endl;
		}
		else if (node->ID == id) { //If id is equal to nodes ID, modify the pointers and delete that node
			if (node->rightChild == nullptr && node->leftChild == nullptr) { //Check if the node to be deleted has no children
				//Figure out if node is a left or right child of its parent and have the parent point to nullptr instead of node
				if (node->parent->leftChild == node) {
					node->parent->leftChild = nullptr;
				}
				else {
					node->parent->rightChild = nullptr;
				}
				delete node;
			}

			else if (node->leftChild != nullptr && node->rightChild != nullptr) { //Check if the node to be deleted has two children
				Node* successor = findInorderSuccessor(node->rightChild);
				successor->parent = node->parent;
				successor->leftChild = node->leftChild;
				successor->rightChild = node->rightChild;

				successor->leftChild->parent = successor; //Set the nodes children to have the successor as a parent
				successor->rightChild->parent = successor;

				//Figure out if node is a left or right child of its parent and place the successor accordingly
				if (node->parent->leftChild == node) {
					node->parent->leftChild = successor;
				}
				else {
					node->parent->rightChild = successor;
				}
				delete node;
			}

			else { //Case where node has one child
				Node* child;
				
				//Find the child node and store it in child
				if (node->leftChild != nullptr) {
					child = node->leftChild;
				}
				else {
					child = node->rightChild;
				}
				child->parent = node->parent;

				//Figure out if node is a left or right child of its parent and place the new child accordingly
				if (node->parent->leftChild == node) {
					node->parent->leftChild = child;
				}
				else {
					node->parent->rightChild = child;
				}

				delete node;
			}
			cout << "Successful" << endl;
		}
		else if (id < node->ID) { //If id is less than nodes ID, recursive call with nodes left child
			removeID(id, node->leftChild);
		}
		else {	//If none of above, then id must be greater than node ID, so recursive call with nodes right child
			//cout << "ID num: " << id << " called rightchild: " << node->rightChild << endl;
			//if (node->rightChild != nullptr) {
			//	cout << "ERROR: not nullptr" << endl;
			//}
			removeID(id, node->rightChild);
		}
	}

	//Find and return pointer to Inorder Successor to be used in remove case of two children
	Node* findInorderSuccessor(Node* node) {
		if (node->leftChild == nullptr)
			return node;
		else {
			findInorderSuccessor(node->leftChild);
		}
	}

	//Will store all nodes of the tree in order, used in main for removeInOrder
	void storeInOrderNodes(Node* node, vector <Node*>& nodes) {
		if (node == nullptr) {
			return;
		}

		storeInOrderNodes(node->leftChild, nodes);

		nodes.push_back(node);

		storeInOrderNodes(node->rightChild, nodes);
	}
};