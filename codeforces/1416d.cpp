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

int st[19][400005];                  

struct reachability_tree {
    vector<vector<int>> g;
    vector<int> pi;
    vector<int> val;
    vector<int> ord;
    vector<pair<int, int>> range;
    int T;

    reachability_tree() {}

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

    void dfs(int x, int p=-1) {
        st[0][x] = p==-1?x:p;
        for (int k=1; k<=18; ++k)
            st[k][x] = st[k-1][st[k-1][x]];
        if (g[x].empty()) {
            range[x] = {T, T};
            ord[T++] = x;
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

    pair<int, int> get_range(int x, int t) {
        for (int k=18; k>=0; --k) {
            if (val[st[k][x]] < t) {
                x = st[k][x];
            }
        }
        return range[x];
    }

} dsu;

const int maxn = 2e5 + 10;
int p[maxn];
int se[maxn << 2];

void build(int x, int l, int r) {
    if (l == r) {
        se[x] = r;
        return;
    }
    int mid = (l + r) / 2;
    build(2*x, l, mid);
    build(2*x+1, mid+1, r);
    if (p[dsu.ord[se[2*x]]] < p[dsu.ord[se[2*x+1]]]) se[x] = se[2*x+1];
    else se[x] = se[2*x];
}

int get_max(int x, int l, int r, int ll, int rr) {
    if (rr < l || r < ll) return -1;
    if (ll <= l && r <= rr) return se[x];
    int mid = (l + r) / 2;
    int L = get_max(2*x, l, mid, ll, rr);
    int R = get_max(2*x+1, mid+1, r, ll, rr);
    if (L == -1) return R;
    if (R == -1) return L;
    if (p[dsu.ord[L]] < p[dsu.ord[R]]) return R;
    return L;
}

void erase_max(int x, int l, int r, int ps) {
    if (ps < l || r < ps) return;
    if (l == r) {
        p[dsu.ord[r]] = 0;
        return;
    }
    int mid = (l+r)/2;
    erase_max(2*x, l, mid, ps);
    erase_max(2*x+1, mid+1, r, ps);
    if (p[dsu.ord[se[2*x]]] < p[dsu.ord[se[2*x+1]]]) se[x] = se[2*x+1];
    else se[x] = se[2*x];   
}


int main() {
    fast_io;
    int n, m, q;
    cin>>n>>m>>q;
    for (int i=0; i<n; ++i) cin>>p[i];
    vector<pair<int, pair<int, int>>> edges;
    for (int i=1; i<=m; ++i) {
        int a, b;
        cin>>a>>b;
        a--; b--;
        edges.push_back({0, {a, b}});
    }
    vector<int> queries(q);
    for (int i=0; i<q; ++i) {
        int t, v;
        cin>>t>>v;
        queries[i] = t==1?v-1:-1;
        if (t==2) edges[v-1].first = q + 1 - i;
    }
    sort(all(edges));
    dsu = reachability_tree(n);
    for (auto e : edges)
        dsu.merge(e.second.first, e.second.second, e.first);
    dsu.make_tree();
    build(1, 0, n-1);
    int t = q + 2;
    for (int i=0; i<q; ++i) {
        if (queries[i] == -1) {
            t = min(t, q + 1 - i);
            continue;
        }
        auto r = dsu.get_range(queries[i], t);
        int pos = get_max(1, 0, n-1, r.first, r.second);
        cout << p[dsu.ord[pos]] << '\n';
        erase_max(1, 0, n-1, pos); 
    }
    return 0;
}