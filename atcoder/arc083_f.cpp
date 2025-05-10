/**
 * @author Miguel Mini
 * @tag dag, functional_graph, combinatorics, greedy
 * @idea
 *  - if no see points (x, y) as edges (x, n+y), 
 *  notice that components are functional graphs
 *  (in other case, no valid order exists).
 * 
 *  - notice that elements in a cycle has two options
 *  and other nodes only one.
 * 
 *  - if we fix a direction for every node in a cycle.
 *  (think for x) notice that for point (x, n+y) points 
 *  (x, n+t) needs be select before if t < y. make
 *  a dag with these restrictions and count number of
 *  dags.   
 *  
 *  - final answer is 2n! x (ans(c) for c in components),
 *  where ans(c) is ans2(first direction) + ans2(second directions)
 *  and ans2 is prod(sz(v))^-1, where sz is number of nodes
 *  in every subtree. 
 * 
 * @complexity O(n)
 */ 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;
vector<int> g[maxn];
bool vis[maxn];
vector<int> vtx;
using ll = long long;
using vi = vector<int>;

int add(int a, int b) {
    return (a+b)%mod;
}

int mul(ll a, ll b) {
    return a*b%mod;
}

void dfs(int x) {
    vis[x] = 1;
    for (int v : g[x]) {
        if (!vis[v]) dfs(v);
    }
    vtx.push_back(x);
}

int f[maxn], f_inv[maxn], inv[maxn];
void init() {
    f[0] = f_inv[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        f[i] = mul(f[i-1], i);
        f_inv[i] = mul(f_inv[i-1], 
            inv[i] = (i == 1 ? 1 : mul(inv[mod % i], mod - mod/i)));
    }
}

int state[maxn];
vi path;
void get_cycle(int v, int p, vi& c) {
    state[v] = 1;
    path.push_back(v);
    for (int u : g[v]) {
        if (u == p) continue;
        if (!state[u]) {
            get_cycle(u, v, c);
        } else if (state[u] == 1) {
            if (c.empty()) {
                for (int i = (int)path.size()-1; i >= 0; --i) {
                    c.push_back(path[i]);
                    if (path[i] == u) break;
                }
                reverse(c.begin(), c.end());
            }
        }
    }
    path.pop_back();
    state[v] = 2;
}

bool dag_vis[maxn];
int deg[maxn];
int pi[maxn];
void get_parents(int x, int p) {
    dag_vis[x] = 1; 
    pi[x] = p;
    for (int v : g[x]) {
        if (v < p) deg[v]++;
        if (v == p || dag_vis[v]) continue;
        get_parents(v, x);
    }
}

int sz[maxn];
void ways(int x) {
    dag_vis[x] = 1;
    sz[x] = 1;
    for (int v : g[x]) {
        if (dag_vis[v]) continue;
        if (v < pi[x]) {
            ways(v);
            sz[x] += sz[v];
        }
    }
}

int calc(vi& v) {
    vi c;
    get_cycle(v[0], 0, c);
    for (int nod : v) deg[nod] = 0;
    get_parents(c[0], c[1]);
    for (int nod : v) dag_vis[nod] = 0;
    for (int nod : v) 
        if (!deg[nod]) 
            ways(nod);
    int r1 = 1;
    for (int nod : v) r1 = mul(r1, inv[sz[nod]]);
    for (int nod : v) dag_vis[nod] = 0;    
    for (int nod : v) deg[nod] = 0;    
    get_parents(c[1], c[0]);
    for (int nod : v) dag_vis[nod] = 0;
    for (int nod : v)
        if (!deg[nod])
            ways(nod);
    int r2 = 1;
    for (int nod : v) r2 = mul(r2, inv[sz[nod]]);
    return add(r1, r2);
}

int main() {
    init();
    int n;
    cin >> n;
    for (int i = 0; i < 2*n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(n+y);
        g[n+y].push_back(x);
    }
    int ans = f[2 * n]; 
    for (int i = 1; i <= 2*n; ++i) {
        if (vis[i]) continue;
        vtx.clear();
        dfs(i);
        int deg = 0;
        for (int v : vtx) deg += g[v].size();
        if (deg != 2 * vtx.size()) {
            cout << "0\n";
            exit(0);
        }
        ans = mul(ans, calc(vtx));
    }
    cout << ans << '\n';
    return 0;
}