class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        int n = name.size(), m = typed.size();
        
        while (i < n && j < m) {
            if (name[i] == typed[j]) {
                i++;
                j++;
            } else if (j > 0 && typed[j] == typed[j - 1]) {
                j++;
            } else {
                return false;
            }
        }
        
        // 检查 name 是否已经遍历完毕
        if (i != n) {
            return false;
        }
        
        // 检查 typed 中剩余的字符是否都是 name 的最后一个字符的长按
        while (j < m) {
            if (typed[j] != name[n - 1]) {
                return false;
            }
            j++;
        }
        
        return true;
    }
};
