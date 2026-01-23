#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int lies = grid[0].size();
        int res = 0;
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<lies; j++)
            {
                if(grid[i][j] == 1)
                {
                    res = max(res, bfs(grid, i, j));
                }
            }
        }
        return res;
    }

private:
    int bfs(vector<vector<int>>& grid, int i, int j)
    {
        int rows = grid.size();
        int lies = grid[0].size();

        if((i<0||i>=rows||j<0||j>=lies) || grid[i][j] != 1) return 0;
        grid[i][j] = 2;
        int shang = bfs(grid,i+1, j);
        int xia = bfs(grid,i-1, j);
        int zuo = bfs(grid, i, j-1);
        int you = bfs(grid, i, j+1);
        return 1+ shang+ xia+ zuo+ you;
    }
};