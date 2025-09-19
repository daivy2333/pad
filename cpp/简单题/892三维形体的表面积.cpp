#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int totalCubes = 0;
        int verticalOverlap = 0;
        int adjacentOverlap = 0;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    totalCubes += grid[i][j];
                    verticalOverlap += (grid[i][j] - 1) * 2;
                    
                    if (j < n - 1) {
                        adjacentOverlap += min(grid[i][j], grid[i][j + 1]) * 2;
                    }
                    if (i < n - 1) {
                        adjacentOverlap += min(grid[i][j], grid[i + 1][j]) * 2;
                    }
                }
            }
        }
        
        int totalSurface = totalCubes * 6 - verticalOverlap - adjacentOverlap;
        return totalSurface;
    }
};
/*
这道题倒是和平面求周长有点像
*/