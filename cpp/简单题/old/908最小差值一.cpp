class Solution {
public:
    int smallestRangeI(vector<int>& nums, int k) {
        if (nums.size() == 1) return 0;
        
        int min_num = nums[0];
        int max_num = nums[0];
        
        // 找出数组中的最小值和最大值
        for (int num : nums) {
            min_num = min(min_num, num);
            max_num = max(max_num, num);
        }
        
        // 计算可能的最小差值
        int diff = max_num - min_num - 2 * k;
        
        // 如果差值小于等于0，说明可以调整到同一个值
        return max(0, diff);
    }
};
/*
最后一句max才是精髓，大多数情况只要考虑临界情况就好
*/