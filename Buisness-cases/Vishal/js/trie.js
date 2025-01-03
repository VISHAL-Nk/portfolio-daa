class TrieNode {
    constructor() {
        this.children = new Map();
        this.isEndOfWord = false;
        this.recommendations = [];
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
    }

    insert(keyword, recommendations) {
        let node = this.root;
        for (const char of keyword.toLowerCase()) {
            if (!node.children.has(char)) {
                node.children.set(char, new TrieNode());
            }
            node = node.children.get(char);
        }
        node.isEndOfWord = true;
        node.recommendations = recommendations;
    }

    search(keyword) {
        let node = this.root;
        for (const char of keyword.toLowerCase()) {
            if (!node.children.has(char)) {
                return [];
            }
            node = node.children.get(char);
        }
        return node.isEndOfWord ? node.recommendations : [];
    }

    startsWith(prefix) {
        let node = this.root;
        for (const char of prefix.toLowerCase()) {
            if (!node.children.has(char)) {
                return [];
            }
            node = node.children.get(char);
        }
        const result = [];
        this.collectAllRecommendations(node, result);
        return result;
    }

    collectAllRecommendations(node, result) {
        if (node.isEndOfWord) {
            result.push(...node.recommendations);
        }
        for (const childNode of node.children.values()) {
            this.collectAllRecommendations(childNode, result);
        }
    }
}