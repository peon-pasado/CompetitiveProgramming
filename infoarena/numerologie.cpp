/**
 * @author Miguel Mini
 * @tag bitmask, number_theory
 * @idea
 *      - divide in primes <= sqrt(m)
 *      and primes > sqrt(m).
 * 
 *      - note that numbers has 
 *      at most one divisor in second
 *      set.
 * 
 *      - we can fix every subset
 *      of first set in O(2**11)
 *      and solve in O(n + m / log(m))
 *      for mask.
 * 
 * @complexity O(2**pi(sqrt(m)) * (n + m / log(m))) ~ 2e6 operations.
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
      vi a(n);
      rep(i, n) in >> a[i];
      vii pr;
      vi c(m+1);
      reu(i, 1, m+1) {
        in >> c[i];
        if (~c[i]) {
          pr.eb(i, c[i]);
        }
      }
      vi b(all(a));
      int k = min(sz(pr), 11);
      vi mask(n);
      rep(i, n) {
        rep(j, k) {
          if (b[i] % pr[j].first == 0) {
            mask[i] |= (1<<j);
            while (b[i] % pr[j].first == 0) {
              b[i] /= pr[j].first;
            } 
          }
        }
      }
      int ans = 2e9;
      rep(i, (1<<k)) {
        int cst = 0;
        rep(j, k) if (i & (1<<j)) {
          cst += pr[j].second;
        }
        vector<bool> vis(n);
        bool ok = 1;
        vector<bool> ss(m + 1);
        rep(j, n) {
          if (!(i & mask[j])) { 
            if (b[j] == 1) {
              ok = 0;
            } else {
              ss[b[j]] = 1;
            }
          }
        }
        if (!ok) continue;
        trav(e, pr)
          if (ss[e.first]) {
            cst += e.second;
          }
        ans = min(ans, cst);
      }
      out << ans << '\n';
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
    string file = "numerologie";
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