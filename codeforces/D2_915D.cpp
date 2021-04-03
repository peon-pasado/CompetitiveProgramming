/**
 * @author Miguel Mini
 * @tag brute_force, edge_classification
 * @idea
 *      - we need erase an edge
 *      from any cycle.
 * 
 *      - brute force edges from
 *      a cycle.
 * 
 * @complexity O(mn + n^2)
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
vii g[maxn];
bool active[maxn];
int vis[maxn];
vi path;

void get_cycle(int x, vi& cycle) {
  path.eb(x);
  vis[x] = 1;
  for (auto e : g[x]) {
    if (!vis[e.first]) get_cycle(e.first, cycle);
    else if (vis[e.first] == 1) {
      if (!cycle.empty()) continue;
      for (int i = sz(path)-1; i >= 0; --i) {
        cycle.eb(path[i]);
        if (path[i] == e.first) break;
      }
      reverse(all(cycle));
    }
  }
  vis[x] = 2;
  path.pop_back();
}

bool has_cycle(int x) {
  vis[x] = 1;
  bool ans = 0;
  for (auto e : g[x]) {
    if (!active[e.second]) continue;
    if (!vis[e.first]) ans |= has_cycle(e.first);
    else if (vis[e.first] == 1) return 1;
  }
  vis[x]= 2;
  return ans;
}


class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int n, m;
      in >> n >> m;
      map<ii, int> id;
      rep(i, m) {
        int a, b;
        in >> a >> b;
        g[a].emplace_back(b, i);
        id[{a, b}] = i;
      }
      vi c;
      reu(i, 1, n + 1) {
        if (!vis[i]) {
          get_cycle(i, c);
        }
      }
      if (c.empty()) out << "YES" << '\n';
      else {
        memset(active, 1, sizeof active);
        bool ans = 0;
        rep(i, sz(c)) {
          int id_e = id[{c[i], c[(i + 1) % sz(c)]}];
          active[id_e] = 0;
          bool ok = 0;
          memset(vis, 0, sizeof vis);
          reu(i, 1, n + 1) {
            if (!vis[i]) {
              ok |= has_cycle(i);
            }
          }
          ans |= !ok;
          active[id_e] = 1;
        }
        if (ans) out << "YES" << '\n';
        else out << "NO" << '\n';
      }
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
    string file = "";
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