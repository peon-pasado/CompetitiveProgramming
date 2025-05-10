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
vector<vector<pii>> T;
vector<int> lnk, rnk;
vector<bool> bridge;
int dp[1010][1010];

void init(int n) {
    lnk.assign(n, 0);
    rnk.assign(n, 0);
    rep(i, 0, n) {
        lnk[i] = i;
    }
}

int get(int x) {
    return lnk[x]==x?x:lnk[x]=get(lnk[x]);
}

bool merge(int x, int y) {
    x = get(x); y = get(y);
    if (x == y) return 0;
    if (rnk[x] < rnk[y]) swap(x, y);
    rnk[x] += rnk[x]==rnk[y];
    lnk[y] = x;
    return 1;
}

int Time;
template <class F>
int dfs(int at, int par, F &f) {
    int me = num[at] = ++Time, e, y, top = me;
    trav(pa, ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y]) {
            top = min(top, num[y]);
            if (num[y] < me)
                st.push_back(e);
        } else {
            int si = sz(st);
            int up = dfs(y, e, f);
            top = min(top, up);
            if (up == me) {
                st.push_back(e);
                f(vi(st.begin() + si, st.end()));
                st.resize(si);
            } else if (up < me)
                st.push_back(e);
            else{ 
                bridge[e] = 1;
                /* e is a bridge */
            }
        }
    }
    return top;
}

template <class F>
void bicomps(F f) {
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}

long long best;
void dfs_(int r, int x, int p, long long c = 1e18) {
    best = max(best, dp[r][x] - c);
    for (auto e : T[x]) {
        if (e.first == p) continue;
        if (bridge[e.second]) dfs_(r, e.first, x, min(c, (long long)dp[x][e.first]));
        else dfs_(r, e.first, x, c);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, mod;
        cin >> n >> m >> mod;
        for (int i = 0; i < n; ++i)
            dp[i][0] = dp[0][i] = 1;
        dp[0][0] = 0; 
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                if (i == j) dp[i][j] = 0;
                else {
                    dp[i][j] = dp[i][j-1]+dp[i-1][j];
                    if (dp[i][j]>=mod) dp[i][j] -= mod;
                    dp[i][j] += dp[i-1][j-1];
                    if (dp[i][j]>=mod) dp[i][j] -= mod;
                }
            }
        }
        ed.assign(n, vector<pii>());
        T.assign(n, vector<pii>());
        init(n);
        bridge.assign(m, 0);
        vector<pii> E;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            E.emplace_back(a, b);
            ed[a].emplace_back(b, i);
            ed[b].emplace_back(a, i);
        }
        if (mod == 1) {
            cout << "0\n";
            continue;
        }
        bicomps([&](vi edges) {
            for (int id : edges) {
                int u = E[id].first;
                int v = E[id].second;
                if (merge(u, v)) {
                    T[u].emplace_back(v, id);
                    T[v].emplace_back(u, id);
                }
            }
        });
        for (int i = 0; i < m; ++i) {
            if (bridge[i]) {
                int u = E[i].first;
                int v = E[i].second;
                T[u].emplace_back(v, i);
                T[v].emplace_back(u, i);
            }
        }
        best = 0;
        for (int i = 0; i < n; ++i) {
            dfs_(i, i, -1);
        }
        cout << best << '\n';
    }
    return 0;
}
