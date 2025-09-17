#include <string>
#include <iostream>
using namespace std;

// 假设 TreeNode 结构已定义：
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    void midorder(TreeNode* root, string& res) {
        if (root == nullptr) {
            return; // 递归终止条件
        }
        
        // 中序遍历：左 -> 根 -> 右
        midorder(root->left, res);
        
        // 如果是叶子节点（左右都为空），则记录值
        if (root->left == nullptr && root->right == nullptr) {
            res += to_string(root->val) + " "; // 用空格分隔，避免数字粘连
        }
        
        midorder(root->right, res);
    }

public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        string leaves1, leaves2;
        midorder(root1, leaves1); // 获取 root1 的叶子序列
        midorder(root2, leaves2); // 获取 root2 的叶子序列
        return leaves1 == leaves2; // 比较是否相同
    }
};
int main() {
    Solution s;

    // 构造测试用例
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(5);
    root1->right = new TreeNode(1);
    root1->left->left = new TreeNode(6);
    root1->left->right = new TreeNode(2);
    root1->right->left = new TreeNode(9);
    root1->right->right = new TreeNode(8);
    root1->left->right->left = new TreeNode(7);
    root1->left->right->right = new TreeNode(4);

    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(5);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(6);
    root2->left->right = new TreeNode(7);
    root2->right->left = new TreeNode(4);
    root2->right->right = new TreeNode(2);
    root2->right->right->left = new TreeNode(9);
    root2->right->right->right = new TreeNode(8);

    cout << boolalpha << s.leafSimilar(root1, root2) << endl; // 输出 true
    return 0;
}
