#pragma once

#include "rand.h";
#include <set>
#include <iostream>
#include <iomanip>
#include<map>
#include<vector>
#include<utility>
#include<queue>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::get;
using std::set;
using std::priority_queue;
using std::greater;
using std::make_pair;
using std::unordered_map;

class GraphAL {
private:
    unordered_map<string, int> prices;

public:

    unordered_map<string, vector<pair<string, int>>> graph; //Adjacency List
    unordered_map<string, int> dist;

    void insertEdge(string from, string to, int wt);
    bool isEdge(string from, string to);

    int getPrice(string Node);
    vector<string> getNeighbors(string Node);
    vector<string> getVertices();
    int getDist(string Node); //Returns shortest path stored after dijkstra's algorithm was executed on a given source

    void print(); //Prints Graph data

    vector<int> dijkstra(string src);
};
