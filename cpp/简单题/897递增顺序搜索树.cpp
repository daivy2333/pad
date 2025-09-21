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
private:
    vector<int> vals;
    // 中序遍历，将节点值存入数组
    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        vals.push_back(node->val);
        inorder(node->right);
    }
public:
    TreeNode* increasingBST(TreeNode* root) {
        inorder(root);  // 中序遍历获取有序值
        
        // 创建新树的根节点
        TreeNode* newRoot = new TreeNode(vals[0]);
        TreeNode* curr = newRoot;
        
        // 根据数组构建只有右子节点的树
        for (int i = 1; i < vals.size(); i++) {
            curr->right = new TreeNode(vals[i]);
            curr = curr->right;
        }
        
        return newRoot;
    }
};
