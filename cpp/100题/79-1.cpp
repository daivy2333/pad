#include<bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> res;
        // 使用 pair 存储节点值和对应的索引
        stack<pair<int, int>> st; 
        int index = 0;
        ListNode* curr = head;
        
        // 先遍历一遍链表，将所有值存入 res，并初始化为 0
        while (curr) {
            res.push_back(0);
            curr = curr->next;
        }
        
        curr = head;
        // 再次遍历链表
        while (curr) {
            // 当栈不为空，且当前节点值大于栈顶元素的值
            while (!st.empty() && curr->val > st.top().first) {
                // 弹出栈顶元素，并更新其在 res 中的结果
                res[st.top().second] = curr->val;
                st.pop();
            }
            // 将当前节点的值和索引压入栈中
            st.push({curr->val, index});
            curr = curr->next;
            index++;
        }
        
        return res;
    }
};
