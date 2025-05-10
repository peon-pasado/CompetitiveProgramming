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

struct dsu_rollback {

    vector<int> parent;
    vector<int> w;
    vector<size_t> subtree_sz;
    stack<int> changes;
    bool bipartite;

    dsu_rollback(int n) {
        parent.resize(n);
        w.resize(n);
        iota(all(parent), 0);
        subtree_sz.resize(n, 1);
        bipartite = 1;
    }

    int get_root(int x) {
        return parent[x] != x ? get_root(parent[x]) : x;
    }

    int h(int u) {
        if (parent[u] == u) return 0;
        return w[u] ^ h(parent[u]);
    }

    void merge(int x, int y) {
        int u = get_root(x); 
        int v = get_root(y);
        if (u == v) {
            if (bipartite && h(x) == h(y)) {
                bipartite = 0;
                changes.push(-2); 
            } else changes.push(-1);
            return;
        }
        if (subtree_sz[u] < subtree_sz[v]) swap(u, v);
        w[v] = (h(x) ^ h(y) ^ 1);
        subtree_sz[u] += subtree_sz[v];
        parent[v] = u;
        changes.push(v);
    } 

    bool same(int u, int v) {
        return get_root(u) == get_root(v);
    }

    void undo() {
        if (changes.empty()) return;
        if (changes.top() >= 0) {
            int v = changes.top();
            subtree_sz[parent[v]] -= subtree_sz[v];
            parent[v] = v;
        } else if (changes.top() == -2) {
            bipartite = 1;
        }
        changes.pop();
    }
};

struct Edge {
    int u, v;
};

struct QueueLike {
    using event = pair<bool, Edge>;
    dsu_rollback dsu;
    vector<event> changes;
    int m;

    QueueLike(int n): dsu(n), m(0) {}

    void merge(int u, int v) {
        changes.push_back({1, {u, v}});
        dsu.merge(u, v);
    }

    void pop() {
        if (m == 0) {
            m = changes.size();
            for (int i=0; i<m; ++i) dsu.undo();
            reverse(all(changes));
            for (auto& [t, e] : changes) t=0, dsu.merge(e.u, e.v);
        }
        if (changes.back().first) {
            vector<stack<event>> tmp(2);
            while (changes.back().first) {
                tmp[1].push(changes.back());
                dsu.undo();
                changes.pop_back();
            }
            int lso = (m & -m);
            for (int i=0; i<lso; ++i) {
                tmp[0].push(changes.back());
                dsu.undo();
                changes.pop_back();
            }
            for (int i=1; i>=0; --i) {
                while (!tmp[i].empty()) {
                    auto [t, e] = tmp[i].top(); tmp[i].pop();
                    dsu.merge(e.u, e.v);
                    changes.push_back({t, e});
                }
            }
        }
        changes.pop_back();
        dsu.undo();
        m--;
    }
};

int main() {
    fast_io;
    int n, m, q;
    cin>>n>>m>>q;
    vector<Edge> edges;
    for (int i=0; i<m; ++i) {
        int u, v;
        cin>>u>>v;
        u--; v--;
        edges.push_back({u, v});
    }   
    QueueLike Q(n);
    for (auto e : edges) {
        Q.merge(e.u, e.v);
    }
    vector<int> dp(m + 1);
    for (int i=0, j=1; i<m; ++i) {
        while (j <= m && !Q.dsu.bipartite) {
            Q.pop(); 
            j++;
        }
        dp[i] = !Q.dsu.bipartite ? m + 2 : j;       
        Q.merge(edges[i].u, edges[i].v);
    }
    while (q--) {
        int l, r;
        cin>>l>>r;
        if (r + 1 < dp[l - 1]) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}