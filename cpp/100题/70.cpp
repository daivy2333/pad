#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int res = 0;
        sort(arr2.begin(), arr2.end());
        for(auto i : arr2)
        {
            cout << i << " ";
        }
        cout << endl;
        for(auto i : arr1)
        {
            if(down(i, arr2, d))
            {
                res++;
            }
        }
        cout<< "res " <<res << endl;
        return res;
    }
private:
    bool down(int target, vector<int>& numbers, const int d)
    {
        int left = 0, right = numbers.size()-1;
        while(left<=right)
        {
            int mid = left + (right-left)/2;
            if(numbers[mid] == target) return false;
            else if(numbers[mid] < target) left = mid+1;
            else right = mid-1;
        }
        
        cout<<"target "<< target << " left " << numbers[left] << endl;

        bool check_left = left < numbers.size();
        bool check_right = right >= 0;
        if(check_left && check_right)
        {
            return (abs(numbers[left] - target) > d) && (abs(numbers[right] - target) > d);
        }
        else if(check_left)
        {
            return abs(numbers[left] - target) > d;
        }
        else
        {
            return abs(numbers[right] - target) > d;
        }
        return numbers[left]-target > d;
    }
};

int main()
{
    Solution s;
    vector<int> arr1 = {4,5,8};
    vector<int> arr2 = {10,9,1,8};
    int d = 2;
    cout<< s.findTheDistanceValue(arr1, arr2, d) << endl;
    return 0;
}