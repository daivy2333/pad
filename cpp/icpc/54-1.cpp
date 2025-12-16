#include<bits/stdc++.h>
using namespace std;


char room[23][23];
int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int Wx,Hy,num;
#define CHECK(x,y)(x<Wx && x>=0 && y>=0 && y<Hy)

struct node {int x,y;};

void dfs(int dx, int dy)
{
    room[dx][dy] = '#';

    num++;
    for(int i = 0; i < 4; i++)
    {
        int newx = dx + dir[i][0];
        int newy = dy + dir[0][i];
        if(CHECK(newx,newy) && room[newx][newy] == '.')
        {
            dfs(newx,newy);
        }
    }
}