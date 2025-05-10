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


struct dsu_tree {

    vector<int> pi;
    vector<int> edge_pi;
    vector<size_t> rank;

    dsu_tree(int n) {
        pi.resize(n);
        iota(all(pi), 0);
        edge_pi.resize(n);
        rank.resize(n);
    }

    int get_root(int x) {
        return pi[x] != x ? get_root(pi[x]) : x;
    }

    int height(int x) {
        return x == pi[x] ? 0 : height(pi[x]) + 1;
    }

    void merge(int u, int v, int time) {
        u = get_root(u);
        v = get_root(v);

        if (u == v) return;
        if (rank[u] < rank[v]) swap(u, v);
        
        rank[u] += rank[u] == rank[v];
        pi[v] = u;
        edge_pi[v] = time;
    } 

    int min_edge(int u, int v) {
        if (u == v) return 0;
        if (get_root(u) != get_root(v)) return -1;
        int hu = height(u);
        int hv = height(v);
        if (hu > hv) swap(u, v), swap(hu, hv);
        if (hu != hv) { 
            while (hu + 1 != hv) {
                v = pi[v];
                hv--;
            }
            if (pi[v] == u) return edge_pi[v];
            v = pi[v];
        }
        while (pi[u] != pi[v]) {
            u = pi[u];
            v = pi[v];
        }
        return min(edge_pi[v], edge_pi[u]);
    }

};

const int maxn = 510;
vector<int> g[maxn];

int main() {
    cout << setprecision(8) << fixed;
    int n;
    cin>>n;
    vector<int> x(n), y(n);
    for (int i=0; i<n; ++i) {
        cin>>x[i]>>y[i];
    }
    int m;
    cin>>m;
    for (int i=0; i<m; ++i) {
        int a, b;
        cin>>a>>b;
        a--; b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    auto d2 = [&](int i, int j) {
        return (x[i]-x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
    };
    vector<pair<pair<int, int>, int>> edges;
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j) {

            for (int v : g[i]) {
                if (v != j) {
                    edges.push_back({{i * n + j, v * n + j}, min(d2(i, j), d2(v, j))});
                }
            }

            for (int v : g[j]) {
                if (v != i) {
                    edges.push_back({{i * n + j, i * n + v}, min(d2(i, j), d2(i, v))});
                }
            }

        }
    sort(all(edges), [](auto p, auto q) {
        return p.second > q.second;
    });
    dsu_tree dsu(n * n);
    for (auto e : edges) dsu.merge(e.first.first, e.first.second, e.second);
    int l;
    cin >> l;
    for (int i=0; i<l; ++i) {
        int u, v;
        cin>>u>>v;
        u--; v--;
        int ans = min(d2(u, v), dsu.min_edge(u*n+v, v*n+u));
        cout << sqrt(ans) << '\n';
    }
    return 0;
}