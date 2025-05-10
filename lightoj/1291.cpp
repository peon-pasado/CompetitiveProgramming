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

void bicomps()
{
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1);
}

vi color;
vector<bool> vis;
void dfs_(int x, int c)
{
    vis[x] = 1;
    color[x] = c;
    for (auto e : ed[x])
    {
        if (vis[e.first])
            continue;
        if (w[e.second])
            continue;
        dfs_(e.first, c);
    }
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    int tc=1;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        ed.assign(n, vector<pii>());
        w.assign(m, 0);
        for (int i = 0; i < m; ++i)
        {
            int a, b;
            cin >> a >> b;
            ed[a].emplace_back(b, i);
            ed[b].emplace_back(a, i);
        }
        bicomps();
        //T.assign(n, vector<pii>());
        vis.assign(n, 0);
        color.assign(n, -1);
        for (int i = 0; i < n; ++i)
        {
            if (!vis[i])
            {
                dfs_(i, i);
            }
        }
        vector<int> deg(n);
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            for (auto e : ed[i])
            {
                if (w[e.second]) {
                    deg[color[i]]++;
                    if (deg[color[i]] == 1) ans += 1;
                    else if (deg[color[i]] == 2) ans -= 1;
                }
            }
        }
        cout << "Case " << tc++ << ": " << (ans + 1) / 2 << "\n";
    }
    return 0;
}
