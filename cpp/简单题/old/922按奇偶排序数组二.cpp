class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size();
        int even = 0;  // 指向下一个要放置偶数的位置
        int odd = 1;   // 指向下一个要放置奇数的位置
        
        while (even < n && odd < n) {
            // 找到第一个在偶数位置上的奇数
            while (even < n && nums[even] % 2 == 0) {
                even += 2;
            }
            // 找到第一个在奇数位置上的偶数
            while (odd < n && nums[odd] % 2 == 1) {
                odd += 2;
            }
            // 如果都还没越界，交换它们
            if (even < n && odd < n) {
                swap(nums[even], nums[odd]);
            }
        }
        
        return nums;
    }
};
/*
精妙，我还在想用双指针根据i是否为奇数偶数来判断遍历
这个算法直接省掉流程，要是位置上的对，就直接跳过，处理不对的就好，反正肯定有解法
*/