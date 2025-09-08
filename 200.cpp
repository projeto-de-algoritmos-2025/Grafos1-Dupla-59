#include <vector>
#include <stack>
#include <utility>  
#include <iostream>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        int islands = 0;

        vector<pair<int,int>> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == '1') {
                    islands++;
                    stack<pair<int,int>> st;
                    st.push({r, c});
                    
                    while (!st.empty()) {
                        auto [i, j] = st.top();
                        st.pop();
                        
                        if (grid[i][j] != '1') continue;
                        grid[i][j] = '0';
                        
                        for (auto [di, dj] : dirs) {
                            int ni = i + di;
                            int nj = j + dj;
                            if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == '1') {
                                st.push({ni, nj});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
};
