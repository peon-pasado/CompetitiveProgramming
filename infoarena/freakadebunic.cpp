/**
 * @author Miguel Mini
 * @tag auxiliary_tree, lca_offline
 * @idea
 *      - according to the construction 
 *      of the auxiliary tree, lca added
 *      is the set(lca(c[i], c[i+1])) 
 *      for c with order of lo.
 *  
 *      - we need find lca with low memory,
 *      we can use lca offline algorithm.
 * 
 * @complexity O(n \alpha n + k \log k)
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
const int mod = 1e9 + 7;

int add(int a, int b, int m=mod) {
    return a+b < mod? a+b : a+b-mod;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%mod;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

const int inf = INT_MAX / 2.2;
const int maxn = 1e5 + 10;
int lo[maxn];
int T;
bitset<maxn> is_lca;
int ancestor[maxn];
vi queries[maxn], g[maxn];
int lnk[maxn];

int get(int x) {
  return x == lnk[x] ? x : lnk[x] = get(lnk[x]);
}

void merge(int x, int y) {
  lnk[get(x)] = get(y);
}

void init(int x) {
  lnk[x] = x;
}

void dfs(int x, int p) {
  lo[x] = T++;
  for (int v : g[x]) {
    if (v == p) continue;
    dfs(v, x);
  }
}

void dfs_lca(int x, int p) {
  ancestor[x] = x;
  for (int v : g[x]) {
    if (v == p) continue;
    dfs_lca(v, x);
    merge(v, x);
    ancestor[get(x)] = x;
  }
  for (int v : queries[x])
    is_lca[ancestor[get(v)]] = 1;
}


class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int n, k;
      in >> n >> k;
      vi c(k);
      rep(i, k) in >> c[i];
      rep(i, n-1) {
        int a, b;
        in >> a >> b;
        g[a].eb(b);
        g[b].eb(a);
      }
      dfs(1, 0);
      sort(all(c), [](int u, int v) {
        return lo[u] < lo[v];
      });
      rep(i, k-1) {
        queries[c[i+1]].eb(c[i]);
      }
      rep(i, n) init(i+1);
      dfs_lca(1, 0);
      int ans = 0;
      rep(i, n) ans += is_lca[i+1];
      out << ans << '\n';
      rep(i, n) {
        if (is_lca[i + 1]) out << i+1 << ' ';
      }
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
    string file = "freakadebunic";
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