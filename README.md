<div align="center">

# 🚀 DAA Portfolio - Smart City Solutions

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![HTML](https://img.shields.io/badge/HTML-5-E34F26?logo=html5&logoColor=white)](https://developer.mozilla.org/en-US/docs/Web/HTML)
[![CSS](https://img.shields.io/badge/CSS-3-1572B6?logo=css3&logoColor=white)](https://developer.mozilla.org/en-US/docs/Web/CSS)
[![JavaScript](https://img.shields.io/badge/JavaScript-ES6-F7DF1E?logo=javascript&logoColor=black)](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)

**A comprehensive portfolio showcasing algorithmic solutions for real-world smart city challenges**

[🌐 View Live Demo](#) | [📖 Documentation](#features) | [👥 Team](#team-members)

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Business Cases](#-business-cases)
- [Technologies Used](#-technologies-used)
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [Usage](#-usage)
- [Algorithms Implemented](#-algorithms-implemented)
- [Team Members](#-team-members)
- [Contributing](#-contributing)
- [License](#-license)

---

## 🌟 Overview

This project is a **Design and Analysis of Algorithms (DAA)** portfolio that demonstrates the practical application of various data structures and algorithms to solve real-world smart city problems. The portfolio includes interactive web visualizations and efficient C++ implementations of complex algorithmic solutions.

### 🎯 Project Goals

- Implement efficient algorithms for urban infrastructure optimization
- Demonstrate proficiency in data structures (Trees, Graphs, Heaps, HashMaps)
- Provide interactive web-based visualizations
- Solve real-world business cases using algorithmic approaches

---

## ✨ Features

### 🖥️ Interactive Web Interface
- **Responsive Design**: Mobile-first approach with modern UI/UX
- **Smooth Animations**: CSS animations and parallax effects
- **Project Showcase**: Comprehensive overview of team members and business cases
- **Smart Navigation**: Easy-to-use navigation system

### 🧮 Algorithm Implementations
- **Graph Algorithms**: Dijkstra's shortest path, BFS/DFS
- **Tree Structures**: Binary Search Trees, Tries
- **Priority Queues**: Heap-based priority management
- **Optimization Algorithms**: Dynamic traffic flow optimization

---

## 💼 Business Cases

### 1️⃣ Traffic Flow Optimization
**Developer**: Devika D Desai (USN: 01FE23BCS089)

**Algorithm**: Dijkstra's Shortest Path with Dynamic Weight Updates

**Features**:
- Real-time traffic congestion monitoring
- Dynamic route optimization based on current traffic conditions
- Weight updates for road segments based on traffic data
- Efficient shortest path calculation for city navigation

**Implementation**: `codes/Devika.cpp`

---

### 2️⃣ Emergency Vehicle Routing
**Developer**: Madhura (USN: 01FE23BCS103)

**Algorithm**: Dijkstra's Algorithm with Lookup Table Optimization

**Features**:
- Precomputed shortest paths for critical routes
- Priority-based emergency vehicle routing
- Binary Search Tree for route management
- Lookup table for instant route retrieval

**Implementation**: `codes/madhura.cpp`

---

### 3️⃣ Public Transport Management
**Developer**: Vaishnavi R Honnagudi (USN: 01FE23BCS125)

**Algorithm**: Priority Queue with BST for Demand Management

**Features**:
- Peak hour bus allocation using max-heap
- Low-demand route identification using BST
- Efficient resource distribution
- Real-time demand tracking

**Implementation**: `codes/Vaishnavi.cpp`

---

### 4️⃣ Tourism Recommendation System
**Developer**: Vishal (USN: 01FE23BCS294)

**Algorithm**: Trie-based Search with Geographic Calculations

**Features**:
- Prefix-based destination search using Trie
- Haversine formula for distance calculations
- Weather-based recommendations
- Multi-criteria filtering (price, rating, season, accessibility)
- Comprehensive destination information including:
  - Opening hours and entrance fees
  - Transport options and nearby attractions
  - Accessibility features and safety tips
  - Seasonal weather patterns

**Implementation**: `codes/Vishal.cpp`

---

## 🛠️ Technologies Used

### Frontend
![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)
![CSS3](https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)

- **HTML5**: Semantic markup and structure
- **CSS3**: Advanced styling with flexbox, grid, and animations
- **Vanilla JavaScript**: DOM manipulation and interactive features
- **Google Fonts**: Typography (Inter, Poppins)

### Backend/Algorithms
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)

- **C++17**: Core algorithm implementations
- **STL**: Standard Template Library for data structures

### Key Libraries & Data Structures
- `<vector>`, `<queue>`, `<unordered_map>` - STL containers
- `<algorithm>` - Sorting and searching utilities
- `<cmath>` - Mathematical computations

---

## 📁 Project Structure

```
portfolio-daa/
│
├── index.html                      # Main landing page
├── README.md                       # Project documentation
├── script.js                       # Main JavaScript file
├── styles.css                      # Main stylesheet
│
├── Buisness-cases/                 # Business case demonstrations
│   ├── index.html                  # Team members overview
│   ├── script.js
│   ├── styles.css
│   ├── Devika/                     # Traffic Flow Optimization
│   ├── Madhura/                    # Emergency Vehicle Routing
│   ├── Vaishnavi/                  # Public Transport Management
│   └── Vishal/                     # Tourism Recommendation System
│
├── codes/                          # C++ Algorithm Implementations
│   ├── main.cpp                    # Integrated solution
│   ├── Devika.cpp                  # Traffic optimization algorithms
│   ├── madhura.cpp                 # Emergency routing algorithms
│   ├── Vaishnavi.cpp              # Transport management algorithms
│   └── Vishal.cpp                  # Tourism recommendation algorithms
│
├── Project-Overview/               # Project showcase
│   ├── index.html                  # Overview page
│   ├── css/                        # Modular stylesheets
│   │   ├── main.css
│   │   ├── animations.css
│   │   ├── components.css
│   │   └── components/
│   └── js/                         # JavaScript modules
│       ├── data.js                 # Team and budget data
│       ├── main.js
│       ├── animations.js
│       └── modules/
│
├── js/                             # Global JavaScript
│   ├── animations.js
│   ├── navigation.js
│   └── parallax.js
│
└── styles/                         # Global styles
    ├── variables.css               # CSS custom properties
    ├── typography.css              # Font styles
    ├── layout.css                  # Layout utilities
    └── components/                 # Component styles
        ├── cards.css
        └── header.css
```

---

## 🚀 Installation

### Prerequisites
- A modern web browser (Chrome, Firefox, Safari, Edge)
- C++ compiler (GCC, Clang, or MSVC) for running algorithm implementations
- Text editor or IDE (VS Code recommended)

### Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/VISHAL-Nk/portfolio-daa.git
   cd portfolio-daa
   ```

2. **Open the project**
   ```bash
   # Open in VS Code
   code .
   
   # Or open index.html in your browser
   open index.html  # macOS
   start index.html # Windows
   xdg-open index.html # Linux
   ```

3. **Compile C++ files** (optional)
   ```bash
   cd codes
   
   # Compile individual files
   g++ -std=c++17 Devika.cpp -o Devika
   g++ -std=c++17 madhura.cpp -o madhura
   g++ -std=c++17 Vaishnavi.cpp -o Vaishnavi
   g++ -std=c++17 Vishal.cpp -o Vishal
   
   # Compile integrated solution
   g++ -std=c++17 main.cpp -o main
   
   # Run
   ./main  # Linux/macOS
   main.exe # Windows
   ```

---

## 💻 Usage

### Web Interface

1. **Home Page**: Navigate to `index.html` to see the landing page with topics covered
2. **Project Overview**: Click "Project Overview" to see team details and project information
3. **Business Cases**: Click "Business Cases" to explore individual algorithm implementations
4. **Interactive Demos**: Each team member's page includes interactive demonstrations

### Running Algorithms

```bash
# Navigate to codes directory
cd codes

# Run integrated solution
./main

# Or run individual solutions
./Devika    # Traffic Flow Optimization
./madhura   # Emergency Vehicle Routing
./Vaishnavi # Public Transport Management
./Vishal    # Tourism Recommendation System
```

---

## 🧩 Algorithms Implemented

### Data Structures

| Structure | Usage | Implementation |
|-----------|-------|----------------|
| **Graph (Adjacency List)** | Road networks, routing | `unordered_map<int, vector<Edge>>` |
| **Priority Queue (Heap)** | Dijkstra's algorithm, demand management | `priority_queue<pair<int, int>>` |
| **Binary Search Tree** | Route management, low-demand tracking | Custom BST class |
| **Trie** | Prefix-based search | Custom TrieNode class |
| **Hash Map** | Lookup tables, fast retrieval | `unordered_map` |

### Algorithms

#### 1. Dijkstra's Shortest Path
- **Time Complexity**: O((V + E) log V)
- **Space Complexity**: O(V)
- **Use Cases**: Traffic optimization, emergency routing

#### 2. Trie Search
- **Time Complexity**: O(m) where m is key length
- **Space Complexity**: O(ALPHABET_SIZE * N)
- **Use Cases**: Autocomplete, prefix matching

#### 3. Priority Queue Operations
- **Insert**: O(log n)
- **Extract Max/Min**: O(log n)
- **Use Cases**: Resource allocation, scheduling

#### 4. BST Operations
- **Search/Insert/Delete**: O(log n) average
- **In-order Traversal**: O(n)
- **Use Cases**: Sorted data management

---

## 👥 Team Members

<table>
  <tr>
    <td align="center">
      <img src="https://ui-avatars.com/api/?name=Devika+D+Desai&background=667eea&color=fff&size=100" width="100px;" alt=""/>
      <br />
      <sub><b>Devika D Desai</b></sub>
      <br />
      <sub>Roll No: 218</sub>
      <br />
      <sub>USN: 01FE23BCS089</sub>
      <br />
      <sub>🚦 Traffic Flow Optimization</sub>
    </td>
    <td align="center">
      <img src="https://ui-avatars.com/api/?name=Madhura&background=f093fb&color=fff&size=100" width="100px;" alt=""/>
      <br />
      <sub><b>Madhura</b></sub>
      <br />
      <sub>Roll No: 221</sub>
      <br />
      <sub>USN: 01FE23BCS103</sub>
      <br />
      <sub>🚑 Emergency Vehicle Routing</sub>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="https://ui-avatars.com/api/?name=Vaishnavi+R+Honnagudi&background=4facfe&color=fff&size=100" width="100px;" alt=""/>
      <br />
      <sub><b>Vaishnavi R Honnagudi</b></sub>
      <br />
      <sub>Roll No: 227</sub>
      <br />
      <sub>USN: 01FE23BCS125</sub>
      <br />
      <sub>🚌 Public Transport Management</sub>
    </td>
    <td align="center">
      <img src="https://ui-avatars.com/api/?name=Vishal&background=43e97b&color=fff&size=100" width="100px;" alt=""/>
      <br />
      <sub><b>Vishal</b></sub>
      <br />
      <sub>Roll No: 248</sub>
      <br />
      <sub>USN: 01FE23BCS294</sub>
      <br />
      <sub>🗺️ Tourism Recommendation System</sub>
    </td>
  </tr>
</table>

---

## 📊 Topics Covered

### Linear Data Structures
- Arrays (1D & 2D)
- Singly Linked List
- Circular Singly Linked List
- Doubly Linked List
- Circular Doubly Linked List

### Non-Linear Data Structures
- Binary Trees
- Binary Search Trees
- Graphs
- Heaps (Min/Max Heap)
- Tries
- Hash Maps

### Algorithm Categories
- **Sorting**: Quick Sort, Merge Sort, Heap Sort
- **Searching**: Binary Search, Trie-based Search
- **Graph Algorithms**: Dijkstra's, BFS, DFS
- **String Matching**: Pattern matching algorithms
- **Backtracking**: Constraint satisfaction problems

---

## 🎨 Design Highlights

- **Modern UI/UX**: Clean, professional interface
- **Responsive Design**: Works on all device sizes
- **Custom Animations**: Smooth transitions and effects
- **Gradient Themes**: Eye-catching color schemes
- **Card-based Layouts**: Easy-to-scan information architecture
- **Interactive Elements**: Hover effects and dynamic content

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📝 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- Course instructors for guidance on algorithm implementations
- Online resources and documentation for best practices
- Team members for collaborative effort and dedication

---

## 📞 Contact

**Project Repository**: [https://github.com/VISHAL-Nk/portfolio-daa](https://github.com/VISHAL-Nk/portfolio-daa)

**Maintainer**: Vishal (USN: 01FE23BCS294)

---
