#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <string>
#include <set>
#include <sstream>  // For stringstream to parse input
#include <algorithm> // For std::reverse

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

void Traffic_Flow_optimisation() {
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

}



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
// void interactWithUser2(TwoThreeTree2& tree2) {
//     std::unordered_map<int, std::vector<std::pair<int, int>>> graph2;

//     // Sample road network (intersections and roads)
//     std::cout << "Enter the road network data (start intersection, end intersection, travel time):\n";
//     std::string input2;
//     while (true) {
//         std::cout << "Enter road data in format 'start end time' or type 'exit' to stop:\n";
//         std::getline(std::cin, input2);

//         if (input2 == "exit") break;

//         int start2, end2, time2;
//         std::stringstream ss2(input2);
//         if (!(ss2 >> start2 >> end2 >> time2)) {
//             std::cout << "Invalid input, please enter in 'start end time' format.\n";
//             continue;  // Skip invalid input
//         }

//         // Update the graph with the road data
//         graph2[start2].push_back({end2, time2});
//         graph2[end2].push_back({start2, time2});  // Assuming it's a bidirectional road

//         tree2.insert2(start2, time2);
//         tree2.insert2(end2, time2);
//     }

//     // Ask for the emergency vehicle's current location and destination
//     int currentLocation2, destination2;
//     std::cout << "Enter the current location of the emergency vehicle: ";
//     std::cin >> currentLocation2;
//     std::cout << "Enter the destination of the emergency: ";
//     std::cin >> destination2;

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
void interactWithUser2(TwoThreeTree2& tree2) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph2;

    // Predefined road network data using compile-time constants
    constexpr struct {
        int start2;
        int end2;
        int time2;
    } roadData2[] = {
        {1, 2, 5},  // Road from intersection 1 to 2, taking 5 minutes
        {2, 3, 3},  // Road from intersection 2 to 3, taking 3 minutes
        {1, 3, 7},  // Road from intersection 1 to 3, taking 7 minutes
        {3, 4, 2},  // Road from intersection 3 to 4, taking 2 minutes
        {2, 4, 6},  // Road from intersection 2 to 4, taking 6 minutes
        {4, 5, 4},  // Road from intersection 4 to 5, taking 4 minutes
        {3, 5, 8}   // Road from intersection 3 to 5, taking 8 minutes
    };

    // Build the graph with the predefined data at compile time
    for (const auto& road2 : roadData2) {
        // Add roads to the graph (bidirectional)
        graph2[road2.start2].push_back({road2.end2, road2.time2});
        graph2[road2.end2].push_back({road2.start2, road2.time2});
        
        // Add intersections to the 2-3 tree
        tree2.insert2(road2.start2, road2.time2);
        tree2.insert2(road2.end2, road2.time2);
    }

    // Predefined emergency scenario using compile-time constants
    constexpr int currentLocation2 = 1;  // Emergency vehicle starts at intersection 1
    constexpr int destination2 = 5;      // Destination is intersection 5

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


void Emergency_routing() {
    // Create an empty 2-3 Tree for the road network
    TwoThreeTree2 tree2;

    // Interact with the user to collect road network data and emergency route
    interactWithUser2(tree2);
}

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

void Bus_Scheduling() {
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

}

// Geographic coordinates for location tracking and distance calculations
struct Coordinates4 {
    double latitude;
    double longitude;
    
    // Default constructor for initialization
    Coordinates4(double lat = 0.0, double lon = 0.0) 
        : latitude(lat), longitude(lon) {}
    
    // Calculate distance between two points using Haversine formula
    double distanceTo4(const Coordinates4& other) const {
        const double R = 6371.0; // Earth's radius in kilometers
        double lat1 = latitude * M_PI / 180.0;
        double lat2 = other.latitude * M_PI / 180.0;
        double dLat = (other.latitude - latitude) * M_PI / 180.0;
        double dLon = (other.longitude - longitude) * M_PI / 180.0;
        
        double a = sin(dLat/2) * sin(dLat/2) +
                  cos(lat1) * cos(lat2) * 
                  sin(dLon/2) * sin(dLon/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        return R * c;
    }
};

// Weather information for better trip planning
struct WeatherInfo4 {
    double temperature;     // Average temperature in Celsius
    int rainyDays;         // Average number of rainy days per month
    int humidity;          // Average humidity percentage
    string weatherType;    // General weather description
    
    WeatherInfo4(double temp = 25.0, int rain = 5, int hum = 70, string type = "Sunny")
        : temperature(temp), rainyDays(rain), humidity(hum), weatherType(type) {}
};

// Comprehensive destination information structure
struct Destination4 {
    string name;
    string type;               // beach, museum, mountain, park, etc.
    string description;
    double rating;
    vector<string> bestSeasons;
    string priceRange;         // $, $$, $$$
    vector<string> activities;
    Coordinates4 coords;
    vector<pair<string, double>> nearbyDestinations;  // name and distance in km
    map<string, string> transportOptions;             // destination -> transport mode
    vector<string> bestTimeToVisit;
    map<string, double> entranceFees;                // currency -> amount
    bool requiresBooking;
    int avgVisitDuration;                            // in hours
    vector<pair<string, string>> openingHours;       // day -> "HH:MM-HH:MM"
    map<string, WeatherInfo4> monthlyWeather;         // month -> weather info
    vector<string> languages;                        // Spoken languages
    vector<string> facilities;                       // Available facilities
    string difficulty;                               // Easy, Moderate, Difficult
    bool wheelchairAccessible;
    vector<string> safetyTips;
    
    // Default constructor required for containers
    Destination4() : rating(0.0), requiresBooking(false), 
                   avgVisitDuration(0), wheelchairAccessible(false) {}
    
    // Main constructor with essential parameters
    Destination4(
        string n, string t, string desc, double r,
        Coordinates4 c, vector<string> seasons = {},
        string price = "$$"
    ) : name(n), type(t), description(desc), rating(r),
        coords(c), bestSeasons(seasons), priceRange(price),
        requiresBooking(false), avgVisitDuration(2),
        wheelchairAccessible(true) {}
};

// TrieNode class for efficient prefix-based searching
class TrieNode4 {
public:
    unordered_map<char, TrieNode4*> children;
    bool isEndOfWord;
    vector<Destination4> destinations;
    
    TrieNode4() : isEndOfWord(false) {}
    
    ~TrieNode4() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

// Main tourism recommendation system class
class TourismRecommendationSystem4 {
private:
    TrieNode4* root;
    unordered_map<string, Destination4> allDestinations;
    
    // Convert string to lowercase for case-insensitive searches
    string toLowerCase4(const string& str) {
        string lower = str;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }
    
    // Insert a keyword and destination into the trie
    void insertIntoTrie4(const string& keyword, const Destination4& dest) {
        TrieNode4* node = root;
        for (char c : keyword) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode4();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
        node->destinations.push_back(dest);
    }
    
    // Collect all destinations under a node
    void collectDestinations4(TrieNode4* node, vector<Destination4>& results) {
        if (node == nullptr) return;
        
        if (node->isEndOfWord) {
            results.insert(results.end(),
                         node->destinations.begin(),
                         node->destinations.end());
        }
        
        for (const auto& pair : node->children) {
            collectDestinations4(pair.second, results);
        }
    }
    
    // Calculate optimal route between destinations
    vector<string> calculateRoute4(const vector<Destination4>& destinations) {
        // Simple implementation - returns destinations sorted by distance
        vector<pair<double, string>> distances;
        for (const auto& dest : destinations) {
            distances.push_back({
                dest.coords.distanceTo4(destinations[0].coords),
                dest.name
            });
        }
        sort(distances.begin(), distances.end());
        
        vector<string> route;
        for (const auto& pair : distances) {
            route.push_back(pair.second);
        }
        return route;
    }

public:
    TourismRecommendationSystem4() {
        root = new TrieNode4();
    }
    
    ~TourismRecommendationSystem4() {
        delete root;
    }
    
    // Print a separator line
    void printSeparator4(char c = '-', int length = 80) {
        cout << string(length, c) << endl;
    }
    
    // Insert a destination into the system
    void insertDestination4(const Destination4& dest) {
        // Insert using both name and type as keywords
        insertIntoTrie4(toLowerCase4(dest.name), dest);
        insertIntoTrie4(toLowerCase4(dest.type), dest);
        allDestinations[dest.name] = dest;
    }
    
    // Search destinations with prefix
    vector<Destination4> searchWithPrefix4(const string& prefix) {
        string lower = toLowerCase4(prefix);
        TrieNode4* node = root;
        vector<Destination4> results;
        
        // Navigate to prefix node
        for (char c : lower) {
            if (node->children.find(c) == node->children.end()) {
                return results;
            }
            node = node->children[c];
        }
        
        // Collect all destinations under this prefix
        collectDestinations4(node, results);
        
        // Remove duplicates based on name
        sort(results.begin(), results.end(),
             [](const Destination4& a, const Destination4& b) {
                 return a.name < b.name;
             });
        results.erase(unique(results.begin(), results.end(),
                           [](const Destination4& a, const Destination4& b) {
                               return a.name == b.name;
                           }), results.end());
        
        // Sort by rating
        sort(results.begin(), results.end(),
             [](const Destination4& a, const Destination4& b) {
                 return a.rating > b.rating;
             });
             
        return results;
    }
    
    // Get detailed information about a destination
    void getDestinationDetails4(const string& name, const Coordinates4& userLocation) {
        if (allDestinations.find(name) == allDestinations.end()) {
            cout << "Destination not found!" << endl;
            return;
        }
        
        const Destination4& dest = allDestinations[name];
        
        printSeparator4('=');
        cout << "\033[1m" << dest.name << " (" << dest.type << ")\033[0m" << endl;
        printSeparator4();
        
        // Basic Information
        cout << "Rating: ";
        for (int i = 0; i < int(dest.rating); i++) cout << "*";
        cout << " " << fixed << setprecision(1) << dest.rating << "/5" << endl;
        
        cout << "Price Range: " << dest.priceRange << endl;
        cout << "Description: " << dest.description << endl;
        
        // Distance and Location
        double distance = userLocation.distanceTo4(dest.coords);
        cout << "\nLocation Details:" << endl;
        cout << "Distance from your location: " 
             << fixed << setprecision(1) << distance << " km" << endl;
        cout << "Coordinates: " << dest.coords.latitude << ", " 
             << dest.coords.longitude << endl;
        
        // Accessibility Information
        cout << "\nAccessibility:" << endl;
        cout << "Wheelchair Accessible: " 
             << (dest.wheelchairAccessible ? "Yes" : "No") << endl;
        cout << "Difficulty Level: " << dest.difficulty << endl;
        
        // Operating Hours
        if (!dest.openingHours.empty()) {
            cout << "\nOpening Hours:" << endl;
            for (const auto& hours : dest.openingHours) {
                cout << "  " << hours.first << ": " << hours.second << endl;
            }
        }
        
        // Activities and Features
        if (!dest.activities.empty()) {
            cout << "\nAvailable Activities:" << endl;
            for (const auto& activity : dest.activities) {
                cout << "  • " << activity << endl;
            }
        }
        
        // Nearby Attractions with Route
        if (!dest.nearbyDestinations.empty()) {
            cout << "\nNearby Attractions:" << endl;
            vector<Destination4> nearbyDests;
            nearbyDests.push_back(dest);
            for (const auto& nearby : dest.nearbyDestinations) {
                if (allDestinations.find(nearby.first) != allDestinations.end()) {
                    nearbyDests.push_back(allDestinations[nearby.first]);
                }
            }
            
            vector<string> route = calculateRoute4(nearbyDests);
            cout << "Suggested visiting order:" << endl;
            for (int i = 0; i < route.size(); i++) {
                cout << "  " << i+1 << ". " << route[i] << endl;
            }
        }
        
        // Safety Information
        if (!dest.safetyTips.empty()) {
            cout << "\nSafety Tips:" << endl;
            for (const auto& tip : dest.safetyTips) {
                cout << "  • " << tip << endl;
            }
        }
        
        printSeparator4('=');
    }
};

void tour_recommendation() {
    TourismRecommendationSystem4 system;
    
    // Insert sample destinations with detailed information
    Destination4 bondiBeach4(
        "Bondi Beach",
        "beach",
        "Famous Australian beach known for surfing and coastal walks",
        4.7,
        Coordinates4(-33.8915, 151.2767),
        {"Summer", "Spring"},
        "$$"
    );
    bondiBeach4.activities = {"Surfing", "Swimming", "Sunbathing", "Coastal Walking"};
    bondiBeach4.safetyTips = {"Swim between the flags", "Apply sunscreen", "Stay hydrated"};
    bondiBeach4.difficulty = "Easy";
    bondiBeach4.languages = {"English"};
    bondiBeach4.openingHours = {{"Daily", "24 hours"}};
    bondiBeach4.facilities = {"Showers", "Restrooms", "Cafes", "Lifeguard"};
    system.insertDestination4(bondiBeach4);
    
    Destination4 louvre4(
        "Louvre Museum",
        "museum",
        "World's largest art museum and home to the Mona Lisa",
        4.8,
        Coordinates4(48.8606, 2.3376),
        {"All year"},
        "$$$"
    );
    louvre4.activities = {"Art Viewing", "Guided Tours", "Photography"};
    louvre4.openingHours = {
        {"Monday", "Closed"},
        {"Tuesday-Sunday", "09:00-18:00"}
    };
    louvre4.requiresBooking = true;
    louvre4.languages = {"French", "English", "Spanish"};
    louvre4.wheelchairAccessible = true;
    system.insertDestination4(louvre4);
    
    // Predefined search queries and user location
    // Change here if you needed to try another search
    // Try to use beach, museum, Bondi
    const vector<string> searchQueries4 = {"beach", "museum", "Bondi"}; 
    const Coordinates4 userLocation4(48.8584, 2.2945); 
    
    // Perform searches with predefined queries
    for (const auto& query : searchQueries4) {
        cout << "\nSearching for: " << query << endl;
        auto results = system.searchWithPrefix4(query);
        
        if (results.empty()) {
            cout << "No destinations found matching '" << query << "'" << endl;
            continue;
        }
        
        cout << "\nFound " << results.size() << " matching destinations:\n";
        system.printSeparator4();
        
        for (int i = 0; i < results.size(); i++) {
            cout << i + 1 << ". " << results[i].name 
                 << " (" << results[i].type << ") - "
                 << results[i].rating << "*" << endl;
        }
        
        // Get details for each found destination
        for (const auto& result : results) {
            system.getDestinationDetails4(result.name, userLocation4);
        }
    }
    
}

int main()
{
    int n;
    while(1)
    {
        cout<<endl<<"Enter your Choice"<<endl;
        cout<<"1 --> Buisness case 1: Traffic Flow Optimization"<<endl;
        cout<<"2 --> Buisness case 2: Emergency Routing"<<endl;
        cout<<"3 --> Buisness case 3: Public Transportation Scheduling and Optimization"<<endl;
        cout<<"4 --> Buisness case 4: Tour Recommendation system "<<endl;
        cout<<"0 --> Exit"<<endl;
        cin>>n;
        switch(n)
        {
            case 1: Traffic_Flow_optimisation();
                    break;
            case 2: Emergency_routing();
                    break;
            case 3: Bus_Scheduling();
                    break;
            case 4: tour_recommendation();
                    break;
            case 0: exit(0);
                    break;
            default:cout<<"Enter the given value"<<endl;
        }
    }
}