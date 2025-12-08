#include<bits/stdc++.h>
using namespace std;

const int Len = 362880;

struct node
{
    int state[9];
    int dis;
};

int dir[4][4] = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0}
};

int visited[Len] = {0};
int start[9];
int goal[9];

long int factory[] = {1,1,2,6,24,120,720,5040,40320,362880};

bool Cantor(int str[], int n)
{
    long result = 0;
    for(int i = 0; i < n; i++)
    {
        int counted = 0;
        for(int j = i + 1; j < n; j++)
        {
            if(str[i] > str[j])
            {
                counted++;
            }
        }
        result += counted * factory[n - i - 1];
    }
    if(!visited[result])
    {
        visited[result] = 1;
        return true;
    }
    return false;
}

int bfs()
{
    node head;
    memcpy(head.state, start, sizeof(head.state));
    head.dis = 0;

    queue<node> q;
    Cantor(head.state, 9);

    q.push(head);

    while(!q.empty())
    {
        head = q.front();
        if(memcmp(head.state,goal,sizeof(goal)) == 0)
        {
            return head.dis;
        }

        q.pop();
        int z;
        for(z = 0; z < 9; z++)
        {
            if(head.state[z] == 0)
            {
                break;
            }
        }

        int x = z % 3;
        int y = z / 3;

        for(int i = 0;i < 4; i++)
        {
            int newx = x +dir[i][0];
            int newy = y +dir[i][1];

            int nz = newx + 3 * newy;
            if(newx >= 0 && newx < 3 && newy >= 0 && newy < 3 )
            {
                node newnode;
                memcpy(&newnode,&head,sizeof(head));
                swap(newnode.state[z],newnode.state[nz]);
                newnode.dis = head.dis + 1;
                if(Cantor(newnode.state,9))
                {
                    q.push(newnode);
                }
            }
        }
    }
    return -1;
}


int main()
{
    for(int i = 0; i < 9; i++)
    {
        cin>>start[i];
    }
    for(int i = 0; i < 9; i++)
    {
        cin>>goal[i];
    }

    int num = bfs();

    if(num != -1) cout<<num<<endl;
    else cout<<"No Solution!"<<endl;

    return 0;
}

/*



康托展开的核心思想是：对于一个排列，计算它在所有排列中的"排名"（从0开始）。

计算步骤：
1. 初始化 result = 0
2. 从左到右依次处理每个元素
3. 对于每个元素，计算它后面比它小的元素个数
4. 用这个个数乘以对应位置的阶乘，加到 result 中

具体计算过程：

数组：[3,1,2,4]
n = 4

第1步：处理第1个元素 3
- 3后面比3小的元素有：1, 2（共2个）
- counted = 2
- 位置权重：(4-1-1)! = 3! = 6
- 贡献值：2 × 6 = 12
- result = 0 + 12 = 12

第2步：处理第2个元素 1
- 1后面比1小的元素：无（0个）
- counted = 0
- 位置权重：(4-2-1)! = 2! = 2
- 贡献值：0 × 2 = 0
- result = 12 + 0 = 12

第3步：处理第3个元素 2
- 2后面比2小的元素：无（0个）
- counted = 0
- 位置权重：(4-3-1)! = 1! = 1
- 贡献值：0 × 1 = 0
- result = 12 + 0 = 12

第4步：处理第4个元素 4
- 4后面比4小的元素：无（0个）
- counted = 0
- 位置权重：(4-4-1)! = 0! = 1
- 贡献值：0 × 1 = 0
- result = 12 + 0 = 12

最终结果：[3,1,2,4] 的康托展开值是 12

验证：
让我们列出所有4个数的排列，看看 [3,1,2,4] 的位置：
1. [1,2,3,4] -> 0
2. [1,2,4,3] -> 1
3. [1,3,2,4] -> 2
4. [1,3,4,2] -> 3
5. [1,4,2,3] -> 4
6. [1,4,3,2] -> 5
7. [2,1,3,4] -> 6
8. [2,1,4,3] -> 7
9. [2,3,1,4] -> 8
10. [2,3,4,1] -> 9
11. [2,4,1,3] -> 10
12. [2,4,3,1] -> 11
13. [3,1,2,4] -> 12 ✓

计算结果正确！[3,1,2,4] 确实是第13个排列（从0开始计数为12）。

这个算法的重要性在于：
1. 可以将任意排列映射到唯一的一个整数
2. 这个整数范围是 [0, n!-1]
3. 可以用于状态压缩和去重
4. 在搜索算法中特别有用，比如八数码问题

使用预计算的阶乘表 factory[] 可以让计算更高效，因为不需要每次都重新计算阶乘。

*/