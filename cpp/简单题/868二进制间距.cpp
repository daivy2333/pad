#include <iostream>
#include <vector>
#include <climits> // 包含 INT_MIN 的头文件
using namespace std;

class Solution {
public:
    int binaryGap(int n) {
        int distance = 0;
        int max_gap = 0;
        bool found_first_one = false;
        
        while (n != 0) {
            int last_bit = n & 1;
            if (last_bit == 1) {
                if (found_first_one) {
                    distance++;
                    if (distance > max_gap) {
                        max_gap = distance;
                    }
                    distance = 0; // 重置距离
                } else {
                    found_first_one = true;
                }
            }
            
            if (found_first_one && last_bit == 0) {
                distance++;
            }
            
            n >>= 1; // 修复：正确的右移语法
        }
        
        return max_gap;
    }
};

int main()
{
    Solution s;
    cout<<s.binaryGap(22);
    return 0;
}