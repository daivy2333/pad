#include<bits/stdc++.h>
using namespace std;

const int maxn = 1050;
int s[maxn+1];

void init_set()
{
    for(int i = 0; i <= maxn; i++)
    {
        s[i] = i;
    }
}

int find_set(int x)
{
    return x == s[x] ? x : find_set(s[x]);
}

void union_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);
    if(x != y) s[x] = s[y];
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