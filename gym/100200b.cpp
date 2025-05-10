#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi num;
vector<vector<pii>> ed;
vector<bool> w;

int Time;

int dfs(int at, int par)
{
    int me = num[at] = ++Time, e, y, top = me;
    trav(pa, ed[at]) if (pa.second != par)
    {
        tie(y, e) = pa;
        if (num[y]) {
            top = min(top, num[y]);
        } else {
            int up = dfs(y, e);
            top = min(top, up);
            if (up > me) w[e] = 1;
        }
    }
    return top;
}

void bicomps() {
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1);
}

int main()
{
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    ed.assign(n, vector<pii>());
    w.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        ed[a].emplace_back(b, i);
        ed[b].emplace_back(a, i);
    }
    bicomps();
    cout << accumulate(all(w), 0) << '\n';
    for (int i = 0; i < m; ++i) {
        if (w[i] == 1) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
    return 0;
}
