#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Tree.h"
using namespace std;

void readFile(string fileName, vector <string>& inputs) {
	ifstream file(fileName);
	string s;
	while (file.good()) {
		getline(file, s);
		inputs.push_back(s);
	}
	file.close();
}

int main() {
	Tree *tree = new Tree();
	
	vector <string> inputs; //Will hold each line of user input as its own index
	readFile("inputs.txt", inputs);
	int numCommands = stoi(inputs[0]); //The first value given to us is the number of instructions to run

	/*	USE TO VERIFY READFILE IS WORKING AS INTENDED
	for (int i = 0; i < inputs.size(); i++) {
		cout << "Input: " << inputs[i] << endl;
	}
	*/

	vector <string> names; //Will be used to hold names in a specified order for printing, cleared after each use
	string userIn; //Will be the first word in user input
	string name; //Will hold name specified by user, if necessary
	string id; //Will hold ID num specified by user, if necessary

	//Run for each index in input vector and perform related command
	for (int i = 1; i <= numCommands; i++) {
		userIn = inputs[i].substr(0, inputs[i].find(' ')); //Put the first word of the input in userIn

		if (userIn == ("insert")) {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector
			//cout << "This is vector after first word is erased: " << inputs[i] << endl;

			//FIXME: Do we not need to check for opening and closing quotations??
			if (inputs[i].at(0) != '\"' || inputs[i].at(inputs[i].find(' ') - 1) != '\"') {
				cout << "Unsuccessful" << endl;
				continue;
			}
			else {
				name = inputs[i].substr(1, inputs[i].find(' ') - 2); //Put the second word of the input in name (+1 and -2 at beginning and end to avoid quotes)
				inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the second word in the input vector

			}
			if (inputs[i].size() != 8) { //If the remaining value is not 8 digits, the ID number is the wrong size
				cout << "Unsuccessful" << endl;
				continue;
			}
			else {
				id = inputs[i]; //Remaining word in string should be the id
				//check each character, if a nondigit is detected then not valid number
				for (int j = 0; j < 8; j++) {
					if (!std::isdigit(id.at(j))) {
						cout << "Unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
						break;
					}
				}
				id = inputs[i]; //If this point is reached, id is valid 8 digit number & name was succesfully added

				Node *node = new Node(name, stoi(id));
				tree->insertNode(tree->root, node);
			}
		}

		else if (userIn == "printInOrder") {
			tree->storeInOrder(tree->root, names);
			tree->printNames(names);
		}

		else if (userIn == "printPreOrder") {
			tree->storePreOrder(tree->root, names);
			tree->printNames(names);
		}

		else if (userIn == "printPostOrder") {
			tree->storePostOrder(tree->root, names);
			tree->printNames(names);
		}

		else if (userIn == "printLevelCount") {
			int level = tree->findLevelCount(tree->root);
			cout << level << endl;
		}

		else if (userIn == "search") {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector and delimeter
			
			if (inputs[i].at(0) == '\"' && inputs[i].at(inputs[i].size() - 1) == '\"') {
				name = inputs[i].substr(1, inputs[i].size() - 2); //Put the second word of the input in name (+1 and -2 at beginning and end to avoid quotes)
				
				//cout << "Searching for: " << name << endl;
				int idNum = tree->searchName(name, tree->root); //Will hold ID num if found, otherwise -1
				if (idNum == -1) {
					cout << "Unsuccessful" << endl;
				}
				else {
					cout << idNum << endl;
				}
			}

			else if(inputs[i].size() == 8) { //If the remaining value is not 8 digits, the ID number is the wrong size
				id = inputs[i]; //Remaining word in string should be the id
				//check each character, if a nondigit is detected then not valid number
				for (int j = 0; j < 8; j++) {
					if (!std::isdigit(id.at(j))) {
						cout << "Unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
						break;
					}
				}
				tree->searchID(stoi(id), tree->root); //If this point is reached, id is valid 8 digit number so call the search for corresponding name
			}
			else {
				cout << "Unsuccessful" << endl;
			}
		}

		else if (userIn == "remove") {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector and delimeter

			if (inputs[i].size() != 8) { //If the remaining value is not 8 digits, the ID number is the wrong size
				cout << "Unsuccessful" << endl;
				continue;
			}
			else {
				id = inputs[i]; //Remaining word in string should be the id

				bool validID = true;
				//check each character, if a nondigit is detected then not valid number
				for (int j = 0; j < 8; j++) {
					if (!std::isdigit(id.at(j))) {
						validID = false;
						cout << "Unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
						break;
					}
				}
				if (validID) {//if ID is valid 8 digit number, call removeID function
					tree->removeID(stoi(id), tree->root);
				}
			}
		}

		else if (userIn == "removeInOrder") {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector and delimeter
			id = inputs[i]; //String id will hold the value provided by user

			bool validID = true;
			//check each character, if a nondigit is detected then not valid number
			for (int j = 0; j < id.size(); j++) {
				if (!std::isdigit(id.at(j))) {
					validID = false;
					cout << "unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
					break;
				}
			}

			if (validID) {
				vector <Node*> nodes;
				tree->storeInOrderNodes(tree->root, nodes); //Vector names will now hold all values in order
				int index = stoi(id); //Will hold the user provided index value as an int
				if (index >= nodes.size() || index < 0) { //If user provided index
					cout << "unsuccessful" << endl;
				}
				else {
					//cout << nodes[index]->ID << endl;
					tree->removeID(nodes[index]->ID, tree->root);
					nodes.clear();
				}
			}
		}

		else { //Command is not valid
			cout << "Unsuccessful" << endl;
		}
	}

	return 0;
};
