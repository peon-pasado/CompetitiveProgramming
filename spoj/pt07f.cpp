#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <vector>
#define sz(c) ((int)c.size())
#define trav(it, c) for (auto it : c)
#define rep(var, begin, end) for (int var = begin; var < end; ++var)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(c) c.begin(), c.end()
#define rall(c) c.rbegin(), c.rend()
#define compress(c) (sort(all(c)), c.erase(unique(all(c)), c.end()))
#define emb emplace_back
#define psb push_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int mod = 1e9 + 7;
const string file_base = "";

int add(int a, int b, int m = mod) {
    return a + b < m ? a + b : a + b - m;
}

int mul(ll a, ll b, int m = mod) {
    return a * b % m;
}

int ex(int a, int b, int m = mod) {
    int r=1;
    for (; b>0; b/=2, a=mul(a,a,m))
        if (b&1) r = mul(r, a, m);
    return r;
}

const int inf = 1.2e9;
const int maxn = 1e4 + 10;
vector<int> g[maxn];
int dp[maxn][2];
int tr[maxn][2][2];

int cost(int v) {
    if (v == -1) return 1e9;
    return dp[v][1] - min(dp[v][0], dp[v][1]);
}

void upd_best(int best[], int v) {
    if (cost(best[0]) >= cost(v)) {
        best[1] = best[0];
        best[0] = v;
    }
    else if (cost(best[1]) > cost(v)) {
        best[1] = v;
    }
}

void dfs(int x, int p) {
    int sum = 0;
    int best[2] = {-1, -1};
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x);
        sum += min(dp[v][0], dp[v][1]);
        upd_best(best, v);
    }
    int u = best[0], v = best[1];
    tr[x][1][0] = tr[x][0][0] = -1;
    tr[x][1][1] = tr[x][0][1] = -1;
    dp[x][0] = sum + cost(u) + cost(v) - 1;
    tr[x][0][0] = u;
    tr[x][0][1] = v;
    if (sum + 1 > sum + cost(u)) {
        dp[x][1] = sum + cost(u);
        tr[x][1][0] = u;
    } else {
        dp[x][1] = sum + 1;
    }
}

vector<int> path[maxn];
void build(int x, int p, int st) {
    int a = tr[x][st][0], b = tr[x][st][1]; 
    for (int v : g[x]) {
        if (v == p) continue;
        if (v == a || v == b) continue;
        build(v, x, dp[v][0] > dp[v][1]);
    }
    if (a > 0) {
        build(a, x, 1);
        path[x].push_back(a);
        path[a].push_back(x);
    }
    if (b > 0) {
        build(b, x, 1);
        path[x].push_back(b);
        path[b].push_back(x);
    }
}

bool vis[maxn];
void print(int x, int p) {
    vis[x] = 1;
    cout << x;
    bool fst = 1;
    for (int v : path[x]) {
        if (v == p) continue;
        if (fst) {
            cout << ' ';
            fst = 0;
        }
        print(v, x);
    }
}

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int n;
        in >> n;
        for (int i = 1; i <= n; ++i) {
            g[i].clear();
            path[i].clear();
            vis[i] = 0;
        }
        for (int i = 1; i <= n-1; ++i) {
            int a, b;
            in >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        dfs(1, 0); 
        cout << min(dp[1][0], dp[1][1]) << '\n';
        build(1, 0, dp[1][0] > dp[1][1]);
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && sz(path[i]) <= 1) {
                print(i, 0);
                out << '\n';
            }
        }
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        in >> test_number;
        forn(tc, test_number) {
            //out << "Case #" << tc+1 << ": ";
            if (solve_one(in, out)) break;
        }
    }
};

int main() {
    Solver solver;
    if (!file_base.empty()) {
        ifstream in(file_base + ".in");
        ofstream out(file_base + ".out");
        in.exceptions(in.failbit);
        solver.solve(in, out);
    } else {
        cin.tie(nullptr)->sync_with_stdio(false);
        //cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}