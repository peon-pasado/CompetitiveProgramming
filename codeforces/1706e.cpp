#include <bits/stdc++.h>
#define sz(v) static_cast<int>(v.size())
#define clear_fit(v) v.clear(), v.shrink_to_fit()
#define all(v) v.begin(), v.end()
#define unique(v) v.erase(unique(all(v)), v.end())
#define fast_io cin.tie(nullptr)->sync_with_stdio(false)

template<typename T1, typename T2>
inline auto max(T1 a, T2 b) {return a > b ? a : b;}

template<typename T1, typename T2>
inline auto min(T1 a, T2 b) {return a < b ? a : b;}

using namespace std;

int st[19][200005];
int h[200005];

pair<int, int> spt[19][200005];


struct reachability_tree {
    vector<vector<int>> g;
    vector<int> pi;
    vector<int> val;
    vector<int> ord;
    vector<pair<int, int>> range;
    int T;

    reachability_tree(int n) {
        g.resize(n);
        val.resize(n);
        pi.resize(n);
        ord.resize(n);
        iota(all(pi), 0);
    }

    int get(int x) {
        return x != pi[x] ? pi[x] = get(pi[x]) : x;
    }

    void merge(int x, int y, int time) {
        x = get(x);
        y = get(y);
        if (x == y) return;
        int new_node = g.size();
        g.resize(g.size() + 1);
        pi[x] = pi[y] = new_node;
        val.push_back(time);
        pi.push_back(new_node);
        g[new_node].push_back(x);
        g[new_node].push_back(y);
    }

    void build(vector<pair<pair<int, int>, int>> edges) {
        //sort(all(edges), [](auto p, auto q) {
        //    return p.first < p.second;
        //});
        for (auto e : edges) {
            merge(e.first.first, e.first.second, e.second);
        }
    }

    void dfs(int x, int p=-1) {
        st[0][x] = p==-1?x:p;
        for (int k=1; k<=18; ++k)
            st[k][x] = st[k-1][st[k-1][x]];
        h[x] = p==-1?0:h[p] + 1;
        if (g[x].empty()) {
            ord[x] = T++;
            return;
        }
        for (auto v : g[x]) {
            dfs(v, x);
        } 
    }

    void make_tree() {
        T = 0;  
        range.resize(g.size());
        for (int i = 0; i < g.size(); ++i) {
            if (pi[i] == i) {
                dfs(i);
            }
        }
    }

    int lca(int x, int y) {
        if (h[x] > h[y]) swap(x, y);
        for (int i=18; i>=0; --i) {
            if (h[st[i][y]] >= h[x]) {
                y = st[i][y];
            }
        }
        if (x == y) return x;
        for (int i=18; i>=0; --i) {
            if (st[i][x] != st[i][y]) {
                x = st[i][x];
                y = st[i][y];
            }
        }
        return st[0][x];
    }

    void init() {
        int n = (int)ord.size() - 1;
        for (int i=1; i <= n; ++i) {
            spt[0][i] = {i, i};
        }
        for (int k=1; k<=18; ++k) {
            for (int i=1; i+(1<<k)-1<=n; ++i) {
                if (ord[spt[k-1][i].first] < ord[spt[k-1][i+(1<<k-1)].first]) {
                    spt[k][i].first = spt[k-1][i].first;
                } else {
                    spt[k][i].first = spt[k-1][i+(1<<k-1)].first;
                }

                if (ord[spt[k-1][i].second] > ord[spt[k-1][i+(1<<k-1)].second]) {
                    spt[k][i].second = spt[k-1][i].second;
                } else {
                    spt[k][i].second = spt[k-1][i+(1<<k-1)].second;
                }
            }
        }
    }

    pair<int, int> query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);

        pair<int, int> q = spt[k][l];

        if (ord[spt[k][l].first] > ord[spt[k][r-(1<<k)+1].first]) {
            q.first = spt[k][r - (1<<k) + 1].first;
        }
        if (ord[spt[k][l].second] < ord[spt[k][r-(1<<k)+1].second]) {
            q.second = spt[k][r - (1<<k) + 1].second;
        } 
        return q;
    }


    int get_value(int x, int y) {
        auto r = query(x, y);
        return val[lca(r.first, r.second)];
    }

};

int main() {
    fast_io;
    int t;
    cin>>t;
    while (t--) {
        int n, m, q;
        cin>>n>>m>>q;
        reachability_tree dsu(n+1);
        for (int i=0; i<m; ++i) {
            int u, v;
            cin>>u>>v;
            dsu.merge(u, v, i+1);
        }
        dsu.make_tree();
        dsu.init();
        for (int i=1; i<=q; ++i) {
            int l, r;
            cin>>l>>r;
            cout << dsu.get_value(l, r) << " \n"[i==q];
        }
    }
    return 0;   
}