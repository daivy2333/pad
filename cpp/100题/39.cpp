#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        for(int i=y; i<y+k; i++)
        {
            int up=x,donw=x+k-1;

            while(up<donw)
            {
                swap(grid[up++][i], grid[donw--][i]);
            }
        }
        return grid;
    }
};