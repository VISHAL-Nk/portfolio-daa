#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

struct Edge1 {
    int to1, weight1;
    Edge1(int to1, int weight1) : to1(to1), weight1(weight1) {}
};

void addRoad1(unordered_map<int, vector<Edge1>>& graph1, int u1, int v1, int weight1) {
    graph1[u1].push_back(Edge1(v1, weight1));
    graph1[v1].push_back(Edge1(u1, weight1));
}

vector<int> dijkstra1(const unordered_map<int, vector<Edge1>>& graph1, int start1, int numNodes1) {
    vector<int> distances1(numNodes1, INT_MAX);
    distances1[start1] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq1;
    pq1.push({0, start1});

    while (!pq1.empty()) {
        int currentDist1 = pq1.top().first;
        int currentNode1 = pq1.top().second;
        pq1.pop();

        if (currentDist1 > distances1[currentNode1]) continue;

        for (size_t i1 = 0; i1 < graph1.at(currentNode1).size(); ++i1) {
            Edge1 edge1 = graph1.at(currentNode1)[i1];
            int neighbor1 = edge1.to1;
            int newDist1 = currentDist1 + edge1.weight1;

            if (newDist1 < distances1[neighbor1]) {
                distances1[neighbor1] = newDist1;
                pq1.push({newDist1, neighbor1});
            }
        }
    }

    return distances1;
}

void updateWeights1(unordered_map<int, vector<Edge1>>& graph1, const vector<pair<pair<int, int>, int>>& trafficData1) {
    for (size_t i1 = 0; i1 < trafficData1.size(); ++i1) {
        pair<pair<int, int>, int> traffic1 = trafficData1[i1];
        int u1 = traffic1.first.first;
        int v1 = traffic1.first.second;
        int congestion1 = traffic1.second;

        for (size_t j1 = 0; j1 < graph1[u1].size(); ++j1) {
            if (graph1[u1][j1].to1 == v1) {
                graph1[u1][j1].weight1 += congestion1;
            }
        }
        for (size_t j1 = 0; j1 < graph1[v1].size(); ++j1) {
            if (graph1[v1][j1].to1 == u1) {
                graph1[v1][j1].weight1 += congestion1;
            }
        }
    }
}

int main() {
    unordered_map<int, vector<Edge1>> graph1;
    int numNodes1 = 5;

    addRoad1(graph1, 0, 1, 5);
    addRoad1(graph1, 0, 2, 10);
    addRoad1(graph1, 1, 2, 2);
    addRoad1(graph1, 1, 3, 8);
    addRoad1(graph1, 2, 3, 3);

    cout << "Initial Shortest Paths from Node 0:" << endl;
    vector<int> distances1 = dijkstra1(graph1, 0, numNodes1);
    for (int i1 = 0; i1 < distances1.size(); ++i1) {
        if (distances1[i1] == INT_MAX) {
            cout << "Node 0 to Node " << i1 << ": no path" << endl;
        } else {
            cout << "Node 0 to Node " << i1 << ": " << distances1[i1] << endl;
        }
    }

    vector<pair<pair<int, int>, int>> trafficData1 = {
        {{0, 1}, 3},
        {{2, 3}, 5}
    };
    updateWeights1(graph1, trafficData1);

    cout << "\nUpdated Shortest Paths from Node 0 after Traffic Updates:" << endl;
    distances1 = dijkstra1(graph1, 0, numNodes1);
    for (int i1 = 0; i1 < distances1.size(); ++i1) {
        if (distances1[i1] == INT_MAX) {
            cout << "Node 0 to Node " << i1 << ": no path" << endl;
        } else {
            cout << "Node 0 to Node " << i1 << ": " << distances1[i1] << endl;
        }
    }

    return 0;
}

