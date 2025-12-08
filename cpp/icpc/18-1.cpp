#include<bits/stdc++.h>

using namespace std;

int main(){
    int i,k,n = 1e8;
    clock_t start,end;
    start = clock();
    for(i = 1; i <= n; i++){
        k++;
    }
    end = clock();

    cout << "time: " << (double)(end-start)/CLOCKS_PER_SEC<<endl;
}