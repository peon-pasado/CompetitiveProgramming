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

const int maxn = 505;
int h[maxn][maxn];
const int dx[] = {0, 0, -1, 1}; 
const int dy[] = {-1, 1, 0, 0};
int n, m, q;


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
        if (u == v) return h[u/m][u%m];
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


bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

int main() {
    fast_io;
    cin>>n>>m>>q;
    vector<pair<int, int>> nodes;
    for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j) {
            cin>>h[i][j];
            nodes.emplace_back(h[i][j], i*m+j);
        }
    sort(all(nodes));
    dsu_tree dsu(n * m);
    for (auto node : nodes) {
        int i = node.second / m, j = node.second % m;
        for (int k=0;k<4; ++k) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (!valid(ni, nj)) continue;
            if (h[ni][nj] > node.first) continue;
            dsu.merge(node.second, ni * m + nj, node.first);
        }        
    }
    while (q--) {
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        x1--; y1--; x2--; y2--;
        cout << dsu.min_edge(x1*m+y1, x2*m+y2) << '\n';
    }
    return 0;
}