/**
 * @author Miguel Mini
 * @tag bfs, dp, number_theory, bfs_tree
 * @idea
 *      - we can make a bfs tree and 
 *      count number of ways to reach
 *      a node from source and sink.
 * 
 *      - we can calculate these ways
 *      with toposort fashion algorithm.
 * 
 *      - as the numbers are very bigs
 *      we can hash the numbers and 
 *      keeping multiplication avaiable.
 * 
 *      - we can use a big prime number
 *      and multiply in binary form.
 * 
 * @complexity O(n \log n + m)
 */ 
#include <bits/stdc++.h>
#define sz(x) ((int)x.size())
#define trav(v, x) for (auto v : x)
#define reu(x, y, z) for (int x=y; x<z; ++x)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define eb emplace_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const ll mod = 1000000000000000003ll;

ll add(ll a, ll b, ll m=mod) {
    return a+b < m? a+b : a+b-m;
}

ll mul(ll a, ll b, ll m=mod) {
   ll r = 0;
   while (b > 0) {
     if (b&1) r = add(r, a, m);
     a = add(a, a, m);
     b >>= 1;
   }
   return r;
}

const int inf = INT_MAX / 2.2;
const int maxn = 7510;
vi g[maxn], adj[maxn], adjt[maxn];
int d[2][maxn], deg[maxn], degt[maxn];
ll ways[2][maxn];
int n;

void bfs(int x, int d[]) {
  vector<bool> vis(n + 1);
  queue<int> Q;
  Q.push(x);
  vis[x] = 1;
  d[x] = 0;
  while (!Q.empty()) {
    int q = Q.front(); Q.pop();
    for (int v : g[q]) {
      if (!vis[v]) {
        vis[v] = 1;
        d[v] = d[q] + 1;
        Q.push(v);
      }
    }
  }
}

void bfs2(int x, ll ways[], vi adj[], int deg[]) {
  queue<int> Q;
  Q.push(x);
  ways[x] = 1;
  while (!Q.empty()) {
    int q = Q.front(); Q.pop();
    for (int v : adj[q]) {
      deg[v]--;
      ways[v] = add(ways[v], ways[q]);
      if (deg[v] == 0) {
        Q.push(v);
      }
    }
  }
}

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int m, x, y;
      in >> n >> m >> x >> y;
      rep(i, m) {
        int a, b;
        in >> a >> b;
        g[a].eb(b);
        g[b].eb(a);
      }
      bfs(x, d[0]);
      bfs(y, d[1]);
      for (int i = 1; i <= n; ++i) {
        for (int j : g[i]) {
          if (d[0][i] + 1 + d[1][j] == d[0][y]) {
            adj[i].push_back(j); deg[j] += 1;
            adjt[j].push_back(i); degt[i] += 1;
          }
        }
      }
      bfs2(x, ways[0], adj, deg);
      bfs2(y, ways[1], adjt, degt);
      ll w = ways[0][y];
      vector<int> res;
      for (int i = 1; i <= n; ++i) {
        if (mul(ways[0][i], ways[1][i]) == w) {
          res.push_back(i);
        } 
      } 
      out << sz(res) << '\n';
      for (int v : res) out << v << ' ';
      out << '\n';
    } 
    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        //in >> testNumber;
        rep(tc, testNumber) {
            //out << "Case #" << tc+1 << ": ";
            solveOne(in, out);
        }
    }
};

int main() {
    Solver solver;
    string file = "graf";
    if (!file.empty()) {
      ifstream in(file + ".in");
      ofstream out(file + ".out");
      in.tie(nullptr);
      in.exceptions(in.failbit);
      solver.solve(in, out);
    } else {
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);
      solver.solve(cin, cout);
    }
    return 0;
}