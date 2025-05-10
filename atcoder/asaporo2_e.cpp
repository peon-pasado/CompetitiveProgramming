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

const int maxn = 2e5 + 10;
int sz[maxn];
long long ans[maxn];

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
        if (g[x].empty()) {
            sz[x] = 1;
            ord[x] = T++;
            return;
        }
        for (auto v : g[x]) {
            dfs(v, x);
            sz[x] += sz[v];
        } 
    }

    void calc(int x, long long sum=0) {
        if (g[x].empty()) {
            ans[x] = sum;
            return;
        }
        for (int i=0; i<2; ++i)
            calc(g[x][i], sum + val[x] *1ll* sz[g[x][1-i]]);
    }

    void make_tree() {
        T = 0;  
        for (int i = 0; i < g.size(); ++i) {
            if (pi[i] == i) {
                dfs(i);
                calc(i);
            }
        }
    }

};

int main() {
    fast_io;
    int n;
    cin>>n;
    vector<pair<int, pair<int, int>>> edges;
    for (int i=0; i<n-1; ++i) {
        int a, b, c;
        cin>>a>>b>>c;
        a--; b--;
        edges.push_back({c, {a, b}});
    }
    sort(all(edges), [](auto p, auto q) {
        return p.first > q.first;
    });
    reachability_tree dsu(n);
    for (auto e : edges) {
        dsu.merge(e.second.first, e.second.second, e.first);
    }
    dsu.make_tree();
    for (int i=0; i<n; ++i) {
        cout << ans[i] << " \n"[i+1==n];
    }
    return 0;   
}