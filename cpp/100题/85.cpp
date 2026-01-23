#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        int rows = land.size();
        int lies = land[0].size();
        vector<int> res;
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<lies; j++)
            {
                if(land[i][j] == 0)
                {
                    res.push_back(dfs(land, i, j));
                }
            }
        }
        sort(res.begin(), res.end());
        return res;
    }

private:
    int dfs(vector<vector<int>>& land, int i, int j)
    {
        int rows = land.size();
        int lies = land[0].size();

        if(i<0||i>=rows||j<0||j>=lies) return 0;  // 先检查边界
        if(land[i][j] != 0) return 0;   
        land[i][j] = -1;
        int sh = dfs(land, i+1, j);
        int z_sh = dfs(land, i+1, j-1);
        int y_sh = dfs(land, i+1, j+1);

        int z = dfs(land, i,j-1);
        int y = dfs(land, i,j+1);

        int xi = dfs(land, i-1,j);
        int z_xi = dfs(land, i-1,j-1);
        int y_xi = dfs(land, i-1,j+1);

        return 1 + sh + z_sh + y_sh + z + y + z_xi + y_xi;
    }
};