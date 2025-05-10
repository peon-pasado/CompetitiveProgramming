/**
 * @author Miguel Mini
 * @tag 2_sat, lazy_propagation, binary_search
 * @idea
 *      - fixed d, we can solve with a 2-sat
 *      solver.
 * 
 *      - in a range we need two types of
 *      edges:
 * 
 *          - a -> [l, r]
 *          - [l, r] -> a 
 * 
 *      - first kind of edges can be done
 *      using a segment tree two separe
 *      ranges.
 * 
 *      - the second class can be done
 *      pushing edges from nodes to child
 *      nodes.
 * 
 * @complexity O(n \log (n) \log (1e9))
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 10;
int x[maxn], y[maxn];
int n;
vector<pair<int, int>> pos;
vector<int> g[maxn * 20], gt[maxn * 20];
int var[maxn][2];
int node[maxn << 4][2];
bool lazy[maxn << 4];

int t;
int get_node() {
    return t++;
}

int neg[maxn << 1];

void build(int nx=1, int l=0, int r=2*n-1) {
    node[nx][0] = get_node();
    node[nx][1] = get_node();
    if (l == r) return;
    int mid = (l+r)/2;
    build(nx<<1, l, mid);
    build(nx<<1|1, mid+1, r);
}

void build_graph(int nx=1, int l=0, int r=2*n-1) {
    if (l == r) {
        g[node[nx][0]].push_back(r);
        g[r].push_back(node[nx][0]);
        
        gt[node[nx][0]].push_back(r);
        gt[r].push_back(node[nx][0]);

        g[node[nx][1]].push_back(neg[r]);
        g[neg[r]].push_back(node[nx][1]);

        gt[node[nx][1]].push_back(neg[r]);
        gt[neg[r]].push_back(node[nx][1]);
        return;
    }
    int mid = (l + r) / 2;
    build_graph(nx<<1, l, mid);
    build_graph(nx<<1|1, mid+1, r);
    g[node[nx][0]].push_back(node[nx<<1][0]);
    g[node[nx][0]].push_back(node[nx<<1|1][0]);

    gt[node[nx<<1][0]].push_back(node[nx][0]);
    gt[node[nx<<1|1][0]].push_back(node[nx][0]);
    
    g[node[nx][1]].push_back(node[nx<<1][1]);
    g[node[nx][1]].push_back(node[nx<<1|1][1]);
    
    gt[node[nx<<1][1]].push_back(node[nx][1]);
    gt[node[nx<<1|1][1]].push_back(node[nx][1]);
}

void add_edges(int nod, int ll, int rr, int nx=1, int l=0, int r=2*n-1) {
    if (rr < ll) return;
    if (rr < l || r < ll) return;
    if (ll <= l && r <= rr) {
        g[nod].push_back(node[nx][1]); 
        gt[node[nx][1]].push_back(nod);
        lazy[nx] = 1;
        return; 
    }
    int mid = (l + r) / 2;
    add_edges(nod, ll, rr, nx<<1, l, mid);
    add_edges(nod, ll, rr, nx<<1|1, mid+1, r);
}

void push(int nx=1, int l=0, int r=2*n-1) {
    if (l == r) return;
    int mid = (l + r) / 2;
    push(nx<<1, l, mid); 
    push(nx<<1|1, mid+1, r);
    if (lazy[nx]) {
        g[node[nx<<1][0]].push_back(node[nx][0]);
        g[node[nx<<1|1][0]].push_back(node[nx][0]);
        gt[node[nx][0]].push_back(node[nx<<1][0]);
        gt[node[nx][0]].push_back(node[nx<<1|1][0]);
    }
}

bool used[maxn * 20];
int comp[maxn * 20];
vector<int> order;

void dfs1(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    order.clear();
    memset(used, 0, sizeof used);
    for (int i = 0; i < 18 * n; ++i) {
        if (!used[i])
            dfs1(i);
    }
    memset(comp, -1, sizeof comp);
    for (int i = 0, j = 0; i < 18 * n; ++i) {
        int v = order[18 * n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }
    for (int i = 0; i < n; ++i) {
        if (comp[var[i][0]] == comp[var[i][1]]) return false;
    }
    return true;
} 

int main() {
    cin >> n;
    t = 2 * n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        pos.emplace_back(x[i], i);
        pos.emplace_back(y[i], i);
    }
    sort(pos.begin(), pos.end());
    for (int i = 0; i < pos.size(); ++i) {
        if (var[pos[i].second][0]) var[pos[i].second][1] = i + 1;
        else var[pos[i].second][0] = i + 1;
    }
    for (int i = 0; i < n; ++i) {
        var[i][0] -= 1;
        var[i][1] -= 1;
        neg[var[i][0]] = var[i][1];
        neg[var[i][1]] = var[i][0];
    }
    auto get_left = [&](int i, int d)->int {
        int lo = 0, hi = i;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (pos[mid].first < pos[i].first - d) lo = mid+1;
            else hi = mid;
        }
        return lo;
    };
    auto get_right = [&](int i, int d)->int {
        int lo = i, hi = 2*n-1;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (pos[mid].first <= pos[i].first + d) lo = mid;
            else hi = mid-1;
        }
        return lo;
    };
    build();
    auto p = [&](int d)->bool {
        for (int i = 0; i < 18 * n; ++i) {
            g[i].clear();
            gt[i].clear();
        }
        build_graph();
        for (int i = 0; i < 2 * n; ++i) {
            int l = get_left(i, d);
            int r = get_right(i, d);
            add_edges(i, l, i-1);
            add_edges(i, i+1, r);
        }
        return solve_2SAT();
    };
    int lo = 0, hi = 1e9;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (p(mid)) lo = mid;
        else hi = mid-1;
    }
    int ans = -1;
    if (p(lo)) ans = lo;
    cout << ans+1 << endl;
    return 0;
}