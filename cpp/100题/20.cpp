#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int m = n-k;
        int s = reduce(cardPoints.begin(), cardPoints.begin()+m);

        int min_s = s;
        for(int i=m; i<n; i++)
        {
            s += cardPoints[i] - cardPoints[i-m];
            min_s = min(min_s, s);
        }
        return reduce(cardPoints.begin(), cardPoints.end())-min_s;
    }
};