#include<bits/stdc++.h>
using namespace std;

void print_set(int n,int k)
{
    for(int i = 0; i < (1 << n); i++)
    {
        int num = 0, kk = i;
        while(kk)
        {
            kk = kk&(kk-1);
            num++;
        }
        if(num == k)
        {
            for(int j = 0; j < n; j++)
            {
                if(i&(1 << j))
                    cout << j+1 << " ";
            }
            cout << endl;
        }
    }
}
int main()
{
    int n, k;
    cin >> n >> k;
    print_set(n, k);
}