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
    vector<int> nextLargerNodes(ListNode *head) {
        vector<int> res;
        ListNode *slow = head;
        while(slow)
        {
            ListNode *fast = slow->next;
            int ans = 0;
            while(fast)
            {
                if(fast->val > slow->val) 
                {
                    ans = fast->val;
                    break;
                }
                fast = fast->next;
            }
            res.push_back(ans);
            slow = slow->next;
        }
        return res;
    }
};