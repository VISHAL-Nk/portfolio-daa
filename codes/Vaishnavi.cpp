#include <bits/stdc++.h>
using namespace std;

// Function to allocate buses during peak hours
void allocateBuses3(priority_queue<pair<int, int>>& demandQueue3, int busesAvailable3) {
    while (!demandQueue3.empty() && busesAvailable3 > 0) {
        pair<int, int> topElement3 = demandQueue3.top();
        int waitingTime3 = topElement3.first;
        int routeId3 = topElement3.second;
        demandQueue3.pop();
        cout << "Allocating bus to route " << routeId3 << " with waiting time " << waitingTime3 << endl;
        busesAvailable3--;
    }
}

// BST implementation for managing low-demand stops
class BST3 {
public:
    struct Node3 {
        int stopId3;
        Node3* left3;
        Node3* right3;
        Node3(int id3) : stopId3(id3), left3(nullptr), right3(nullptr) {}
    };

    Node3* root3;

    BST3() : root3(nullptr) {}

    void insert3(int stopId3) {
        root3 = insertNode3(root3, stopId3);
    }

    void inOrderTraversal3(Node3* node3) {
        if (node3) {
            inOrderTraversal3(node3->left3);
            cout << "Stop " << node3->stopId3 << " has low demand.\n";
            inOrderTraversal3(node3->right3);
        }
    }

    void displayLowDemandStops3() {
        cout << "Low-demand stops during off-peak hours:\n";
        inOrderTraversal3(root3);
    }

private:
    Node3* insertNode3(Node3* node3, int stopId3) {
        if (!node3) return new Node3(stopId3);
        if (stopId3 < node3->stopId3)
            node3->left3 = insertNode3(node3->left3, stopId3);
        else if (stopId3 > node3->stopId3)
            node3->right3 = insertNode3(node3->right3, stopId3);
        return node3;
    }
};

// Graph representation for shortest path calculation
class Graph3 {
public:
    vector<vector<pair<int, int>>> adjList3;
    int numStops3;

    Graph3(int stops3) {
        numStops3 = stops3;
        adjList3.resize(stops3);
    }

    void addRoute3(int u3, int v3, int dist3) {
        adjList3[u3].push_back({v3, dist3});
        adjList3[v3].push_back({u3, dist3});
    }

    void bfs3(int start3) {
        vector<int> dist3(numStops3, INT_MAX);
        dist3[start3] = 0;
        queue<int> q3;
        q3.push(start3);

        while (!q3.empty()) {
            int u3 = q3.front();
            q3.pop();

            for (auto& neighbor3 : adjList3[u3]) {
                int v3 = neighbor3.first;
                int weight3 = neighbor3.second;

                if (dist3[u3] + weight3 < dist3[v3]) {
                    dist3[v3] = dist3[u3] + weight3;
                    q3.push(v3);
                }
            }
        }

        for (int i3 = 0; i3 < numStops3; i3++) {
            cout << "Shortest path from stop " << start3 << " to stop " << i3 << ": " << dist3[i3] << endl;
        }
    }
};

int main() {
    int choice3;
    cout << "Select an option:\n";
    cout << "1. Allocate buses during peak hours\n";
    cout << "2. Display low-demand stops\n";
    cout << "3. Calculate shortest paths between stops\n";
    cin >> choice3;

    if (choice3 == 1) {
        // Peak hour bus allocation
        priority_queue<pair<int, int>> demandQueue3;
        demandQueue3.push({50, 1});
        demandQueue3.push({30, 2});
        demandQueue3.push({70, 3});

        int busesAvailable3 = 2;
        cout << "Allocating buses during peak hours:\n";
        allocateBuses3(demandQueue3, busesAvailable3);
    } else if (choice3 == 2) {
        // Low-demand stop management
        BST3 bst3;
        bst3.insert3(101);
        bst3.insert3(103);
        bst3.insert3(105);

        bst3.displayLowDemandStops3();
    } else if (choice3 == 3) {
        // Shortest path calculation
        Graph3 g3(7);
        g3.addRoute3(0, 1, 10);
        g3.addRoute3(0, 2, 15);
        g3.addRoute3(1, 3, 5);
        g3.addRoute3(1, 4, 8);
        g3.addRoute3(2, 5, 10);
        g3.addRoute3(2, 6, 7);

        cout << "Shortest paths from main hub (stop 0):\n";
        g3.bfs3(0);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
