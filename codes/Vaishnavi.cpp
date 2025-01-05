
#include <bits/stdc++.h>
using namespace std;

// Function to allocate buses during peak hours
void allocateBuses(priority_queue<pair<int, int>>& demandQueue, int busesAvailable) {
    while (!demandQueue.empty() && busesAvailable > 0) {
        auto [waitingTime, routeId] = demandQueue.top();
        demandQueue.pop();
        cout << "Allocating bus to route " << routeId << " with waiting time " << waitingTime << endl;
        busesAvailable--;
    }
}

// BST implementation for managing low-demand stops
class BST {
public:
    struct Node {
        int stopId;
        Node* left;
        Node* right;
        Node(int id) : stopId(id), left(nullptr), right(nullptr) {}
    };

    Node* root;

    BST() : root(nullptr) {}

    void insert(int stopId) {
        root = insertNode(root, stopId);
    }

    void inOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << "Stop " << node->stopId << " has low demand.\n";
            inOrderTraversal(node->right);
        }
    }

    void displayLowDemandStops() {
        cout << "Low-demand stops during off-peak hours:\n";
        inOrderTraversal(root);
    }

private:
    Node* insertNode(Node* node, int stopId) {
        if (!node) return new Node(stopId);
        if (stopId < node->stopId)
            node->left = insertNode(node->left, stopId);
        else if (stopId > node->stopId)
            node->right = insertNode(node->right, stopId);
        return node;
    }
};

// Graph representation for shortest path calculation
class Graph {
public:
    vector<vector<pair<int, int>>> adjList;
    int numStops;

    Graph(int stops) {
        numStops = stops;
        adjList.resize(stops);
    }

    void addRoute(int u, int v, int dist) {
        adjList[u].push_back({v, dist});
        adjList[v].push_back({u, dist});
    }

    void bfs(int start) {
        vector<int> dist(numStops, INT_MAX);
        dist[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    q.push(v);
                }
            }
        }

        for (int i = 0; i < numStops; i++) {
            cout << "Shortest path from stop " << start << " to stop " << i << ": " << dist[i] << endl;
        }
    }
};

int main() {
    int choice;
    cout << "Select an option:\n";
    cout << "1. Allocate buses during peak hours\n";
    cout << "2. Display low-demand stops\n";
    cout << "3. Calculate shortest paths between stops\n";
    cin >> choice;

    if (choice == 1) {
        // Peak hour bus allocation
        priority_queue<pair<int, int>> demandQueue;
        demandQueue.push({50, 1});
        demandQueue.push({30, 2});
        demandQueue.push({70, 3});

        int busesAvailable = 2;
        cout << "Allocating buses during peak hours:\n";
        allocateBuses(demandQueue, busesAvailable);
    } else if (choice == 2) {
        // Low-demand stop management
        BST bst;
        bst.insert(101);
        bst.insert(103);
        bst.insert(105);

        bst.displayLowDemandStops();
    } else if (choice == 3) {
        // Shortest path calculation
        Graph g(7);
        g.addRoute(0, 1, 10);
        g.addRoute(0, 2, 15);
        g.addRoute(1, 3, 5);
        g.addRoute(1, 4, 8);
        g.addRoute(2, 5, 10);
        g.addRoute(2, 6, 7);

        cout << "Shortest paths from main hub (stop 0):\n";
        g.bfs(0);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
