class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        if (strs.empty()) return 0;
        
        int n = strs.size();        // 字符串数量（行数）
        int m = strs[0].size();     // 字符串长度（列数）
        int count = 0;              // 需要删除的列数
        
        // 遍历每一列
        for (int j = 0; j < m; j++) {
            // 检查当前列是否是非严格递增的
            for (int i = 1; i < n; i++) {
                if (strs[i][j] < strs[i-1][j]) {
                    count++;
                    break;
                }
            }
        }
        
        return count;
    }
};
