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


#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int maxn = 1e5 + 2;
ordered_set s[maxn];

int st[19][2 * maxn];

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
        if (g[x].empty()) {
            range[x] = {T, T};
            ord[x] = T++;
            return;
        }
        range[x] = {1e9, 0};
        for (auto v : g[x]) {
            dfs(v, x);
            range[x].first = min(range[x].first, range[v].first);
            range[x].second = max(range[x].second, range[v].second);
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

    pair<int, int> get_range(int x, int time) {
        for (int k=18; k>=0; --k) {
            if (val[st[k][x]] <= time) {
                x = st[k][x];
            }
        }
        return range[x];
    }

};




int main() {
    fast_io;
    int n, m, k;
    cin>>n>>m>>k;
    reachability_tree tree(n);
    vector<pair<int, pair<int, int>>> friends;
    for (int i=0; i<m; ++i) {
        int u, v;
        cin>>u>>v;
        u--; v--;
        friends.push_back({0, {u, v}});
    }
    for (int i=0; i<k; ++i) {
        int u, v;
        cin>>u>>v;
        u--; v--;
        tree.merge(u, v, 0);
    }
    vector<pair<int, int>> queries;
    int q;
    cin>>q;
    for (int i=1; i<=q; ++i) {
        string s;
        int a, b;
        cin>>s;
        if (s == "T") {
            cin>>a>>b;
            a--; b--;
            tree.merge(a, b, i);
        } else if (s == "F") {
            cin>>a>>b;
            a--; b--;
            friends.push_back({i, {a, b}});
        } else {
            cin>>a;
            a--;
            queries.emplace_back(i, a);
        }
    }
    tree.make_tree();
    int j = 0;
    for (auto [t, u] : queries) {
        while (j < friends.size() && friends[j].first <= t) {
            int u = friends[j].second.first;
            int v = friends[j].second.second;
            s[u].insert(tree.ord[v]);
            s[v].insert(tree.ord[u]);
            j++;
        }
        auto r = tree.get_range(u, t);
        int ans = s[u].order_of_key(r.second + 1) - s[u].order_of_key(r.first);
        cout << ans << '\n';        
    }
    return 0;
}