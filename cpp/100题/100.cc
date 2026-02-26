#include"main.h"

class Solution {
public:
    bool hasAlternatingBits(int n) {

        long key = (n>>1)^n;
        return 0 == key&(key+1);
    }
};