#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <string>
#include <set>
#include <sstream>  // For stringstream to parse input
#include <algorithm> // For std::reverse

// Define the 2-3 Tree Node and Tree Structure
struct TreeNode {
    int value; // The intersection ID or a similar unique identifier
    std::vector<TreeNode*> children;  // Adjacent nodes (intersections)
    std::vector<int> weights;  // Edge weights (travel time or distance)
    TreeNode(int v) : value(v) {}
};

// 2-3 Tree class
class TwoThreeTree {
private:
    TreeNode* root;

    // Helper method to insert into 2-3 Tree (simplified version for the sake of the example)
    void insertHelper(TreeNode* node, int value, int weight) {
        // For simplicity, we add values directly to the node if there's space.
        // Full tree insertion logic with balancing is omitted for brevity.
        node->children.push_back(new TreeNode(value));
        node->weights.push_back(weight);
    }

public:
    TwoThreeTree() : root(nullptr) {}

    void insert(int value, int weight) {
        if (!root) {
            root = new TreeNode(value);
        } else {
            insertHelper(root, value, weight);
        }
    }

    TreeNode* getRoot() {
        return root;
    }
};

// Dijkstra's Algorithm to find the shortest path
std::vector<int> dijkstra(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph, int start, int target) {
    // Priority queue to store (distance, node) pairs
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> parent;

    // Initialize distances and queue
    for (const auto& node : graph) {
        dist[node.first] = INT_MAX;
    }
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // If the destination is reached, stop
        if (u == target) break;

        for (const auto& neighbor : graph.at(u)) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Reconstruct the path
    std::vector<int> path;
    if (parent.find(target) == parent.end()) {
        return path;  // No path found
    }
    for (int v = target; v != start; v = parent[v]) {
        path.push_back(v);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

// Function to interact with the user and process the feedback dynamically
void interactWithUser(TwoThreeTree& tree) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;

    // Sample road network (intersections and roads)
    std::cout << "Enter the road network data (start intersection, end intersection, travel time):\n";
    std::string input;
    while (true) {
        std::cout << "Enter road data in format 'start end time' or type 'exit' to stop:\n";
        std::getline(std::cin, input);

        if (input == "exit") break;

        int start, end, time;
        std::stringstream ss(input);
        if (!(ss >> start >> end >> time)) {
            std::cout << "Invalid input, please enter in 'start end time' format.\n";
            continue;  // Skip invalid input
        }

        // Update the graph with the road data
        graph[start].push_back({end, time});
        graph[end].push_back({start, time});  // Assuming it's a bidirectional road

        tree.insert(start, time);
        tree.insert(end, time);
    }

    // Ask for the emergency vehicle's current location and destination
    int currentLocation, destination;
    std::cout << "Enter the current location of the emergency vehicle: ";
    std::cin >> currentLocation;
    std::cout << "Enter the destination of the emergency: ";
    std::cin >> destination;

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
    // Create an empty 2-3 Tree for the road network
    TwoThreeTree tree;

    // Interact with the user to collect road network data and emergency route
    interactWithUser(tree);

    return 0;
}