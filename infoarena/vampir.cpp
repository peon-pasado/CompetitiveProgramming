/**
 * @author Miguel Mini
 * @tag geometry, number_theory
 * @idea
 *      - as k si even, movements
 *      are 0 (mod k) for each axis.
 *  
 *      - radius is l / 2, thus k
 *      is a even divisor of l / 2.
 * 
 *      - B(k / 2, k / 2) / k is    
 *      decreasing. then k is
 *      maximum even divisor of
 *      l / 2.
 * 
 * @complexity O(l) with small constant.
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
      int p, l;
      in >> p >> l;
      l /= 2;
      vector<int> t;
      for (int i = 1; i * i <= l; ++i) {
        if (l % i == 0) {
          if (i % 2 == 0) t.push_back(i);
          if (l != i * i && l / i % 2 == 0) t.push_back(l / i);
        }
      }
      sort(all(t));
      if (t.empty()) out << -1 << '\n';
      else if (p == 1) {
        out << sz(t) << '\n';
        trav(v, t) out << v << " ";
        out << '\n';
      } else {
        int k = t.back();
        int p = l / k, q = k / 2;
        reu(i, 1, k / 2) {
          p = mul(p, i);
	        q = mul(q, k/2 + i);
        }
	      out << mul(p, ex(q, mod-2)) << '\n';
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Solver solver;
    string file = "vampir";
    if (!file.empty()) {
      ifstream in(file + ".in");
      ofstream out(file + ".out");
      solver.solve(in, out);
    } else {
      solver.solve(cin, cout);
    }
    return 0;
}