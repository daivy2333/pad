#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const int FACT[10] = {1,1,2,6,24,120,720,5040,40320,362880};

// 康托展开：将 state 编码为 [0, 9!-1] 的整数
int cantor(int state[N][N]) {
    int a[9];
    for (int i = 0; i < 9; ++i) {
        a[i] = state[i/3][i%3];  // 行优先展开
    }
    int code = 0;
    for (int i = 0; i < 9; ++i) {
        int less = 0;
        for (int j = i+1; j < 9; ++j) {
            if (a[j] < a[i]) less++;
        }
        code += less * FACT[8 - i];
    }
    return code;
}

struct Node {
    int state[N][N];
    int x, y; // 空格 0 的位置，避免每次搜索
    int step;
};

int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int bfs(int start[N][N], int goal[N][N]) {
    unordered_map<int, int> dist1, dist2; // state_code -> steps
    queue<Node> q1, q2;

    // 初始化 start
    Node s, g;
    memcpy(s.state, start, sizeof(s.state));
    memcpy(g.state, goal, sizeof(g.state));
    // 找 0 的位置
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s.state[i][j] == 0) { s.x = i; s.y = j; }
            if (g.state[i][j] == 0) { g.x = i; g.y = j; }
        }
    }
    s.step = 0; g.step = 0;

    int code_s = cantor(s.state);
    int code_g = cantor(g.state);
    dist1[code_s] = 0;
    dist2[code_g] = 0;
    q1.push(s);
    q2.push(g);

    // 如果起点 == 终点
    if (code_s == code_g) return 0;

    // 双向 BFS：每次扩展一层（当前队列所有节点）
    while (!q1.empty() && !q2.empty()) {
        // 优先扩展小的队列（可选优化）
        if (q1.size() > q2.size()) {
            swap(q1, q2);
            swap(dist1, dist2);
        }

        int size = q1.size();
        while (size--) {
            Node cur = q1.front(); q1.pop();
            int cur_code = cantor(cur.state);

            for (int d = 0; d < 4; ++d) {
                int nx = cur.x + dir[d][0];
                int ny = cur.y + dir[d][1];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

                Node nxt = cur;
                swap(nxt.state[cur.x][cur.y], nxt.state[nx][ny]);
                nxt.x = nx; nxt.y = ny;
                nxt.step = cur.step + 1;

                int nxt_code = cantor(nxt.state);

                // 检查是否在反向搜索中已访问
                if (dist2.count(nxt_code)) {
                    return nxt.step + dist2[nxt_code];
                }

                // 若未在正向访问过，则加入
                if (!dist1.count(nxt_code)) {
                    dist1[nxt_code] = nxt.step;
                    q1.push(nxt);
                }
            }
        }
    }
    return -1; // 无解
}

int main() {
    int start[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
    int goal[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,0,8}
    };
    cout << bfs(start, goal) << endl; // 应输出 1
}