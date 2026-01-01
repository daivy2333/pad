#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int cnt[2]{};
        int road=0, result=0, left=0;
        int len = answerKey.size();
        for(int right=0; right<len; right++)
        {
            int in = answerKey[right]=='T'? 0:1;
            road++;
            cnt[in]++;

            while (cnt[0]>k && cnt[1]>k)
            {
                road--;
                int out = answerKey[left]=='T'? 0:1;
                cnt[out]--;
                left++;
            }
            result = max(result, road);
        }
        return result;
    }
};