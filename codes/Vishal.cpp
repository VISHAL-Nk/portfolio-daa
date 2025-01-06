#include <bits/stdc++.h>
using namespace std;

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

int main() {
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
    
    return 0;
}
