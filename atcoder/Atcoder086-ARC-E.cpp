/**
 * @author Miguel Mini
 * @tag dp, probabilities, dsu
 * @idea
 *      - we can use probability
 *      for every depth.
 * 
 *      - can combine two 
 *      subtrees and calculating
 *      numbers of subsets with
 *      1 and 0 elements.
 *  
 *      - can use dsu depth-merge
 *      to obtain O(n) solution.
 * 
 * @complexity O(n)
 */ 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;
using pii = pair<int, int>;
using ll = long long;
vector<int> g[maxn];
vector<pii> var[maxn];

int mul(ll a, ll b) {
    return a*b%mod;
}

int add(int a, int b) {
    return (a+b)%mod;
}

void init(int x, int v) {
    if (~v) swap(var[x], var[v]);
    var[x].push_back({inv2, inv2});
}

pii combine(pii a, pii b) {
    return {add(mul(a.first, b.second), mul(a.second, b.first)),
            mul(a.second, b.second)};
}

int ni[maxn];
void merge(int u, int v) {
    const int n = var[u].size(), m = var[v].size();
    for (int i = 0; i < m; ++i) {
        var[u][n-2-i] = combine(var[u][n-2-i], var[v][m-1-i]);
    }
}

int len[maxn];
void dsu(int x) {
    len[x] = 1;
    for (int& v : g[x]) {
        dsu(v);
        if (len[x] < len[v] + 1) {
            len[x] = len[v] + 1;
            swap(g[x][0], v);
        }
    }
    if (!g[x].empty()) {
        init(x, g[x][0]);
        int m = 0;
        for (int i = 1; i < g[x].size(); ++i) { 
            merge(x, g[x][i]);
            m = max(m, len[g[x][i]]);
        }
        for (int i = 0; i < m; ++i) {
            auto& q = var[x][len[x]-2-i];
            q.second = add(mod, 1-q.first);
        }
    } else init(x, -1);
}


int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int pi;
        cin >> pi;
        g[pi].push_back(i);
    }
    int pot = 1;
    for (int i = 0; i <= n; ++i) {
        pot = add(pot, pot);
    }
    dsu(0);
    int ans = 0;
    for (auto e : var[0]) {
        ans = add(ans, e.first);
    }
    ans = mul(ans, pot);
    cout << ans << endl;
    return 0;
}