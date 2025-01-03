// Initialize the Trie with sample data
const trie = new Trie();

// Add sample tourism data
trie.insert("beach", ["Bondi Beach", "Waikiki Beach", "Copacabana Beach"]);
trie.insert("museum", ["Louvre Museum", "Metropolitan Museum of Art", "British Museum"]);
trie.insert("mountain", ["Mount Everest", "Rocky Mountains", "Kilimanjaro"]);
trie.insert("park", ["Yellowstone National Park", "Central Park", "Yosemite National Park"]);

// Handle search functionality
const searchInput = document.getElementById('searchInput');
const resultsContainer = document.getElementById('results');

searchInput.addEventListener('input', (e) => {
    const searchTerm = e.target.value.trim();
    const results = searchTerm ? trie.startsWith(searchTerm) : [];
    
    // Clear previous results
    resultsContainer.innerHTML = '';
    
    // Display new results with animation
    results.forEach(result => {
        const resultElement = document.createElement('div');
        resultElement.className = 'result-item fade-in';
        resultElement.textContent = result;
        resultsContainer.appendChild(resultElement);
    });
});