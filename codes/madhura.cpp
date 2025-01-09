#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

// Binary Search Tree Node
struct BSTNode {
    int key;
    int value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int k, int v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Binary Search Tree
class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int key, int value) {
        if (!node) return new BSTNode(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        return node;
    }

public:
    BST() : root(nullptr) {}

    void insert(int key, int value) {
        root = insert(root, key, value);
    }
};

// Lookup table to store precomputed shortest distances between nodes
std::unordered_map<int, std::unordered_map<int, int>> lookupTable;

// Dijkstra's algorithm
std::vector<int> dijkstra(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph, int start, int end) {
    // Check lookup table first
    if (lookupTable.find(start) != lookupTable.end() && lookupTable[start].find(end) != lookupTable[start].end()) {
        std::cout << "Retrieved from lookup table: Distance = " << lookupTable[start][end] << "\n";
    }

    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;
    auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.second > b.second; };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);

    for (const auto& node : graph) {
        dist[node.first] = std::numeric_limits<int>::max();
    }
    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        auto current_pair = pq.top();
        int current = current_pair.first;
        int d = current_pair.second;
        pq.pop();

        if (current == end) break;

        for (const auto& neighbor : graph.at(current)) {
            int next = neighbor.first;
            int weight = neighbor.second;
            int newDist = d + weight;
            if (newDist < dist[next]) {
                dist[next] = newDist;
                prev[next] = current;
                pq.push({next, newDist});
            }
        }
    }

    std::vector<int> path;
    for (int at = end; prev.find(at) != prev.end(); at = prev[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    // Store result in lookup table
    lookupTable[start][end] = dist[end];
    lookupTable[end][start] = dist[end]; // Symmetric path

    return path;
}

// Heap sort implementation
void heapify(std::vector<std::tuple<int, int, int>>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && std::get<2>(arr[left]) > std::get<2>(arr[largest]))
        largest = left;

    if (right < n && std::get<2>(arr[right]) > std::get<2>(arr[largest]))
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<std::tuple<int, int, int>>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Interaction function
void interactWithUser(BST& tree) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;

    // Predefined road network data using compile-time constants
    std::vector<std::tuple<int, int, int>> roadData = {
        {1, 2, 5}, {2, 3, 3}, {1, 3, 7}, {3, 4, 2}, {2, 4, 6}, {4, 5, 4}, {3, 5, 8}
    };

    // Sort roads by travel time using heap sort
    heapSort(roadData);

    // Build the graph with the sorted data
    for (const auto& road : roadData) {
        int start = std::get<0>(road);
        int end = std::get<1>(road);
        int time = std::get<2>(road);

        graph[start].push_back({end, time});
        graph[end].push_back({start, time});

        // Add intersections to the binary search tree
        tree.insert(start, time);
        tree.insert(end, time);
    }

    // Predefined emergency scenario
    constexpr int currentLocation = 1;
    constexpr int destination = 5;

    // Find the shortest path using Dijkstra's algorithm
    std::vector<int> path = dijkstra(graph, currentLocation, destination);

    // Display the optimized route
    if (path.empty()) {
        std::cout << "No path found from " << currentLocation << " to " << destination << ".\n";
    } else {
        std::cout << "Optimal route: ";
        for (int intersection : path) {
            std::cout << intersection << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    BST tree;
    interactWithUser(tree);
    return 0;
}