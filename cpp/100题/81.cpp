#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
    void bfs(vector<vector<char>>& grid, int rows, int cols, int x, int y)
    {
        if(x < 0 || x >= rows || y < 0 || y >= cols || grid[x][y] != '1') 
            return;

        grid[x][y] = '2';
        bfs(grid, rows, cols, x+1, y);
        bfs(grid, rows, cols, x-1, y);
        bfs(grid, rows, cols, x, y+1);
        bfs(grid, rows, cols, x, y-1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        
        int rows = grid.size();
        int cols = grid[0].size();
        int res = 0;
        
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(grid[i][j] == '1')
                {
                    bfs(grid, rows, cols, i, j);
                    res++;
                }
            }
        }
        return res;
    }
};
// 递归，很神奇吧