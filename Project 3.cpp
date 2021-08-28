#include "rand.h"
#include "AVLTree.h"
#include "GraphAL.h"
#include <algorithm>
#include <functional>

#include <unordered_map>

using std::cin;
using std::queue;
using std::unordered_map;
using std::function;


AVLTree toPriceBST(GraphAL& graph, string source); //Creates a Balanced BST based on the graph passed in. Tree is based on the prices of the restaurants
AVLTree toDistBST(GraphAL& graph, string source); //Creates a Balanced BST based on the graph passed in. Tree is based on the distances of the restaurants from the source location

GraphAL makeGraph(int& verts, long& edges, vector<string>& names); //Creates and fills the graph object

void printVectorDist(Node* node);
void printVectorPrice(Node* node);


int main()
{
    long edges; 
    int verts;

    bool badInput = true;

    cout << "How many Vertices in the Graph: ";

    while (badInput) {
        cin >> verts;

        if (verts > 0) {
            badInput = false;
        }
        else {
            cout << "Please enter a positive non zero value" << endl;
        }
    }
    cout << "How many Edges in the Graph: ";     //RECOMMENDED: This graph is meant to represent a map in the form of an adjacency lists. Edge to Vertice Ratio should not exceed 4:1 (Most Real life maps are sparser)

    badInput = true;

    while (badInput) {
        cin >> edges;

        long maxEdges = verts * verts;
        if (edges <= 0) {
            cout << "Please enter a positive non zero value" << endl;
        }
        else if (edges < verts) {
            cout << "Please enter a value equal to or larger than the amount of vertices" << endl;
        }
        else if (edges > maxEdges) {
            cout << "Max amount of edges is " << maxEdges << ". Please try again" << endl;
        }
        else {
            badInput = false;
        }
    }
    cout << endl;

    srand((unsigned int)time(NULL)); //Sets seed for random restaurant name generation

    string src; //Source restaurant
    vector<string> names; //Stores restaurant names

    AVLTree priceTree;
    AVLTree distTree;

    GraphAL graph = makeGraph(verts, edges, names);

    /*cout << "Graph Representation:" << endl << endl;                        //Comment in for Graph Representation
    graph.print();
    cout << endl;*/

    int ind;
    cout << "Choose Location: ";

    badInput = true;

    while (badInput) {
        cin >> ind;

        if (ind < names.size() && ind > 0) {
            badInput = false;
        }
        else {
            cout << "Please enter a valid index" << endl;
        }
    }
    cout << endl;

    src = names.at(ind);

    cout << "Location Chosen: " << src << endl << endl;

    cout << "Organizing based on distance and price...";
    cout << endl << endl;

    //Conversion to the tree
    priceTree = toPriceBST(graph, src);
    distTree = toDistBST(graph, src);


    cout << "Distances from source: " << endl;                              //Comment in to list all prices and distances
    distTree.printInorder(distTree.root);
    cout << endl;

    cout << "Prices(Least to Greatest): " << endl;
    priceTree.printInorder(priceTree.root);
    cout << endl;

    while (true) {
        cout << "Do you want to: " << endl;
        cout << "1. Display information about a given restaurant" << endl;
        cout << "2. Display all restaurants of a given price or distance away from you" << endl;
        cout << "3. Display the restaurant of cheapest and most expensive price for a given distance" << endl;
        cout << "4. Display the restaurant of closest distance for a given price" << endl;
        cout << "0. Exit" << endl;

        badInput = true;
        int choice;

        while (badInput) {
            cin >> choice;

            if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 0) {
                badInput = false;
            }
            else {
                cout << "Please enter a valid choice" << endl;
            }
        }
        cout << endl;

        if (choice == 1) {
            cout << "Select a Restaurant Location: ";

            badInput = true;
            while (badInput) {
                cin >> ind;

                if (ind < names.size() && ind > 0) {
                    badInput = false;
                }
                else {
                    cout << "Please enter a valid index" << endl;
                }
            }

            cout << endl << endl;
            cout << endl;

            cout << "Restaurant Chosen: " << names.at(ind);
            cout << endl << endl;

            cout << "Price: " << "$" << graph.getPrice(names.at(ind)) << endl;

            Node* node = priceTree.search(graph.getPrice(names.at(ind)));

            int rank = 1;
            bool found = false;

            priceTree.kthSmallest(priceTree.root, node, rank, found);

            cout << names.at(ind) << " ranks " << "#" << rank << " among cheap restaurants alongside " << node->namesAndVal2.size() - 1 << " other restaurants" << endl;
            cout << names.at(ind) << " ranks " << "#" << priceTree.size - rank + 1 << " among expensive restaurants alongside " << node->namesAndVal2.size() - 1 << " other restaurants" << endl << endl;

            cout << "Distance: " << graph.getDist(names.at(ind)) << " miles away" << endl;

            Node* node2 = distTree.search(graph.getDist(names.at(ind)));

            rank = 1;
            found = false;

            distTree.kthSmallest(distTree.root, node2, rank, found);

            cout << names.at(ind) << " ranks " << "#" << rank << " among closest restaurants alongside " << node2->namesAndVal2.size() - 1 << " other restaurants" << endl;
            cout << names.at(ind) << " ranks " << "#" << distTree.size - rank + 1 << " among furthest restaurants alongside " << node2->namesAndVal2.size() - 1 << " other restaurants" << endl << endl;
        }
        else if (choice == 2) {
            cout << "Do you want to know all restaurants of: " << endl;
            cout << "1. A given price" << endl;
            cout << "2. A given distance" << endl;

            badInput = true;

            while (badInput) {
                cin >> choice;

                if (choice == 1 || choice == 2) {
                    badInput = false;
                }
                else {
                    cout << "Please enter a valid choice" << endl;
                }
            }
            cout << endl;

            if (choice == 1) {
                cout << "What price? ";

                int price;

                badInput = true;

                while (badInput) {
                    cin >> price;

                    if (price >= 0) {
                        badInput = false;
                    }
                    else {
                        cout << "Please enter a positive integer" << endl;
                    }
                }
                cout << endl;

                Node* node = priceTree.search(price);

                cout << "Restaurants of $" << price << ":" << endl;

                printVectorDist(node);
            }
            else if (choice == 2) {
                cout << "What distance? ";

                int dist;

                badInput = true;

                while (badInput) {
                    cin >> dist;

                    if (dist >= 0) {
                        badInput = false;
                    }
                    else {
                        cout << "Please enter a positive integer" << endl;
                    }
                }
                cout << endl;

                Node* node = distTree.search(dist);

                cout << "Restaurants " << dist << " miles away:" << endl;

                printVectorPrice(node);
            }
        }
        else if (choice == 3) {
            cout << "What distance? ";

            int dist;
           
            badInput = true;

            while (badInput) {
                cin >> dist;

                if (dist >= 0) {
                    badInput = false;
                }
                else {
                    cout << "Please enter a positive integer" << endl;
                }
            }
            cout << endl;

            Node* node = distTree.search(dist);

            if (node != nullptr) {
                cout << "Cheapest - " << get<0>(node->namesAndVal2.at(0)) << ":  $" << get<1>(node->namesAndVal2.at(0)) << endl;
                cout << "Most Expensive - " << get<0>(node->namesAndVal2.at(node->namesAndVal2.size() - 1)) << ":  $" << get<1>(node->namesAndVal2.at(node->namesAndVal2.size() - 1)) << endl << endl;
            }
            else {
                cout << "Cheapest - " << "none" << endl;
                cout << "Most Expensive - " << "none" << endl << endl;
            }

        }
        else if (choice == 4) {
            cout << "What price? ";

            int price;
            
            badInput = true;

            while (badInput) {
                cin >> price;

                if (price >= 0) {
                    badInput = false;
                }
                else {
                    cout << "Please enter a positive integer" << endl;
                }
            }
            cout << endl;

            Node* node = priceTree.search(price);

            if (node != nullptr) {
                cout << get<0>(node->namesAndVal2.at(0)) << ": " << get<1>(node->namesAndVal2.at(0)) << " miles away" << endl << endl;
            }
            else {
                cout << "none";
            }
        }
        else if (choice == 0) {
            break;
        }
    }
    return 0;
}

AVLTree toPriceBST(GraphAL& graph, string source) {
    AVLTree priceTree;

    //Basically perform a BFS on the graph and insert it to the tree on each step
    unordered_map<string, bool> visited;
    queue<string> q;

    visited[source] = true;
    q.push(source);

    //Use this to get the distances from the source node
    vector<int> callDijkstra = graph.dijkstra(source);

    while (!q.empty()) {
        string u = q.front();

        priceTree.root = priceTree.insert(priceTree.root, graph.getPrice(u), graph.getDist(u), u);

        q.pop();

        //sort(neighbors.begin(), neighbors.begin() + neighbors.size());                          //Uncomment for alphabetical sort

        vector<pair<string, int>>& links = graph.graph[u];

        for (int i = 0; i < links.size(); i++) {
            string v = get<0>(links.at(i));
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    priceTree.sortNodes(priceTree.root);

    return priceTree;
}

AVLTree toDistBST(GraphAL& graph, string source) {
    AVLTree distTree;

    //Conduct a Dijkstras Algorithm on the graph and insert nodes into the tree
    unordered_map<string, bool> visited;
    queue<string> q;

    visited[source] = true;
    q.push(source);

    vector<int> callDijkstra = graph.dijkstra(source);

    while (!q.empty()) {
        string u = q.front();

        distTree.root = distTree.insert(distTree.root, graph.getDist(u), graph.getPrice(u), u);

        q.pop();

        //sort(neighbors.begin(), neighbors.begin() + neighbors.size());                        //Uncomment for alphabetical traversal

        vector <pair<string, int>>& links = graph.graph[u];

        for (int i = 0; i < links.size(); i++) {
            string v = get<0>(links.at(i));
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    distTree.sortNodes(distTree.root);

    return distTree;
}

GraphAL makeGraph(int& verts, long& edges, vector<string>& names) {
    GraphAL graph;

    for (int i = 0; i < verts; i++) {
        names.push_back(Random::String(7));
    }
    for (int i = 0; i < edges; i++) {
        int vert1 = 0;
        int vert2 = 0;

        while (vert1 == vert2) {
            vert1 = Random::Int(0, verts - 1);
            vert2 = Random::Int(0, verts - 1);
        }
        graph.insertEdge(names.at(Random::Int(0, verts - 1)), names.at(Random::Int(0, verts - 1)), Random::Int(1, 50)); //insert our edges
    }

    return graph;
}

void printVectorDist(Node* node) {
    if (node != nullptr) {
        for (int i = 0; i < node->namesAndVal2.size(); i++) {
            cout << get<0>(node->namesAndVal2.at(i)) << ": " << get<1>(node->namesAndVal2.at(i)) << " miles away" << endl;
        }
    }
    else {
        cout << "none" << endl;
    }
    cout << endl;
}

void printVectorPrice(Node* node) {
    if (node != nullptr) {
        for (int i = 0; i < node->namesAndVal2.size(); i++) {
            cout << get<0>(node->namesAndVal2.at(i)) << ": $" << get<1>(node->namesAndVal2.at(i)) << endl;
        }
    }
    else {
        cout << "none" << endl;
    }
    cout << endl;
}