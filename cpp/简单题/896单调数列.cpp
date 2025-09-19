class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        bool increasing = true;
        bool decreasing = true;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                decreasing = false; // 出现递增，则不可能是单调递减
            } else if (nums[i] < nums[i - 1]) {
                increasing = false; // 出现递减，则不可能是单调递增
            }
            // 如果 nums[i] == nums[i-1]，两个标志位都不需要改变
        }
        
        return increasing || decreasing;
    }
};
