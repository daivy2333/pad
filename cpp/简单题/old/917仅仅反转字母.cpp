class Solution {
public:
    string reverseOnlyLetters(string s) {
        int left = 0;
        int right = s.size() - 1;
        
        while (left < right) {
            // 如果left指向的不是字母，右移left
            if (!isalpha(s[left])) {
                left++;
                continue;
            }
            // 如果right指向的不是字母，左移right
            if (!isalpha(s[right])) {
                right--;
                continue;
            }
            // 两个指针都指向字母，交换位置
            swap(s[left], s[right]);
            left++;
            right--;
        }
        
        return s;
    }
};
