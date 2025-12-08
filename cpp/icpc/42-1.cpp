#include<bits/stdc++.h>
using namespace std;

void print_subset(int n){
    for(int i = 0; i < (1<<n); i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i & (1<<j))
                cout << j << " ";
        }
        cout<<endl;
    }
}

int mian(){
    int n;
    cin >> n;
    print_subset(n);
}