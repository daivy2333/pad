#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int rows = grid.size();
        int lies = grid[0].size();
        int res = 0;

        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<lies; j++)
            {
                if(grid[i][j] == 1)
                {
                    is_boarder = false;
                    area = 0;
                    dfs(grid, i, j);
                    if(!is_boarder)
                    {
                        res += area;
                    }
                }
                
            }
        }
        return res;
    }
private:
    void dfs(vector<vector<int>>& grid, int i, int j)
    {
        int rows = grid.size();
        int lies = grid[0].size();
        if(i<0||j<0||i>=rows||j>=lies)
        {
            is_boarder = true;
            return;
        }
        if(grid[i][j] != 1) return;
        grid[i][j] = 0;
        area++;
        int arr[][2] =
        {{0,1},{0,-1},{1,0},{-1,0}};
        for(auto dir: arr)
        {
            int new_x = i+dir[0];
            int new_y = j+dir[1];
            dfs(grid, new_x, new_y);
        }
    }
    bool is_boarder;
    int area;
};
// 你就说过没过吧