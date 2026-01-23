#include <iostream>
#include <vector> // 添加头文件，vector需要
using namespace std;

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size();    // 原矩阵的行数
        int n = matrix[0].size(); // 原矩阵的列数
        
        // 创建一个新的 n × m 的矩阵
        vector<vector<int>> result(n, vector<int>(m));
        
        // 填充转置矩阵
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[j][i] = matrix[i][j];
            }
        }
        
        return result;
    }
};


// 辅助函数：打印矩阵
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    Solution s;
    // 正确初始化矩阵
    vector<vector<int>> matrix = {{1,2,3}, {4,5,6}, {7,8,9}};

    // 转置矩阵（原地修改）
    vector<vector<int>> result = s.transpose(matrix);

    // 打印结果
    cout << "Transposed Matrix:" << endl;
    printMatrix(result);

    return 0;
}
