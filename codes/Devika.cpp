#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

void addRoad(unordered_map<int, vector<Edge>>& graph, int u, int v, int weight) {
    graph[u].push_back(Edge(v, weight));
    graph[v].push_back(Edge(u, weight));
}

vector<int> dijkstra(const unordered_map<int, vector<Edge>>& graph, int start, int numNodes) {
    vector<int> distances(numNodes, INT_MAX);
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDist > distances[currentNode]) continue;

        for (size_t i = 0; i < graph.at(currentNode).size(); ++i) {
            Edge edge = graph.at(currentNode)[i];
            int neighbor = edge.to;
            int newDist = currentDist + edge.weight;

            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.push({newDist, neighbor});
            }
        }
    }

    return distances;
}

void updateWeights(unordered_map<int, vector<Edge>>& graph, const vector<pair<pair<int, int>, int>>& trafficData) {
    for (size_t i = 0; i < trafficData.size(); ++i) {
        pair<pair<int, int>, int> traffic = trafficData[i];
        int u = traffic.first.first;
        int v = traffic.first.second;
        int congestion = traffic.second;

        for (size_t j = 0; j < graph[u].size(); ++j) {
            if (graph[u][j].to == v) {
                graph[u][j].weight += congestion;
            }
        }
        for (size_t j = 0; j < graph[v].size(); ++j) {
            if (graph[v][j].to == u) {
                graph[v][j].weight += congestion;
            }
        }
    }
}

int main() {
    unordered_map<int, vector<Edge>> graph;
    int numNodes = 5;

    addRoad(graph, 0, 1, 5);
    addRoad(graph, 0, 2, 10);
    addRoad(graph, 1, 2, 2);
    addRoad(graph, 1, 3, 8);
    addRoad(graph, 2, 3, 3);

    cout << "Initial Shortest Paths from Node 0:" << endl;
    vector<int> distances = dijkstra(graph, 0, numNodes);
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Node 0 to Node " << i << ": no path" << endl;
        } else {
            cout << "Node 0 to Node " << i << ": " << distances[i] << endl;
        }
    }

    vector<pair<pair<int, int>, int>> trafficData = {
        {{0, 1}, 3},
        {{2, 3}, 5}
    };
    updateWeights(graph, trafficData);

    cout << "\nUpdated Shortest Paths from Node 0 after Traffic Updates:" << endl;
    distances = dijkstra(graph, 0, numNodes);
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Node 0 to Node " << i << ": no path" << endl;
        } else {
            cout << "Node 0 to Node " << i << ": " << distances[i] << endl;
        }
    }

    return 0;
}