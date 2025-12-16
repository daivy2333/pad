#include<bits/stdc++.h>
using namespace std;

using ll = long long;

ll gcd(ll a, ll b)
{
    while(b)
    {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

pair<ll, ll> add_frac(ll a, ll b, ll c, ll d)
{
    ll num = a * d + b * c;
    ll den = b * d;
    ll g = gcd(abs(num), abs(den));
    return {num / g, den / g};
}

pair<ll, ll> sub_frac(ll a, ll b, ll c, ll d)
{
    ll num = a * d + b * c;
    ll den = b * d;
    if(num < 0) return {-1, -1};
    ll g = gcd(num, den);
    return {num / g, den / g};
}

bool dfs(ll num, ll den, int depth, int max_depth, ll last_den, vector<ll>& path)
{
    if(depth == max_depth)
    {
        if(num == 1)
        {
            path.push_back(den);
            return true;
        }
        return false;
    }

    int rest = max_depth - depth;

    ll min_den = max(last_den+1, (den+num-1)/num);
    ll max_den = (rest*den) / num;
    if(min_den > max_den) return false;

    for(ll x = min_den; x <= max_den; x++)
    {
        auto [new_num,new_den] = sub_frac(num, den, 1, x);
        if(new_num == -1) continue;

        path.push_back(x);

        if(dfs(new_num, new_den, depth+1, max_depth, x, path))
        {
            return true;
        }
        path.pop_back();
    }
    return false;
}

vector<ll> egyptian_fraction(ll num, ll den) {
    // 先约分
    ll g = gcd(num, den);
    num /= g;
    den /= g;

    if (num == 0) return {};
    if (num == 1) return {den};

    // 如果是假分数？题目一般要求真分数，但可处理：
    vector<ll> res;
    while (num > den) {
        res.push_back(1); // 1/1
        num -= den;
        g = gcd(num, den);
        num /= g;
        den /= g;
    }
    if (num == 0) return res;
    if (num == 1) {
        res.push_back(den);
        return res;
    }

    // 现在确保 0 < num < den
    vector<ll> path;
    for (int max_depth = 1; max_depth <= 10; ++max_depth) { // 一般 ≤6 就够，防死循环
        path.clear();
        if (dfs(num, den, 0, max_depth, 0, path)) {
            res.insert(res.end(), path.begin(), path.end());
            return res;
        }
    }
    return {}; // 无解（理论上总有解，但深度可能过大）
}

// 辅助：打印结果
void print_result(ll num, ll den, const vector<ll>& ef) {
    cout << num << "/" << den << " = ";
    for (int i = 0; i < ef.size(); ++i) {
        if (i > 0) cout << " + ";
        cout << "1/" << ef[i];
    }
    cout << endl;
}

int main() {
    // 示例测试
    vector<pair<ll, ll>> tests = {
        {4, 13},
        {5, 121},
        {6, 14},  // = 3/7
        {2, 3},
        {7, 15}
    };

    for (auto [num, den] : tests) {
        auto ef = egyptian_fraction(num, den);
        if (ef.empty()) {
            cout << num << "/" << den << " → no solution found (within depth limit)\n";
        } else {
            print_result(num, den, ef);
        }
    }

    // 交互式输入（可选）
    /*
    ll a, b;
    cout << "Enter numerator and denominator: ";
    while (cin >> a >> b) {
        if (a <= 0 || b <= 0) break;
        auto ef = egyptian_fraction(a, b);
        print_result(a, b, ef);
        cout << "Next: ";
    }
    */

    return 0;
}