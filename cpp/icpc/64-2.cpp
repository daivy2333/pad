#include<bits/stdc++.h>
using namespace std;

const int maxn = 1050;
int s[maxn+1];

int height[maxn+1];
void init_set()
{
    for(int i=1; i<=maxn; i++)
    {
        s[i] = i;
        height[i] = 0;
    }
}

int find_set(int x)
{
    int r = x;
    while(s[r]!=r) r = s[r];
    int i = x, j;
    while(i!=r)
    {
        j = s[i];
        s[i] = r;
        i = j;
    }
}

void union_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);
    if(height[x]==height[y])
    {
        height[x] = height[x]+1;
        s[y] = x;
    }
    else
    {
        if(height[x]<height[y]) s[x] = y;
        else s[y] = x;
    }
}

int main()
{
    int t, n, m, x, y;
    cin >> t;
    while(t--)
    {
        cin>>n>>m;
        init_set();
        for(int i = 1; i <= m; i++)
        {
            cin>>x>>y;
            union_set(x, y);
        }
        int ans = 0;
        for(int i=1; i<=n; i++)
        {
            if(s[i]==i) ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}