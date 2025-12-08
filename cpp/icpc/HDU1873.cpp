#include<bits/stdc++.h>
using namespace std;

using namespace std;

struct node
{
    int id;
    int val;

    friend bool operator<(node a,node b)
    {
        if(a.val != b.val) return a.val < b.val;
        else return a.id < b.id;
    }
};

int n;

int main()
{
    int i,j;
    char s[100];
    int num,set;
    while(~scanf("%d",&n))
    {
        num = 1;
        node temp;
        priority_queue<node> q[5];

        for(i = 1; i<=n; i++)
        {
            scanf("%s",s);
            if(s[0] == 'I')
            {
                scanf("%d %d", &set,&temp.val);
                temp.id = num++;
                q[set].push(temp);
            }
            else
            {
                scanf("%d",&set);
                if(q[set].empty()) {
                    printf("EMPTY\n");
                    continue;
                }

                node exm = q[set].top();
                q[set].pop();
                printf("%d\n",exm.id);
            }
        }
    }
}