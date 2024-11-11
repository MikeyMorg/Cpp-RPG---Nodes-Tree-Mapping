#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include <vector>
#include "Story.h"


template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;

public:
    GameDecisionTree() : root(nullptr) {}

    // Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const string& filename, char delimiter) {
        //create our variables that will get used later on and create our Node
        string line;
        int event, left, right, key;
        Node<T> * newNode = nullptr;
        //also create our unorderedmap
        unordered_map<int, Node<T>* > nodeMap;
        //open file
        ifstream file(filename);

        //check to make sure file is open, otherwise return
        if (!file.is_open()) {
            cout << "File could not be opened" << endl;
            return;
        }

        while (getline(file, line)) {
            stringstream currLine(line);
            string tok;
            vector<string> storyInfo;

            //parse through current line, stopping at the delimiter and push back with tok,
            //and store the information into our vector space.
            while(getline(currLine, tok, delimiter)){
                storyInfo.push_back(tok);
            }

            // access our vector, and use stoi to turn string to int when necessary
            event = stoi(storyInfo[0]);
            string desc = storyInfo[1];
            left = stoi(storyInfo[2]);
            right = stoi(storyInfo[3]);

            //Initialize story object with the current line's information
            Story story(desc, event, left, right);

            //set current Node to our story
            newNode = new Node<T>(story);
            //newNode -> data.print();
            nodeMap[event] = newNode;

            //insert at root if root is empty -->
            if(root == nullptr) {
               root = newNode;
            }
        }
        //Set child nodes using for loop!
        for(int i = 1; i <= event; i++) {
            //set our key equal to the node's leftEventNumber
            key = nodeMap[i] -> data.leftEventNumber;
            nodeMap[i] -> left = nodeMap[key];

            //set our key equal to the node's rightEventNumber
            key = nodeMap[i] -> data.rightEventNumber;
            nodeMap[i] -> right = nodeMap[key];
        }
            //Close file
            file.close();
    }

    // Function to start the game and traverse the tree based on user input
    void playGame() {
        //create a node that starts out to point at our root node
        Node<T>* currNode =  root;
        int user;
        cout << "Welcome to Sandwich Quest! Press 1 to play, or any other number to exit!" << endl;
        cin >> user;
        //if user doesn't want to play, exit
        if(user != 1) {
            cout << "Thanks for playing!" << endl;
            return;
        }
        //currNode's child pointers aren't null we enter a while loop
        while( !(currNode -> left == nullptr && currNode -> right == nullptr) ) {
            //print out current node's data, which also prompts the user! Take in user input
            cout << currNode -> data.description << endl;
            cin >> user;

            //if user input is not equal to
            if(user != currNode -> data.leftEventNumber && user != currNode -> data.rightEventNumber) {
                while(user!= currNode -> data.leftEventNumber && user != currNode-> data.rightEventNumber) {
                    cout << "Please enter a valid path and try again!" << endl;
                    cin >> user;
                }
            }
            //if user input == left index then set current node to left
            if(user == currNode -> data.leftEventNumber) {
                currNode = currNode -> left;
            }
            //otherwise currentnode is set to right
            else {
                currNode = currNode -> right;
            }
        }
        //print out last node description
        cout << currNode -> data.description << endl;
        cout << "Thanks for playing!" << endl;
    }
};

#endif // GAMEDECISIONTREE_H
