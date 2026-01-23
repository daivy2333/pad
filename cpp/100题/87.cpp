#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int note = image[sr][sc];
        dfs(image, sr, sc, color, note);
        return image;
    }

private:
    void dfs(vector<vector<int>>& image, int sr, int sc, int color, int note)
    {
        int rows = image.size();
        int lies = image[0].size();
        if((sr<0||sc<0||sr>=rows||sc>=lies) || image[sr][sc] == color || image[sr][sc] != note) return;

        image[sr][sc] = color;
        // 只检查上下左右4个方向
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for(int k = 0; k<4; k++)
        {
            int new_x = sr+dx[k];
            int new_y = sc+dy[k];
            dfs(image, new_x, new_y, color, note);
        }
    }
};