#include <iostream>
#include <vector>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] == x) {
            return x;
        } else {
            return parent[x] = find(parent[x]);
        }
    }
    
    void union_(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int rows = grid.size();
        int cols = grid[0].size();
        int totalCells = rows * cols;
        DisjointSet ds(totalCells);
        
        int waterCount = 0;
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    int current = i * cols + j;
                    
                    if (i > 0 && grid[i - 1][j] == '1') {
                        ds.union_(current, current - cols);
                    }
                    
                    if (j > 0 && grid[i][j - 1] == '1') {
                        ds.union_(current, current - 1);
                    }
                } else {
                    waterCount++;
                }
            }
        }
        
        int islandCount = 0;
        for (int i = 0; i < totalCells; ++i) {
            if (grid[i / cols][i % cols] == '1' && ds.find(i) == i) {
                islandCount++;
            }
        }
        
        return islandCount;
    }
};

int main() {
    Solution solution;
    
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    
    cout << solution.numIslands(grid1) << endl; // Output: 1
    
    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    
    cout << solution.numIslands(grid2) << endl; // Output: 3
    
    return 0;
}
