#include<bits/stdc++.h>
using namespace std;

int main(){
    map<string,int> shop;
    int n,m,p;
    while(cin>>n)
    {
        string s;
        for(int i=1; i<=n; i++)
        {
            cin>>s;
        }

        cin>>m;
        while(m--)
        {
            for(int i=1; i<=n; i++)
            {
                cin>>p>>s;
                shop[s]+=p;
            }
            int rank = 1;
            map<string,int>::iterator it;
            for(it = shop.begin(); it!=shop.end(); it++)
            {
                if(it->second> shop["memory"])
                rank++;
            }
            cout<<rank<<endl;
        }
        shop.clear();
    }
    return 0;
}