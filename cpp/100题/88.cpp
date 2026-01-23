#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size();
        int n = grid[0].size();
        int originalColor = grid[row][col];
        
        // 如果颜色相同，直接返回
        if (originalColor == color) return grid;
        
        // 标记数组，记录已访问的格子
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        // 边界格子数组，记录哪些是边界
        vector<vector<bool>> isBorder(m, vector<bool>(n, false));
        
        // 先进行DFS，标记所有连通分量并找出边界
        dfs(grid, row, col, originalColor, visited, isBorder);
        
        // 给边界格子着色
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isBorder[i][j]) {
                    grid[i][j] = color;
                }
            }
        }
        
        return grid;
    }
    
private:
    void dfs(vector<vector<int>>& grid, int i, int j, int originalColor, 
             vector<vector<bool>>& visited, vector<vector<bool>>& isBorder) {
        int m = grid.size();
        int n = grid[0].size();
        
        // 边界检查
        if (i < 0 || i >= m || j < 0 || j >= n) return;
        // 颜色检查
        if (grid[i][j] != originalColor) return;
        // 访问检查
        if (visited[i][j]) return;
        
        visited[i][j] = true;
        
        // 检查是否是边界
        // 如果在网格的边界上，肯定是边界
        if (i == 0 || i == m-1 || j == 0 || j == n-1) {
            isBorder[i][j] = true;
        } else {
            // 检查四个方向的邻居
            vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
            for (auto& dir : directions) {
                int ni = i + dir.first;
                int nj = j + dir.second;
                
                // 如果邻居颜色不同，说明当前格子是边界
                if (grid[ni][nj] != originalColor) {
                    isBorder[i][j] = true;
                }
            }
        }
        
        // 递归访问邻居
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto& dir : directions) {
            int ni = i + dir.first;
            int nj = j + dir.second;
            dfs(grid, ni, nj, originalColor, visited, isBorder);
        }
    }
};
/*
没辙了，我的代码不对
class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int note = grid[row][col];
        
        dfs(grid, row, col, color, note);
        check(grid, row, col, color, note);

        return grid;
    }

private:
    void dfs(vector<vector<int>>& grid, int row, int col, int color,int note)
    {
        int rows = grid.size();
        int lies = grid[0].size();
        if((row<0||col<0||row>=rows||col>=lies) || grid[row][col] != note) return;

        grid[row][col] = color;
        int forward[][2] =
        {
            {0,1},
            {0,-1},
            {1,0},
            {-1,0}
        };
        for(auto i : forward)
        {
            int new_x = row+i[0];
            int new_y = col+i[1];
            dfs(grid, new_x, new_y, color, note);
        }
    }
    void check(vector<vector<int>>& grid, int row, int col, int color,int note)
    {
        int rows = grid.size();
        int lies = grid[0].size();
        if((row<0||col<0||row>=rows||col>=lies)) return;
        if(grid[row][col] != color) return;

        int forward[][2] =
        {
            {0,1},
            {0,-1},
            {1,0},
            {-1,0}
        };
        int key = 1;
        for(auto i: forward)
        {
            int new_x = row+i[0];
            int new_y = col+i[1];
            if(new_x<0||new_y<0||new_x>=rows||new_y>=lies || grid[new_x][new_y] != color)
            {
                key = 0;
                break;
            }
        }
        if(key)grid[row][col] = note;
        
        for(auto i : forward)
        {
            int new_x = row+i[0];
            int new_y = col+i[1];
            check(grid, new_x, new_y, color, note);
        }
    }
};

*/
