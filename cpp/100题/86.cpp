#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int rows = grid.size();
        int lies= grid[0].size();
        int res = 0;
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<lies; j++)
            {
                if(grid[i][j]==0) continue;
                else
                {
                    res += 4-check(grid, i, j);
                }
            }
        }
        return res;
    }
private:
    int check(vector<vector<int>>& grid, int i, int j)
    {
        int count = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        
        // 只检查上下左右4个方向
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        for(int k = 0; k < 4; k++) {
            int new_x = i + dx[k];
            int new_y = j + dy[k];
            
            if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && grid[new_x][new_y] == 1) {
                count++;
            }
        }
        return count;
    }
};