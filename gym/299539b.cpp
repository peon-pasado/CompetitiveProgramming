#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 10;
int n, C;
int w[maxn], v[maxn];
bool vis[maxn][maxn];
int memo[maxn][maxn];

int bt(int pos, int C) {
    if (C < 0) return -2.1e9;
    if (pos == n) return 0; 
    if (vis[pos][C]) return memo[pos][C];
    vis[pos][C] = 1;
    int ans = bt(pos+1, C), sum = 0;
    for (int m = v[pos], t = 1; m > 0; m /= 2, t++) {
        sum += m;
        ans = max(ans, bt(pos+1, C - w[pos] * t) + sum);
    }
    return memo[pos][C] = ans;
}

int main() {
    cin >> n >> C;
    for (int i = 0; i < n; ++i) cin >> w[i];
    for (int i = 0; i < n; ++i) cin >> v[i];
    cout << bt(0, C) << endl;
    return 0;
}