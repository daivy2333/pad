#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int left=0, right=plants.size()-1, note=0;
        int bo_a=capacityA, bo_b=capacityB;
        while(left<=right)
        {
            if(left==right)
            {
                if(bo_b>bo_a)
                {
                    if(plants[right]>bo_b) 
                    {
                        call(note);
                    }
                    right--;
                }
                else
                {
                    if(plants[left]>bo_a) 
                    {
                        call(note);
                    }
                    left++;
                }
            }
            else
            {
                if(plants[left]>bo_a) 
                {
                    bo_a = capacityA;
                    call(note);
                }

                if(plants[right]>bo_b) 
                {
                    bo_b = capacityB;
                    call(note);
                }
                bo_a -= plants[left++];
                bo_b -= plants[right--];
            }
            
        }
        return note;
    }
private:
    void call(int& note)
    {
        note++;
    }
};