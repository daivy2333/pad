class Solution {
public:
    int minBitFlips(int start, int goal) {
        int key = start^goal;
        int res = 0;
        while(key)
        {
            res += key&1;
            key >>= 1;
        }
        return res;
    }
};