#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

#include "Node.h"

using std::endl;
using std::cout;
using std::pair;
using std::make_pair;
using std::get;

class AVLTree {
public:
    Node* root;
    int size;

    AVLTree(); //Default Constructor

    Node* insert(Node* root, int val1, int val2, string name);
    Node* search(int val1);

    Node* rrRotation(Node* parent);
    Node* llRotation(Node* parent);
    Node* lrRotation(Node* parent);
    Node* rlRotation(Node* parent);

    Node* balance(Node* temp);

    int getHeight(Node* node);

    void printInorder(Node* root);

    void sortNodes(Node* root); //Sorts the vectors within each node in the tree

    void kthSmallest(Node* root, Node* destination, int& temp2, bool& found);

    pair<string,int> findOptimal(int val1);
};

