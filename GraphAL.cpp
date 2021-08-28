#include "GraphAL.h"

void GraphAL::insertEdge(string from, string to, int wt) {
    if (graph.count(from) == 0) {
        prices[from] = Random::Int(5, 300);
    }

    if (graph.count(to) == 0) {
        prices[to] = Random::Int(5, 300);
    }

    if (from != to && isEdge(from, to) == false) {
        graph[from].push_back(make_pair(to, wt));
        graph[to].push_back(make_pair(from, wt));
    }
}

bool GraphAL::isEdge(string from, string to) {
    if (graph.count(from) == 0) {
        return false;
    }

    for (int i = 0; i < graph[from].size(); i++) {
        if (graph[from].at(i).first == to) {
            return true;
        }
    }
    return false;
}

void GraphAL::print() {
    int i = 1;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        cout << it->first << "--->";
        for (int i = 0; i < (it->second).size(); i++) {
            cout << (it->second).at(i).first << " " << (it->second).at(i).second << " | ";
        }
        cout << endl;
    }
}

int GraphAL::getPrice(string Node) {
    return prices[Node];
}

vector<string> GraphAL::getNeighbors(string Node) {
    vector<string> neighbors;

    for (int i = 0; i < graph[Node].size(); i++) {
        neighbors.push_back(get<0>(graph[Node].at(i)));
    }
    return neighbors;
}

vector<string> GraphAL::getVertices() {
    int indexVal = 0;
    vector<string> vertices;
    map<string, int> vS;
    for (auto it = graph.begin(); it != graph.end(); it++) {
        if (vS.find(it->first) == vS.end()) {
            vS[it->first] = indexVal;
            vertices.push_back(it->first);
            indexVal++;
        }
    }

    return vertices;
}

// implementation of dijkstras algortithm for final project
// dijkstraCompute callculates the shortest path from the source to all other vertices in the graph
vector<int> GraphAL::dijkstra(string src) {
    //v represents #of vertices
    int v = graph.size();
    vector<string> vIndex = getVertices();

    // initialize 2 vectors and 2 sets
    //set of vertices for which we have already computed shortest path
    //initially empty except for source vertex
    set<string> s;
    s.insert(src);

    //set of the vertices we still need to process
    //initialize to contain all vertices
    map<string, int> vS;
    int indexVal = 0;
    for (auto it = graph.begin(); it != graph.end(); it++) {
        if (vS.find(it->first) == vS.end()) {
            vS[it->first] = indexVal;
            indexVal++;
        }
    }
    map<int, string> vMap; // vMap will use int keys for better indexing in the algorithm
    int index = 0;
    for (auto it = vS.begin(); it != vS.end(); it++) {
        vMap[index] = it->first;
        index++;
    }
    int srcInt = vS[src];

    //vector containing shortest distance from s to v
    //initialize source to 0, others to infinity, size = v
    vector<int> d(v, INT8_MAX);
    // d[src] = 0;

    //vector containing predecessor of v in path from s to v
    //initialize all to -1
    vector<string> p(v, "-1");

    // pair<int, int>: distance, node
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // push the soure node into pq
    pq.push(make_pair(0, srcInt)); // dist, node
    d[srcInt] = 0;
    p[srcInt] = src;


    while (!pq.empty()) {
        pair<int, int> curr = pq.top();
        pq.pop();

        // get current node
        int u = curr.second;
        string graphKey = vMap[u];

        // look at each neigbhor of the current node u
        for (auto it = graph[graphKey].begin();it != graph[graphKey].end(); it++) {
            int v = vS[it->first]; // neighbor
            int w = it->second; // u->v the weight of the edge
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.push(make_pair(d[v], v));
                p[v] = vIndex[u];
            }
        }
    }
    for (int i = 0; i < d.size(); i++) {
        dist[vIndex.at(i)] = d[i];
    }
    return d;
}

int GraphAL::getDist(string Node) {
    return dist[Node];
}