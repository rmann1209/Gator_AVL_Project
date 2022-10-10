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

	vector <string> names; //Will be used to hold names in a specified order for printing, cleared after each use
	string userIn; //Will be the first word in user input
	string name; //Will hold name specified by user, if necessary
	string id; //Will hold ID num specified by user, if necessary
	
	vector <string> inputs; //Will hold each line of user input as its own index
	//readFile("inputs3.txt", inputs);
	int numCommands; //The first value given to us is the number of instructions to run
	getline(cin, userIn);
	numCommands = stoi(userIn);

	//Run for each index in input vector and perform related command
	for (int i = 0; i < numCommands; i++) {
		getline(cin, userIn); //Store line in userIn string variable
		inputs.push_back(userIn); //inputs vector is used bc I initially wrote functionality to support read file, this allows me to still utilize that :)

		userIn = inputs[i].substr(0, inputs[i].find(' ')); //Put the first word of the input in userIn

		
		if (userIn == ("insert")) {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector
			//cout << "This is vector after first word is erased: " << inputs[i] << endl;

			if (inputs[i].at(0) != '\"' || (inputs[i].substr(1).find('\"') == -1)) { //Verify first value is " and at least one more " exists
				cout << "unsuccessful" << endl;
				continue;
			}
			else {
				name = inputs[i].substr(1); //Put the second word of the input in name just past the first quote
				name = name.substr(0, name.find('\"'));
				
				bool nameValid = true;
				//Verify name is valid
				for (int j = 0; j < name.size(); j++) {
					if (!(std::isalpha(name.at(j)) || name.at(j) == ' ')) { //check if any character is not alphabetic or a space
						cout << "unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
						nameValid = false;
						break;
					}
				}
				if (!nameValid) {
					continue;
				}
				inputs[i].erase(0, name.size()+3); //Erase the second word in the input vector (+3 to account for two quotes and space)

			}
			if (inputs[i].size() != 8) { //If the remaining value is not 8 digits, the ID number is the wrong size
				cout << "unsuccessful" << endl;
				continue;
			}
			else {
				id = inputs[i]; //Remaining word in string should be the id

				bool idValid = true;
				//check each character, if a nondigit is detected then not valid number
				for (int j = 0; j < 8; j++) {
					if (!std::isdigit(id.at(j))) {
						cout << "unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
						idValid = false;
						break;
					}
				}

				if (!idValid) {
					continue;
				}

				id = inputs[i]; //If this point is reached, id is valid 8 digit number & name was succesfully added

				Node *node = new Node(name, stoi(id));
				//cout << "Adding \"" << node->NAME << "\" " << node->ID << endl;
				tree->insertNode(tree->getRoot(), node);
				//cout << "Root node is " << tree->getRoot()->ID << endl;
			}
		}

		else if (userIn == "printInorder") {
			tree->storeInOrder(tree->getRoot(), names);
			tree->printNames(names);
		}

		else if (userIn == "printPreorder") {
			tree->storePreOrder(tree->getRoot(), names);
			tree->printNames(names);
		}

		else if (userIn == "printPostorder") {
			tree->storePostOrder(tree->getRoot(), names);
			tree->printNames(names);
		}

		else if (userIn == "printLevelCount") {
			int level = tree->findLevelCount(tree->getRoot());
			cout << level << endl;
		}

		else if (userIn == "search") {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector and delimeter
			
			if (inputs[i].at(0) == '\"' && inputs[i].at(inputs[i].size() - 1) == '\"') {
				name = inputs[i].substr(1, inputs[i].size() - 2); //Put the second word of the input in name (+1 and -2 at beginning and end to avoid quotes)
				
				vector <int> idNums; //Will store all ID occurrences with matching name
				//cout << "Searching for " << name << endl;
				tree->searchName(name, tree->getRoot(), idNums);

				if (idNums.size() == 0) {
					cout << "unsuccessful" << endl;
				}
				else {
					//Print each id value stored
					for (int k = 0; k < idNums.size(); k++) {
						cout << idNums[k] << endl;
					}
				}
				idNums.clear();
			}

			else if(inputs[i].size() == 8) { //If the remaining value is not 8 digits, the ID number is the wrong size
				id = inputs[i]; //Remaining word in string should be the id
				//check each character, if a nondigit is detected then not valid number
				for (int j = 0; j < 8; j++) {
					if (!std::isdigit(id.at(j))) {
						cout << "unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
						break;
					}
				}
				tree->searchID(stoi(id), tree->getRoot()); //If this point is reached, id is valid 8 digit number so call the search for corresponding name
			}
			else {
				cout << "unsuccessful" << endl;
			}
		}

		else if (userIn == "remove") {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector and delimeter

			if (inputs[i].size() != 8) { //If the remaining value is not 8 digits, the ID number is the wrong size
				cout << "unsuccessful" << endl;
				continue;
			}
			else {
				id = inputs[i]; //Remaining word in string should be the id

				bool validID = true;
				//check each character, if a nondigit is detected then not valid number
				for (int j = 0; j < 8; j++) {
					if (!std::isdigit(id.at(j))) {
						validID = false;
						cout << "unsuccessful" << endl; //If the character at j is not a digit, print unsuccessful and break
						break;
					}
				}
				if (validID) {//if ID is valid 8 digit number, call removeID function
					//cout << "Removing id num " << stoi(id) << endl;
					tree->removeID(stoi(id), tree->getRoot());
				}
			}
		}

		else if (userIn == "removeInorder") {
			inputs[i].erase(0, inputs[i].find(' ') + 1); //Erase the first word in the input vector and delimeter
			id = inputs[i]; //String id will hold the value provided by user
			//cout << "Index to remove is " << id << endl;

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
				tree->storeInOrderNodes(tree->getRoot(), nodes); //Vector names will now hold all values in order
				int index = stoi(id); //Will hold the user provided index value as an int
				if (index >= nodes.size() || index < 0) { //If user provided index is invalid
					cout << "unsuccessful" << endl;
				}
				else {
					//cout << nodes[index]->ID << endl;
					tree->removeID(nodes[index]->ID, tree->getRoot());
					nodes.clear();
				}
			}
		}

		else { //Command is not valid
			cout << "unsuccessful" << endl;
		}
	}

	delete tree;
	return 0;
};
