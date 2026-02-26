class Solution {
public:
    int hammingDistance(int x, int y) {
        int key = x ^ y;
        int res = 0;
        while(key)
        {
            res += key&1;
            key >>= 1;
        }
        return res;
    }
};