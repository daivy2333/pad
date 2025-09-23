#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> diStringMatch(string s) {
        int n = s.size();
        vector<int> perm(n + 1);
        int low = 0, high = n;
        
        for (int i = 0; i < n; i++) {
            if (s[i] == 'I') {
                perm[i] = low++;
            } else {
                perm[i] = high--;
            }
        }
        perm[n] = low;  // 此时low等于high
        
        return perm;
    }
};
