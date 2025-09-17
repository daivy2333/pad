#include <iostream>
#include <vector> // 添加头文件，vector需要
using namespace std;

class Solution {
private:
    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size(); // 行数
        int n = matrix[0].size(); // 列数

        // 检查是否为方阵，非方阵无法原地转置
        if (m != n) {
            cerr << "Error: Matrix is not square! Cannot transpose in-place." << endl;
            return {}; // 返回空矩阵
        }

        // 只处理方阵的原地转置
        for (int i = 0; i < m; i++) {
            for (int j = i; j < n; j++) { // j从i开始，避免重复交换
                // 修复：使用 matrix[i][j] 和 matrix[j][i]
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        return matrix;
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
