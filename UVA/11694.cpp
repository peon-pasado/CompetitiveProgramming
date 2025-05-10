#include <bits/stdc++.h>
using namespace std;

const int maxn = 10;
int n;
const int dx[] = {-1, -1, 1, 1};
const int dy[] = {-1, 1, -1, 1};
int deg[maxn][maxn];
int dd[maxn][maxn];

struct dsu_rollback {

    vector<int> parent;
    vector<size_t> subtree_sz;
    stack<int> changes;

    void init(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        subtree_sz.resize(n, 1);
        while (!changes.empty()) changes.pop();
    }

    int get_root(int x) {
        return parent[x] != x ? get_root(parent[x]) : x;
    }

    void merge(int u, int v) {
        u = get_root(u); v = get_root(v);
        if (u == v) {
            return changes.push(-1);
        }
        if (subtree_sz[u] < subtree_sz[v]) swap(u, v);
        
        subtree_sz[u] += subtree_sz[v];
        parent[v] = u;
        changes.push(v);
    } 

    bool same(int u, int v) {
        return get_root(u) == get_root(v);
    }

    void undo() {
        if (changes.empty()) return;
        if (changes.top() >= 0) {
            int v = changes.top();
            subtree_sz[parent[v]] -= subtree_sz[v];
            parent[v] = v;          
        }
        changes.pop();
    }
} dsu;

bool valid(int x, int y) {
    return x>=0 && y>=0 && x<=n && y<=n;
}

int adj[7 * maxn][7 * maxn];
char s[maxn][maxn];
void print_solution() {
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            cout << s[i][j];
        }
        cout << '\n';
    }
}

bool check(int x, int y, bool r) {
    if (r) {
        if (dsu.same(x * (n + 1) + y, (x + 1) * (n+1) + y+1)) return 0;
        if (deg[x][y] != -1 && dd[x][y] + 1 != deg[x][y]) return 0;
        if (deg[x][y+1] != -1 && dd[x][y+1] > deg[x][y+1]) return 0;
        if (deg[x+1][y] != -1 && dd[x+1][y] > deg[x+1][y]) return 0;
        if (deg[x+1][y+1] != -1 && dd[x+1][y+1] + 1 > deg[x+1][y+1]) return 0;
        if (y != n-1) {
            if (deg[x][y+1] != -1 && abs(dd[x][y + 1] - deg[x][y + 1]) > 1) return 0;
        } else {
            if (deg[x][y+1] != -1 && dd[x][y+1] != deg[x][y+1]) return 0;
        }
        if (x != n-1) {
            if (deg[x+1][y] != -1 && abs(dd[x + 1][y] - deg[x + 1][y]) > 1 + (y != 0)) return 0;
        } else {
            if (deg[x+1][y] != -1 && dd[x + 1][y] != deg[x + 1][y]) return 0;
        }
        if (x == n-1 && y == n-1) {
            if (deg[x+1][y+1] != -1 && dd[x+1][y+1] + 1 != deg[x+1][y+1]) return 0;
        }
        return 1;
    }
    if (dsu.same(x * (n + 1) + y + 1, (x + 1) * (n+1) + y)) return 0;
    if (deg[x][y] != -1 && dd[x][y] != deg[x][y]) return 0;
    if (deg[x][y+1] != -1 && dd[x][y+1] + 1 > deg[x][y+1]) return 0;
    if (deg[x+1][y] != -1 && dd[x+1][y] + 1 > deg[x+1][y]) return 0;
    if (deg[x+1][y+1] != -1 && dd[x+1][y+1] > deg[x+1][y+1]) return 0;
    if (y != n-1) {
        if (deg[x][y+1] != -1 && abs(dd[x][y + 1] + 1 - deg[x][y + 1]) > 1) return 0;
    } else {
        if (deg[x][y+1] != -1 && dd[x][y+1] + 1 != deg[x][y+1]) return 0;
    }
    if (x != n-1) {
        if (deg[x+1][y] != -1 && abs(dd[x + 1][y] + 1 - deg[x + 1][y]) > 1 + (y != 0)) return 0;
    } else {
        if (deg[x+1][y] != -1 && dd[x + 1][y] + 1 != deg[x + 1][y]) return 0;
    }
    if (x == n-1 && y == n-1) {
        if (deg[x+1][y+1] != -1 && dd[x+1][y+1] != deg[x+1][y+1]) return 0;
    }
    return 1;
}

bool solve(int x, int y) {
    if (y == n) return solve(x+1, 0);
    if (x == n) {
        print_solution();
        return 1;
    }
    int P = x * (n + 1) + y, Q = P + 1;
    int R = P + (n + 1), S = R + 1;
    bool ans = 0;
    if ((adj[P][S] & 1) && (adj[Q][R] & 2) && check(x, y, 1)) {
        dd[x][y] += 1;
        dd[x + 1][y + 1] += 1;
        s[x][y] = '\\';
        dsu.merge(x*(n+1)+y, (x+1)*(n+1)+(y+1));
        ans = solve(x, y + 1);
        dsu.undo();
        dd[x][y] -= 1;
        dd[x + 1][y + 1] -= 1;
    }
    if (ans) return 1;
    if ((adj[P][S] & 2) && (adj[Q][R] & 1) && check(x, y, 0)) {
        dd[x + 1][y] += 1;
        dd[x][y + 1] += 1;
        s[x][y] = '/';
        dsu.merge(x*(n+1)+y+1, (x+1)*(n+1)+y);
        ans = solve(x, y + 1);
        dsu.undo();
        dd[x + 1][y] -= 1;
        dd[x][y + 1] -= 1;
    }
    return ans;
}

int main() {
    int T;
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=0; i<=n; ++i) {
            string s;
            cin>>s;
            for (int j = 0; j<=n; ++j) {
                if (s[j] == '.') {
                    deg[i][j] = -1;
                } else {
                    int x = s[j] - '0';
                    deg[i][j] = x;
                }
            }
        }   
        dsu.init((n+1)*(n+1));
        for (int i=0; i<(n+1)*(n+1); ++i)
            for (int j=0; j<(n+1)*(n+1); ++j)
                adj[i][j] = 3;
        for (int i=0; i<=n; ++i) {
            for (int j=0; j<=n; ++j) {
                if (deg[i][j] % 4 == 0) {
                    for (int k=0; k<4; ++k) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (!valid(nx, ny)) continue;
                        adj[i * (n + 1) + j][nx * (n + 1) + ny] = 
                            adj[nx * (n + 1) + ny][i * (n + 1) + j] = 
                                (deg[i][j] == 0 ? 2 : 1);
                    }
                }
            }
        }
        solve(0, 0);
    }
    return 0;
}