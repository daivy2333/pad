/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        int sum = 0;
        dfs(root, low, high, sum);
        return sum;
    }

private:
    void dfs(TreeNode* root, int low, int high, int& sum) {
        if (root == nullptr) {
            return;
        }

        // 利用二叉搜索树的特性进行剪枝
        if (root->val > low) {
            dfs(root->left, low, high, sum);
        }
        
        // 如果当前节点值在范围内，则加入总和
        if (root->val >= low && root->val <= high) {
            sum += root->val;
        }
        
        if (root->val < high) {
            dfs(root->right, low, high, sum);
        }
    }
};
/*
受教了
*/