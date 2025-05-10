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
        return max(edge_pi[v], edge_pi[u]);
    }

};

int main() {
    fast_io;
    int t;
    cin>>t;
    while (t--) {
        int n, m;
        cin>>n>>m;
        dsu_tree dsu(n + 1);
        for (int i = 1; i <= m; ++i) {
            int t, u, v;
            cin>>t>>u>>v;
            if (t==1) dsu.merge(u, v, i);
            else cout << dsu.min_edge(u, v) << '\n';
        }
    }
    return 0;
}