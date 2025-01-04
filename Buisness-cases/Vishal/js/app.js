// Sample destinations data
const sampleDestinations = [
    {
        name: "Bondi Beach",
        type: "beach",
        description: "Famous Australian beach known for surfing and coastal walks",
        rating: 4.7,
        activities: ["Surfing", "Swimming", "Sunbathing", "Coastal Walking"],
        priceRange: "$$"
    },
    {
        name: "Louvre Museum",
        type: "museum",
        description: "World's largest art museum and home to the Mona Lisa",
        rating: 4.8,
        activities: ["Art Viewing", "Guided Tours", "Photography"],
        priceRange: "$$$"
    }
];

// Initialize the tourism system
const system = new TourismRecommendationSystem();
sampleDestinations.forEach(dest => system.insertDestination(dest));

// DOM elements
const searchInput = document.getElementById('searchInput');
const searchResults = document.getElementById('searchResults');
const implementationCode = document.getElementById('implementation-code');

// Display the implementation code
implementationCode.textContent = `#include <bits/stdc++.h>
using namespace std;

// Geographic coordinates for location tracking and distance calculations
struct Coordinates {
    double latitude;
    double longitude;
    
    // Default constructor for initialization
    Coordinates(double lat = 0.0, double lon = 0.0) 
        : latitude(lat), longitude(lon) {}
    
    // Calculate distance between two points using Haversine formula
    double distanceTo(const Coordinates& other) const {
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
struct WeatherInfo {
    double temperature;     // Average temperature in Celsius
    int rainyDays;         // Average number of rainy days per month
    int humidity;          // Average humidity percentage
    string weatherType;    // General weather description
    
    WeatherInfo(double temp = 25.0, int rain = 5, int hum = 70, string type = "Sunny")
        : temperature(temp), rainyDays(rain), humidity(hum), weatherType(type) {}
};

// Comprehensive destination information structure
struct Destination {
    string name;
    string type;               // beach, museum, mountain, park, etc.
    string description;
    double rating;
    vector<string> bestSeasons;
    string priceRange;         // $, $$, $$$
    vector<string> activities;
    Coordinates coords;
    vector<pair<string, double>> nearbyDestinations;  // name and distance in km
    map<string, string> transportOptions;             // destination -> transport mode
    vector<string> bestTimeToVisit;
    map<string, double> entranceFees;                // currency -> amount
    bool requiresBooking;
    int avgVisitDuration;                            // in hours
    vector<pair<string, string>> openingHours;       // day -> "HH:MM-HH:MM"
    map<string, WeatherInfo> monthlyWeather;         // month -> weather info
    vector<string> languages;                        // Spoken languages
    vector<string> facilities;                       // Available facilities
    string difficulty;                               // Easy, Moderate, Difficult
    bool wheelchairAccessible;
    vector<string> safetyTips;
    
    // Default constructor required for containers
    Destination() : rating(0.0), requiresBooking(false), 
                   avgVisitDuration(0), wheelchairAccessible(false) {}
    
    // Main constructor with essential parameters
    Destination(
        string n, string t, string desc, double r,
        Coordinates c, vector<string> seasons = {},
        string price = "$$"
    ) : name(n), type(t), description(desc), rating(r),
        coords(c), bestSeasons(seasons), priceRange(price),
        requiresBooking(false), avgVisitDuration(2),
        wheelchairAccessible(true) {}
};

// TrieNode class for efficient prefix-based searching
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    vector<Destination> destinations;
    
    TrieNode() : isEndOfWord(false) {}
    
    ~TrieNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

// Main tourism recommendation system class
class TourismRecommendationSystem {
private:
    TrieNode* root;
    unordered_map<string, Destination> allDestinations;
    
    // Convert string to lowercase for case-insensitive searches
    string toLowerCase(const string& str) {
        string lower = str;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }
    
    // Insert a keyword and destination into the trie
    void insertIntoTrie(const string& keyword, const Destination& dest) {
        TrieNode* node = root;
        for (char c : keyword) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
        node->destinations.push_back(dest);
    }
    
    // Collect all destinations under a node
    void collectDestinations(TrieNode* node, vector<Destination>& results) {
        if (node == nullptr) return;
        
        if (node->isEndOfWord) {
            results.insert(results.end(),
                         node->destinations.begin(),
                         node->destinations.end());
        }
        
        for (const auto& pair : node->children) {
            collectDestinations(pair.second, results);
        }
    }
    
    // Calculate optimal route between destinations
    vector<string> calculateRoute(const vector<Destination>& destinations) {
        // Simple implementation - returns destinations sorted by distance
        vector<pair<double, string>> distances;
        for (const auto& dest : destinations) {
            distances.push_back({
                dest.coords.distanceTo(destinations[0].coords),
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
    TourismRecommendationSystem() {
        root = new TrieNode();
    }
    
    ~TourismRecommendationSystem() {
        delete root;
    }
    
    // Print a separator line
    void printSeparator(char c = '-', int length = 80) {
        cout << string(length, c) << endl;
    }
    
    // Insert a destination into the system
    void insertDestination(const Destination& dest) {
        // Insert using both name and type as keywords
        insertIntoTrie(toLowerCase(dest.name), dest);
        insertIntoTrie(toLowerCase(dest.type), dest);
        allDestinations[dest.name] = dest;
    }
    
    // Search destinations with prefix
    vector<Destination> searchWithPrefix(const string& prefix) {
        string lower = toLowerCase(prefix);
        TrieNode* node = root;
        vector<Destination> results;
        
        // Navigate to prefix node
        for (char c : lower) {
            if (node->children.find(c) == node->children.end()) {
                return results;
            }
            node = node->children[c];
        }
        
        // Collect all destinations under this prefix
        collectDestinations(node, results);
        
        // Remove duplicates based on name
        sort(results.begin(), results.end(),
             [](const Destination& a, const Destination& b) {
                 return a.name < b.name;
             });
        results.erase(unique(results.begin(), results.end(),
                           [](const Destination& a, const Destination& b) {
                               return a.name == b.name;
                           }), results.end());
        
        // Sort by rating
        sort(results.begin(), results.end(),
             [](const Destination& a, const Destination& b) {
                 return a.rating > b.rating;
             });
             
        return results;
    }
    
    // Get detailed information about a destination
    void getDestinationDetails(const string& name, const Coordinates& userLocation) {
        if (allDestinations.find(name) == allDestinations.end()) {
            cout << "Destination not found!" << endl;
            return;
        }
        
        const Destination& dest = allDestinations[name];
        
        printSeparator('=');
        cout << "033[1m" << dest.name << " (" << dest.type << ")033[0m" << endl;
        printSeparator();
        
        // Basic Information
        cout << "Rating: ";
        for (int i = 0; i < int(dest.rating); i++) cout << "*";
        cout << " " << fixed << setprecision(1) << dest.rating << "/5" << endl;
        
        cout << "Price Range: " << dest.priceRange << endl;
        cout << "Description: " << dest.description << endl;
        
        // Distance and Location
        double distance = userLocation.distanceTo(dest.coords);
        cout << "Location Details:" << endl;
        cout << "Distance from your location: " 
             << fixed << setprecision(1) << distance << " km" << endl;
        cout << "Coordinates: " << dest.coords.latitude << ", " 
             << dest.coords.longitude << endl;
        
        // Accessibility Information
        cout << "Accessibility:" << endl;
        cout << "Wheelchair Accessible: " 
             << (dest.wheelchairAccessible ? "Yes" : "No") << endl;
        cout << "Difficulty Level: " << dest.difficulty << endl;
        
        // Operating Hours
        if (!dest.openingHours.empty()) {
            cout << "Opening Hours:" << endl;
            for (const auto& hours : dest.openingHours) {
                cout << "  " << hours.first << ": " << hours.second << endl;
            }
        }
        
        // Activities and Features
        if (!dest.activities.empty()) {
            cout << "Available Activities:" << endl;
            for (const auto& activity : dest.activities) {
                cout << "  • " << activity << endl;
            }
        }
        
        // Nearby Attractions with Route
        if (!dest.nearbyDestinations.empty()) {
            cout << "Nearby Attractions:" << endl;
            vector<Destination> nearbyDests;
            nearbyDests.push_back(dest);
            for (const auto& nearby : dest.nearbyDestinations) {
                if (allDestinations.find(nearby.first) != allDestinations.end()) {
                    nearbyDests.push_back(allDestinations[nearby.first]);
                }
            }
            
            vector<string> route = calculateRoute(nearbyDests);
            cout << "Suggested visiting order:" << endl;
            for (int i = 0; i < route.size(); i++) {
                cout << "  " << i+1 << ". " << route[i] << endl;
            }
        }
        
        // Safety Information
        if (!dest.safetyTips.empty()) {
            cout << "Safety Tips:" << endl;
            for (const auto& tip : dest.safetyTips) {
                cout << "  • " << tip << endl;
            }
        }
        
        printSeparator('=');
    }
};

int main() {
    TourismRecommendationSystem system;
    
    // Insert sample destinations with detailed information
    Destination bondiBeach(
        "Bondi Beach",
        "beach",
        "Famous Australian beach known for surfing and coastal walks",
        4.7,
        Coordinates(-33.8915, 151.2767),
        {"Summer", "Spring"},
        "$$"
    );
    bondiBeach.activities = {"Surfing", "Swimming", "Sunbathing", "Coastal Walking"};
    bondiBeach.safetyTips = {"Swim between the flags", "Apply sunscreen", "Stay hydrated"};
    bondiBeach.difficulty = "Easy";
    bondiBeach.languages = {"English"};
    bondiBeach.openingHours = {{"Daily", "24 hours"}};
    bondiBeach.facilities = {"Showers", "Restrooms", "Cafes", "Lifeguard"};
    system.insertDestination(bondiBeach);
    
    Destination louvre(
        "Louvre Museum",
        "museum",
        "World's largest art museum and home to the Mona Lisa",
        4.8,
        Coordinates(48.8606, 2.3376),
        {"All year"},
        "$$$"
    );
    louvre.activities = {"Art Viewing", "Guided Tours", "Photography"};
    louvre.openingHours = {
        {"Monday", "Closed"},
        {"Tuesday-Sunday", "09:00-18:00"}
    };
    louvre.requiresBooking = true;
    louvre.languages = {"French", "English", "Spanish"};
    louvre.wheelchairAccessible = true;
    system.insertDestination(louvre);
    
    // Predefined search queries and user location
    // Change here if you needed to try another search
    // Try to use beach, museum, Bondi
    const vector<string> searchQueries = {"beach", "museum", "Bondi"}; 
    const Coordinates userLocation(48.8584, 2.2945);  // Paris coordinates
    
    // Perform searches with predefined queries
    for (const auto& query : searchQueries) {
        cout << "Searching for: " << query << endl;
        auto results = system.searchWithPrefix(query);
        
        if (results.empty()) {
            cout << "No destinations found matching '" << query << "'" << endl;
            continue;
        }
        
        cout << "Found " << results.size() << " matching destinations:";
        system.printSeparator();
        
        for (int i = 0; i < results.size(); i++) {
            cout << i + 1 << ". " << results[i].name 
                 << " (" << results[i].type << ") - "
                 << results[i].rating << "*" << endl;
        }
        
        // Get details for each found destination
        for (const auto& result : results) {
            system.getDestinationDetails(result.name, userLocation);
        }
    }
    
    return 0;
}`;

// Create a result card
function createResultCard(dest) {
    return `
        <div class="result-card">
            <div style="display: flex; justify-content: space-between; align-items: flex-start">
                <div>
                    <h3 style="font-size: 1.25rem; font-weight: 600; margin-bottom: 0.5rem">
                        ${dest.name}
                    </h3>
                    <p style="opacity: 0.7">${dest.type}</p>
                </div>
                <div style="display: flex; align-items: center">
                    <span style="color: #fbbf24">★</span>
                    <span style="margin-left: 0.25rem; opacity: 0.7">
                        ${dest.rating}
                    </span>
                </div>
            </div>
            <p style="margin: 1rem 0">${dest.description}</p>
            ${dest.activities ? `
                <div style="margin-top: 1rem">
                    <h4 style="font-weight: 500; margin-bottom: 0.5rem">Activities:</h4>
                    <div style="display: flex; flex-wrap: wrap; gap: 0.5rem">
                        ${dest.activities.map(activity => `
                            <span style="background: rgba(255, 255, 255, 0.1); 
                                       padding: 0.25rem 0.75rem; border-radius: 9999px; 
                                       font-size: 0.875rem">
                                ${activity}
                            </span>
                        `).join('')}
                    </div>
                </div>
            ` : ''}
        </div>
    `;
}

// Handle search input
searchInput.addEventListener('input', (e) => {
    const query = e.target.value.trim();
    
    if (query === '') {
        searchResults.innerHTML = '';
        return;
    }

    const results = system.searchWithPrefix(query);
    searchResults.innerHTML = results.map(createResultCard).join('');
});