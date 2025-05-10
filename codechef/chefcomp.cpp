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
int a[maxn], b[maxn];
int inv[maxn];
int ans[maxn];
int p[maxn];

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

    vector<pair<long long, int>> arr;
    void dfs(int x, int pa=-1, int lval=0) {
       
        if (lval != val[x]) {
            arr.emplace_back(a[p[val[x]]] + arr.back().first, val[x]);
        }

        if (g[x].empty()) {
            int lo = 1, hi = (int)arr.size() - 1;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (arr[mid].first < b[x]) lo = mid+1;
                else hi = mid;
            }    
            if (arr[lo].first >= b[x]) ans[x] = arr[lo].second;
            else ans[x] = -1;
        }

        for (auto v : g[x]) {
            dfs(v, x, val[x]);
        }
        if (lval != val[x]) {
            arr.pop_back();
        }
    }

    void make_tree() {
        arr.push_back({0, 0});
        T = 0;  
        range.resize(g.size());
        for (int i = 0; i < g.size(); ++i) {
            if (pi[i] == i) {
                dfs(i);
            }
        }
    }

};

int main() {
    fast_io;
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        vector<pair<int, pair<int, int>>> edges;
        for (int i=0; i<n-1; ++i) {
            int a, b;
            cin>>a>>b;
            edges.push_back({0, {a, b}});
        }
        for (int i=1; i<=n; ++i) {
            cin>>p[i];
            inv[p[i]] = i;
        }
        for (int i=0; i<n-1; ++i) {
            edges[i].first = min(inv[edges[i].second.first], inv[edges[i].second.second]);
        }
        sort(all(edges), [&](auto a, auto b) {
            return a.first > b.first;
        });
        for (int i=1; i<=n; ++i) cin>>a[i];
        for (int i=1; i<=n; ++i) cin>>b[i];
        reachability_tree dsu(n + 1);
        for (int i=1; i<=n; ++i) dsu.val[i] = inv[i];
        for (auto e : edges) {
            dsu.merge(e.second.first, e.second.second, e.first);
        }
        dsu.make_tree();
        for (int i=1; i<=n; ++i) cout << ans[i] << " \n"[i==n];
    }   
    return 0;
}