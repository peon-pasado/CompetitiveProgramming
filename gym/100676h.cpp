#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi num, st;
vector<vector<pii>> ed;
vector<int> w;
vector<long long> cst;

int Time;

int dfs(int at, int par)
{
    int me = num[at] = ++Time, e, y, top = me;
    trav(pa, ed[at]) if (pa.second != par)
    {
        tie(y, e) = pa;
        if (num[y])
        {
            top = min(top, num[y]);
            // if (num[y] < me)
            //	st.push_back(e);
        }
        else
        {
            // int si = sz(st);
            int up = dfs(y, e);
            top = min(top, up);
            if (up == me)
            {
                // st.push_back(e);
                // f(vi(st.begin() + si, st.end()));
                // st.resize(si);
            }
            else if (up < me)
            {
                // st.push_back(e);
            }
            else
            {
                /* e is a bridge */
                w[e] = 1;
            }
        }
    }
    return top;
}

void bicomps() {
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1);
}

vector<vector<pii>> T;
vi color;
vector<bool> vis;
void dfs_(int x, int c) {
    vis[x] = 1;
    color[x] = c;
    for (auto e : ed[x]) {
        if (vis[e.first]) continue;
        if (w[e.second]) continue;
        dfs_(e.first, c);
    }
}

vector<long long> dp[2];
void add_(int x, long long w) {
    if (dp[0][x] < w) {
        dp[1][x] = dp[0][x];
        dp[0][x] = w;
    } else {
        dp[1][x] = max(dp[1][x], w);
    }
}

void dfs_root(int x, int p) {
    dp[0][x] = 0;
    dp[1][x] = 0;
    for (auto e : T[x]) {
        if (e.first == p) continue;
        dfs_root(e.first, x);
        add_(x, cst[e.second] + dp[0][e.first]);
    }
}

void dfs_reroot(int x, int p, long long w=0) {
    if (p >= 0) {
        if (dp[0][p] == w + dp[0][x]) {
            if (dp[1][p] + w > dp[0][x]) {
                dp[1][x] = dp[0][x];
                dp[0][x] = w + dp[1][p];
            } else {
                dp[1][x] = max(dp[1][x], w + dp[1][p]);
            }
        } else {
            if (dp[0][p] + w > dp[0][x]) {
                dp[1][x] = dp[0][x];
                dp[0][x] = w + dp[0][p];
            } else {
                dp[1][x] = max(dp[1][x], w + dp[0][p]);
            }
        }
    }
    for (auto e : T[x]) {
        if (e.first == p) continue;
        dfs_reroot(e.first, x, cst[e.second]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        ed.assign(n, vector<pii>());
        w.assign(m, 0);
        cst.assign(m, 0);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            a--;
            b--;
            cst[i] = c;
            ed[a].emplace_back(b, i);
            ed[b].emplace_back(a, i);
        }
        bicomps();
        T.assign(n, vector<pii>());
        vis.assign(n, 0);
        color.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                dfs_(i, i);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (auto e : ed[i]) {
                if (w[e.second]) {
                    T[color[i]].emplace_back(color[e.first], e.second);
                }
            }
        }
        rep(i, 0, 2) dp[i].assign(n, 1e18);
        dfs_root(0, -1);
        dfs_reroot(0, -1);
        auto idx = min_element(all(dp[0]));
        cout << (idx - dp[0].begin() + 1) << " " << (*idx) << '\n';
    }
    return 0;
}
