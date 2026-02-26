class Solution {
public:
    int bitwiseComplement(int n) {
        if(!n) return 1;
        int mask = ~0;
        while(mask & n)
        {
            mask <<= 1;
        }
        return ~mask & ~n;
    }
};