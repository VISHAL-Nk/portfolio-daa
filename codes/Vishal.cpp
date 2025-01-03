#include <bits/stdc++.h>
using namespace std;

// Define a TrieNode
class TrieNode {
public:
    TrieNode* children[26]; // Each child represents a letter ('a' to 'z')
    bool isEndOfWord;
    vector<string> recommendations; // Store location-based suggestions

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

// Define a Trie for managing tourism recommendations
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a keyword with related recommendations
    void insert(string keyword, vector<string> recommendations) {
        TrieNode* node = root;
        for (char ch : keyword) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
        node->recommendations = recommendations;
    }

    // Search for a keyword and return related recommendations
    vector<string> search(string keyword) {
        TrieNode* node = root;
        for (char ch : keyword) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return {}; // Return empty vector if keyword not found
            }
            node = node->children[index];
        }
        return node->isEndOfWord ? node->recommendations : vector<string>{};
    }

    // Check if any keyword starts with a given prefix
    vector<string> startsWith(string prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return {}; // Return empty vector if prefix not found
            }
            node = node->children[index];
        }

        // Collect all recommendations from this node and its children
        vector<string> result;
        collectAllRecommendations(node, result);
        return result;
    }

    // Helper function to collect all recommendations recursively
    void collectAllRecommendations(TrieNode* node, vector<string>& result) {
        if (node == nullptr) return;

        if (node->isEndOfWord) {
            result.insert(result.end(), node->recommendations.begin(), node->recommendations.end());
        }

        for (int i = 0; i < 26; i++) {
            collectAllRecommendations(node->children[i], result);
        }
    }
};

// Main function
int main() {
    Trie trie;

    // Insert tourism-related keywords and recommendations
    trie.insert("beach", {"Bondi Beach", "Waikiki Beach", "Copacabana Beach"});
    trie.insert("museum", {"Louvre Museum", "Metropolitan Museum of Art", "British Museum"});
    trie.insert("mountain", {"Mount Everest", "Rocky Mountains", "Kilimanjaro"});
    trie.insert("park", {"Yellowstone National Park", "Central Park", "Yosemite National Park"});

    // Search and print recommendations
    string keyword = "museum";
    vector<string> recommendations = trie.search(keyword);

    cout << "Recommendations for '" << keyword << "':" << endl;
    for (const string& rec : recommendations) {
        cout << "- " << rec << endl;
    }

    // Prefix search for "mou" (mountain-related)
    string prefix = "mou";
    vector<string> prefixResults = trie.startsWith(prefix);

    cout << "\nRecommendations starting with '" << prefix << "':" << endl;
    for (const string& rec : prefixResults) {
        cout << "- " << rec << endl;
    }

    return 0;
}
