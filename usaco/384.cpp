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

int st[19][500005];

struct reachability_tree {
    vector<vector<int>> g;
    vector<int> pi;
    vector<int> val;
    //vector<int> ord;
    vector<pair<int, int>> range;
    int T;

    reachability_tree(int n) {
        g.resize(n);
        val.resize(n);
        pi.resize(n);
        //ord.resize(n);
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
            T++;
            //ord[x] = T++;
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

    int get_value(int x, int t) {
        for (int k=18; k>=0; --k) {
            if (range[st[k][x]].second - range[st[k][x]].first + 1 < t) {
                x = st[k][x];
            }
        }
        return val[st[0][x]];
    }

};

const int maxn = 502;
int h[maxn][maxn];
int r[maxn][maxn];

int main() {
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);
    int n, m, t;
    cin>>n>>m>>t;
    for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j) {
            cin>>h[i][j];
        }
    for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j) {
            cin>>r[i][j];
        }
    vector<pair<int, pair<int, int>>> edges;
    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};
    for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j)
            for (int k=0; k<4; ++k) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni < 0 || nj < 0) continue;
                if (ni >= n || nj >= m) continue;
                if (i * m + j < ni * m + nj) {
                    edges.push_back({abs(h[ni][nj] - h[i][j]), {i*m+j, ni*m+nj}});
                }
            }
    sort(all(edges));
    reachability_tree dsu(n * m);
    for (auto e : edges) {
        dsu.merge(e.second.first, e.second.second, e.first);
    }
    dsu.make_tree();
    long long sum = 0;
    for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j)
            if (r[i][j]) sum += dsu.get_value(i*m+j, t);
    cout << sum << '\n';
    return 0;
}