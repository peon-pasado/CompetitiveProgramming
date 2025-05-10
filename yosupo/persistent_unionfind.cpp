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

    vector<int> pi;
    vector<size_t> size_tree;
    stack<int> changes;

    dsu_rollback(int n) {
        pi.resize(n);
        iota(all(pi), 0);
        size_tree.resize(n, 1);
    }

    void add() {
        pi.push_back(sz(pi));
        size_tree.push_back(1);
    }

    int get_root(int x) {
        return pi[x] != x ? get_root(pi[x]) : x;
    }

    void merge(int u, int v) {
        u = get_root(u);
        v = get_root(v);

        if (u == v) {
            changes.push(-1);
            return;
        }
        if (size_tree[u] < size_tree[v]) swap(u, v);
        
        size_tree[u] += size_tree[v];
        pi[v] = u;
        changes.push(v);
    } 

    bool same(int u, int v) {
        return get_root(u) == get_root(v);
    }

    void undo() {
        if (changes.empty()) return;
        if (changes.top() >= 0) {
            int v = changes.top();
            size_tree[pi[v]] -= size_tree[v];
            pi[v] = v;          
        }
        changes.pop();
    }
};

int main() {
    fast_io;
    int n, q;
    cin>>n>>q;
    dsu_rollback dsu(n);
    vector<pair<int, int>> edges;
    vector<vector<int>> tree(q + 1);
    vector<vector<int>> queries(q + 1);
    for (int i=1; i<=q; ++i) {
        int type, k, u, v;
        cin>>type>>k>>u>>v;
        edges.emplace_back(u, v);
        if (type == 1) {
            queries[k+1].push_back(i);
        } else {
            tree[k+1].push_back(i);
        }
    }
    vector<int> ans(q + 1, -1);
    auto dfs = [&](auto&& dfs, int x)->void {
        for (int v : queries[x]) {
            ans[v] = dsu.same(edges[v-1].first, edges[v-1].second);
        }

        for (int v : tree[x]) {
            dsu.merge(edges[v-1].first, edges[v-1].second);
            dfs(dfs, v);
            dsu.undo();
        }
    };
    dfs(dfs, 0);
    for (int i=1; i<=q; ++i) {
        if (ans[i]!=-1) cout << ans[i] << '\n';
    }
    return 0;
}