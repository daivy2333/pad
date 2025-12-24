#include<bits/stdc++.h>
using namespace std;

const int N = 1010;

struct node {
    int value;
    node *l, *r;
    node(int value = 0, node* l = NULL, node* r = NULL) : value(value), l(l), r(r) {}
};

// 使用局部变量传递数组
node* buildtree(int* pre, int* in, int preL, int preR, int inL, int inR) {
    if (preL > preR) return NULL;
    
    node* root = new node(pre[preL]);  // 先序遍历第一个节点是根节点
    
    int k;
    for (k = inL; k <= inR; k++) {
        if (in[k] == pre[preL])  // 在中序遍历中找到根节点
            break;
    }
    
    int numLeft = k - inL;  // 左子树的节点数
    
    // 递归构建左子树
    root->l = buildtree(pre, in, preL + 1, preL + numLeft, inL, k - 1);
    // 递归构建右子树
    root->r = buildtree(pre, in, preL + numLeft + 1, preR, k + 1, inR);
    
    return root;
}

void postorder(node* root, vector<int>& result) {
    if (root == NULL) return;
    postorder(root->l, result);
    postorder(root->r, result);
    result.push_back(root->value);
}

void remove_tree(node* root) {
    if (root == NULL) return;
    remove_tree(root->l);
    remove_tree(root->r);
    delete root;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n > 0) {
        vector<int> pre(n), in(n);
        
        for (int i = 0; i < n; i++) scanf("%d", &pre[i]);
        for (int i = 0; i < n; i++) scanf("%d", &in[i]);
        
        node* root = buildtree(pre.data(), in.data(), 0, n - 1, 0, n - 1);
        
        vector<int> postResult;
        postorder(root, postResult);
        
        for (int i = 0; i < n; i++) {
            printf("%d", postResult[i]);
            if (i != n - 1) printf(" ");
        }
        printf("\n");
        
        remove_tree(root);
    }
    return 0;
}