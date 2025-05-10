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

const int maxn = 3e5 + 10;
int st[19][maxn * 2];
int h[maxn * 2];

struct reachability_tree {
    vector<vector<int>> g;
    vector<int> pi;
    vector<int> val;
    vector<int> ord;
    //vector<pair<int, int>> range;
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
        h[x] = p==-1?0:h[p]+1;
        if (g[x].empty()) {
            //range[x] = {T, T};
            //ord[x] = T++;
            return;
        }
        //range[x] = {1e9, 0};
        for (auto v : g[x]) {
            dfs(v, x);
            //range[x].first = min(range[x].first, range[v].first);
            //range[x].second = max(range[x].second, range[v].second);
        } 
    }

    void make_tree() {
        T = 0;  
        //range.resize(g.size());
        for (int i = 0; i < g.size(); ++i) {
            if (pi[i] == i) {
                dfs(i);
            }
        }
    }

    int query(int x, int y) {
        if (!x || !y) return x+y;
        if (h[x] > h[y]) swap(x, y);
        for (int k=18; k>=0; --k) {
            if (h[st[k][y]] >= h[x]) {
                y = st[k][y];
            }
        }
        if (x == y) return x;
        for (int k=18; k>=0; --k) {
            if (st[k][x] != st[k][y]) {
                x = st[k][x];
                y = st[k][y];
            }
        }
        return st[0][x];
    }

} dsu;

int n, q;
int tree[maxn * 4];
int cur[maxn * 4];
bool lazy[2][maxn * 4];


void build(int nx=1, int l=1, int r=n) {
    if (l == r) {
        tree[nx] = r;
        return;
    }
    int mi = (l+r)/2;
    build(2*nx, l, mi);
    build(2*nx+1, mi+1, r);
    tree[nx] = dsu.query(tree[2*nx], tree[2*nx+1]);
}

void update_one(int nx, bool t) {
    cur[nx] = t ? tree[nx] : 0;
    lazy[t][nx] = 1;
    lazy[1-t][nx] = 0;
}

void push(int nx) {
    for (int i=0; i<2; ++i) {
        if (lazy[i][nx]) {
            update_one(2*nx, i);
            update_one(2*nx+1, i);
            lazy[i][nx] = 0;
        }
    }
}


void update(int ll, int rr, bool state, int nx=1, int l=1, int r=n) {
    if (rr < l || r < ll) return;
    if (ll <= l && r <= rr) {
        update_one(nx, state);
        return;
    }       
    push(nx);
    int mi = (l + r) / 2;
    update(ll, rr, state, 2*nx, l, mi);
    update(ll, rr, state, 2*nx+1, mi+1, r);
    cur[nx] = dsu.query(cur[2*nx], cur[2*nx+1]);
}


int main() {
    fast_io;
    cin>>n>>q;
    vector<pair<int, pair<int, int>>> edges(n-1);
    for (int i=0; i<n-1; ++i) {
        int u, v, w;
        cin>>u>>v>>w;
        edges[i] = {w, {u, v}};
    }
    sort(all(edges));
    dsu = reachability_tree(n + 1);
    for (auto [w, e] : edges) {
        dsu.merge(e.first, e.second, w);
    }
    dsu.make_tree();
    for (int i=0; i<=n; ++i) dsu.val[i] = -1;
    build();
    while (q--) {
        int t;
        cin>>t;
        if (t<=2) {
            int l, r;
            cin>>l>>r;
            update(l, r, 2-t);
        } else {
            int x;
            cin>>x;
            cout << dsu.val[dsu.query(x, cur[1])] << '\n';
        }
    }
    return 0;
}