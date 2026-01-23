class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            // 找到左边第一个奇数
            while (left < right && nums[left] % 2 == 0) {
                left++;
            }
            // 找到右边第一个偶数
            while (left < right && nums[right] % 2 == 1) {
                right--;
            }
            // 交换奇数和偶数的位置
            if (left < right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        return nums;
    }
};
/*
我还想着能不能用数组的操作去做这个，结果还是要双指针么，算了经典的就是好用
*/