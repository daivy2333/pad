#include<bits/stdc++.h>
using namespace std;
int ko[1000001];
#define swap(a,b) {int temp = a;a = b;b = temp;}
int n,m;
void bubble_sort()
{
    for(int i =1; i<= n-1; i++){
        for(int j = 1; j<=n-1; j++){
            if(ko[j] > ko[j+1]){
                swap(ko[j],ko[j+1]);
            }
        }
    }
}
int main(){
    while(scanf("%d %d",&n,&m)){
        for(int i =1; i<=n ; i++){
        scanf("%d", &ko[i]);
        }
        bubble_sort();
        for(int i = n; i >= n-m+1; i--)
        {
            if(i == n-m+1) printf("%d\n", ko[i]);
            else printf("%d ",ko[i]);
        }
    }
    return 0;
}