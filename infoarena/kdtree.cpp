/**
 * @author Miguel Mini
 * @tag greedy, dfs
 * @idea
 *      - if a subtree has diameter = k
 *      we can erase it.
 *
 *      - select maximum number of subtrees
 *      with depth less than k.
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
vector<int> g[maxn];
int dp[maxn];
int n, k;

int dfs(int x, int p=0) {
    vector<int> t;
    int ans = 0;
    for (int v : g[x]) {
        if (v == p) continue;
        ans += dfs(v, x);
        if (dp[v] == k) ans += 1;
        else t.push_back(dp[v] + 1);
    }
    sort(t.begin(), t.end());
    int len = t.size();
    while (t.size() > 1 && t[len-2] + t[len-1] > k) len--;
    ans += t.size() - len;
    t.resize(len);
    dp[x] = t.empty() ? 0 : t.back();
    return ans;
}

int main() {
    freopen("kdtree.in", "r", stdin);
    freopen("kdtree.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    cout << dfs(1) << endl;
    return 0;
}

