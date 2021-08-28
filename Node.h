#pragma once

#include <string>;

using std::string;
using std::vector;
using std::pair;

struct Node {
    vector<pair<string,int>> namesAndVal2;

    int val1;

    Node* left = nullptr;
    Node* right = nullptr;
};