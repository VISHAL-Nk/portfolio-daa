class TrieNode {
    constructor() {
        this.children = new Map();
        this.isEndOfWord = false;
        this.destinations = [];
    }
}

class TourismRecommendationSystem {
    constructor() {
        this.root = new TrieNode();
        this.allDestinations = new Map();
    }

    toLowerCase(str) {
        return str.toLowerCase();
    }

    insertIntoTrie(keyword, dest) {
        let node = this.root;
        const lowerKeyword = this.toLowerCase(keyword);

        for (const char of lowerKeyword) {
            if (!node.children.has(char)) {
                node.children.set(char, new TrieNode());
            }
            node = node.children.get(char);
        }
        node.isEndOfWord = true;
        node.destinations.push(dest);
    }

    collectDestinations(node) {
        const results = [];
        
        if (node.isEndOfWord) {
            results.push(...node.destinations);
        }

        for (const child of node.children.values()) {
            results.push(...this.collectDestinations(child));
        }

        return results;
    }

    insertDestination(dest) {
        this.insertIntoTrie(dest.name, dest);
        this.insertIntoTrie(dest.type, dest);
        this.allDestinations.set(dest.name, dest);
    }

    searchWithPrefix(prefix) {
        const lower = this.toLowerCase(prefix);
        let node = this.root;

        for (const char of lower) {
            if (!node.children.has(char)) {
                return [];
            }
            node = node.children.get(char);
        }

        const results = this.collectDestinations(node);
        return Array.from(new Map(results.map(dest => [dest.name, dest]))
            .values())
            .sort((a, b) => b.rating - a.rating);
    }
}