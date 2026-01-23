#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        if (land.empty() || land[0].empty()) return {};
        
        int rows = land.size();
        int cols = land[0].size();
        vector<int> res;
        
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(land[i][j] == 0)
                {
                    res.push_back(dfs(land, i, j, rows, cols));
                }
            }
        }
        sort(res.begin(), res.end());
        return res;
    }

private:
    int dfs(vector<vector<int>>& land, int i, int j, int rows, int cols)
    {
        if(i < 0 || i >= rows || j < 0 || j >= cols || land[i][j] != 0) return 0;
        
        land[i][j] = -1;
        int count = 1;
        
        // 8个方向
        for(int dx = -1; dx <= 1; dx++)
        {
            for(int dy = -1; dy <= 1; dy++)
            {
                if(dx == 0 && dy == 0) continue;
                count += dfs(land, i + dx, j + dy, rows, cols);
            }
        }
        
        return count;
    }
};
