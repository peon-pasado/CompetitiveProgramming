/**
 * @author Miguel Mini
 * @tag constructive
 * @idea
 *    - we must assign cm. 
 * 
 *    - assign all c_i to 
 *    elements with ai != bi
 *    and others to an element
 *    with bj = cm.
 * 
 * @complexity O((n + m) \log m)
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

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int n, m;
      in >> n >> m;
      vi a(n), b(n), c(m);
      rep(i, n) in >> a[i];
      rep(i, n) in >> b[i];
      rep(i, m) in >> c[i];
      vector<bool> vis(n);
      bool ok = 0;
      int pos = -1;
      rep(i, n) {
        if (a[i] != b[i]) {
          vis[i] = 1;
          if (b[i] == c.back()) {
            ok = 1;
            pos = i;
          }
        } 
      }
      if (!ok) {
        rep(i, n) {
          if (a[i] == b[i] && b[i] == c.back() && !ok) {
            vis[i] = 1;
            ok = 1;
            pos = i;
          }
        }
      }
      if (!ok) {
        out << "NO" << '\n'; 
        return;
      }
      multiset<ii> sc;
      rep(i, m) sc.insert({c[i], i});
      vi ans(m);
      rep(i, n) {
        if (vis[i]) {
          auto q = sc.lower_bound({b[i], -1});
          if (q == sc.end() || q->first != b[i]) {
            out << "NO" << '\n';
            return;
          }
          ans[q->second] = i + 1;
          sc.erase(q);
        }
      }
      for (auto e : sc) ans[e.second] = pos + 1;
      out << "YES" << '\n';
      rep(i, m) out << ans[i] << ' ';
      out << '\n';
    }
    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        in >> testNumber;
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