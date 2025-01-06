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
struct TreeNode2 {
    int value2; // The intersection ID or a similar unique identifier
    std::vector<TreeNode2*> children2;  // Adjacent nodes (intersections)
    std::vector<int> weights2;  // Edge weights (travel time or distance)
    TreeNode2(int v) : value2(v) {}
};

// 2-3 Tree class
class TwoThreeTree2 {
private:
    TreeNode2* root2;

    // Helper method to insert into 2-3 Tree (simplified version for the sake of the example)
    void insertHelper2(TreeNode2* node2, int value2, int weight2) {
        // For simplicity, we add values directly to the node if there's space.
        // Full tree insertion logic with balancing is omitted for brevity.
        node2->children2.push_back(new TreeNode2(value2));
        node2->weights2.push_back(weight2);
    }

public:
    TwoThreeTree2() : root2(nullptr) {}

    void insert2(int value2, int weight2) {
        if (!root2) {
            root2 = new TreeNode2(value2);
        } else {
            insertHelper2(root2, value2, weight2);
        }
    }

    TreeNode2* getRoot2() {
        return root2;
    }
};

// Dijkstra's Algorithm to find the shortest path
std::vector<int> dijkstra2(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph2, int start2, int target2) {
    // Priority queue to store (distance, node) pairs
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq2;
    std::unordered_map<int, int> dist2;
    std::unordered_map<int, int> parent2;

    // Initialize distances and queue
    for (const auto& node2 : graph2) {
        dist2[node2.first] = INT_MAX;
    }
    dist2[start2] = 0;
    pq2.push({0, start2});

    while (!pq2.empty()) {
        int u2 = pq2.top().second;
        pq2.pop();

        // If the destination is reached, stop
        if (u2 == target2) break;

        for (const auto& neighbor2 : graph2.at(u2)) {
            int v2 = neighbor2.first;
            int weight2 = neighbor2.second;

            if (dist2[u2] + weight2 < dist2[v2]) {
                dist2[v2] = dist2[u2] + weight2;
                parent2[v2] = u2;
                pq2.push({dist2[v2], v2});
            }
        }
    }

    // Reconstruct the path
    std::vector<int> path2;
    if (parent2.find(target2) == parent2.end()) {
        return path2;  // No path found
    }
    for (int v2 = target2; v2 != start2; v2 = parent2[v2]) {
        path2.push_back(v2);
    }
    path2.push_back(start2);
    std::reverse(path2.begin(), path2.end());
    return path2;
}

// Function to interact with the user and process the feedback dynamically
void interactWithUser2(TwoThreeTree2& tree2) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph2;

    // Sample road network (intersections and roads)
    std::cout << "Enter the road network data (start intersection, end intersection, travel time):\n";
    std::string input2;
    while (true) {
        std::cout << "Enter road data in format 'start end time' or type 'exit' to stop:\n";
        std::getline(std::cin, input2);

        if (input2 == "exit") break;

        int start2, end2, time2;
        std::stringstream ss2(input2);
        if (!(ss2 >> start2 >> end2 >> time2)) {
            std::cout << "Invalid input, please enter in 'start end time' format.\n";
            continue;  // Skip invalid input
        }

        // Update the graph with the road data
        graph2[start2].push_back({end2, time2});
        graph2[end2].push_back({start2, time2});  // Assuming it's a bidirectional road

        tree2.insert2(start2, time2);
        tree2.insert2(end2, time2);
    }

    // Ask for the emergency vehicle's current location and destination
    int currentLocation2, destination2;
    std::cout << "Enter the current location of the emergency vehicle: ";
    std::cin >> currentLocation2;
    std::cout << "Enter the destination of the emergency: ";
    std::cin >> destination2;

    // Find the shortest path using Dijkstra's algorithm
    std::vector<int> path2 = dijkstra2(graph2, currentLocation2, destination2);

    // Display the optimized route
    if (path2.empty()) {
        std::cout << "No path found from " << currentLocation2 << " to " << destination2 << ".\n";
    } else {
        std::cout << "Optimal route: ";
        for (int intersection2 : path2) {
            std::cout << intersection2 << " ";
        }
        std::cout << "\n";
    }
}
// void interactWithUser2(TwoThreeTree2& tree2) {
//     std::unordered_map<int, std::vector<std::pair<int, int>>> graph2;

//     // Predefined road network data using compile-time constants
//     constexpr struct {
//         int start2;
//         int end2;
//         int time2;
//     } roadData2[] = {
//         {1, 2, 5},  // Road from intersection 1 to 2, taking 5 minutes
//         {2, 3, 3},  // Road from intersection 2 to 3, taking 3 minutes
//         {1, 3, 7},  // Road from intersection 1 to 3, taking 7 minutes
//         {3, 4, 2},  // Road from intersection 3 to 4, taking 2 minutes
//         {2, 4, 6},  // Road from intersection 2 to 4, taking 6 minutes
//         {4, 5, 4},  // Road from intersection 4 to 5, taking 4 minutes
//         {3, 5, 8}   // Road from intersection 3 to 5, taking 8 minutes
//     };

//     // Build the graph with the predefined data at compile time
//     for (const auto& road2 : roadData2) {
//         // Add roads to the graph (bidirectional)
//         graph2[road2.start2].push_back({road2.end2, road2.time2});
//         graph2[road2.end2].push_back({road2.start2, road2.time2});
        
//         // Add intersections to the 2-3 tree
//         tree2.insert2(road2.start2, road2.time2);
//         tree2.insert2(road2.end2, road2.time2);
//     }

//     // Predefined emergency scenario using compile-time constants
//     constexpr int currentLocation2 = 1;  // Emergency vehicle starts at intersection 1
//     constexpr int destination2 = 5;      // Destination is intersection 5

//     // Find the shortest path using Dijkstra's algorithm
//     std::vector<int> path2 = dijkstra2(graph2, currentLocation2, destination2);

//     // Display the optimized route
//     if (path2.empty()) {
//         std::cout << "No path found from " << currentLocation2 << " to " << destination2 << ".\n";
//     } else {
//         std::cout << "Optimal route: ";
//         for (int intersection2 : path2) {
//             std::cout << intersection2 << " ";
//         }
//         std::cout << "\n";
//     }
// }


int main() {
    // Create an empty 2-3 Tree for the road network
    TwoThreeTree2 tree2;

    // Interact with the user to collect road network data and emergency route
    interactWithUser2(tree2);

    return 0;
}
