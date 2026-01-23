#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int rows = grid.size();
        int lies = grid[0].size();
        int res = 0;
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<lies; j++)
            {
                if(grid[i][j] != 0)
                {
                    if(bfs(grid, i, j)%k == 0)
                    {
                        res++;
                    }
                }
            }
        }
        return res;
    }

private:
    long long bfs(vector<vector<int>>& grid, int i, int j)
    {
        int rows = grid.size();
        int lies = grid[0].size();

        if((i<0||i>=rows||j<0||j>=lies) || grid[i][j] == 0) return 0;
        long long mid = grid[i][j];
        grid[i][j] = 0;
        long long shang = bfs(grid,i+1, j);
        long long xia = bfs(grid,i-1, j);
        long long zuo = bfs(grid, i, j-1);
        long long you = bfs(grid, i, j+1);
        return (mid+ shang+ xia+ zuo+ you);
    }
};