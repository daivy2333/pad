#include<bits/stdc++.h>
using namespace std;
#define Swap(a,b){int c = a; a = b; b = c;}
int dat[] = {1,2,3,4,5,6,7,8,9,0};
int num = 0;
void Perm(int begin, int end)
{
    int i;
    if(begin == end)
    {
        num++;
        for(int i : dat)
        {
            cout<<i<< " ";
        }
    }
    else
    {
        for(i = begin; i <= end; i++)
        {
            Swap(dat[begin], dat[i]);
            Perm(begin+1,end);
            Swap(dat[begin], dat[i]);
        }
    }
}
int main(){
    clock_t start,end;
    start = clock();
    Perm(0,9);
    end = clock();
    cout<< (double)(end-start)/CLOCKS_PER_SEC<<endl;
    cout<<num<<endl;
    return 0;
}