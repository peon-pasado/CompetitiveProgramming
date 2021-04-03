/**
 * @author Miguel Mini
 * @tag greedy, sorting
 * @idea
 *      - we can erase
 *      in the same order
 *      of b.
 * 
 *      - if we can erase
 *      a neighbor of b[i]
 *      in a, then operacion
 *      is same as erase
 *      b[i].  
 * 
 *      - re-label elements
 *      in a with order in b 
 *      (element not in b with 
 *      0), multiply by: 
 *      
 *          (a[i-1] < a[i]) + (a[i+1] < a[i])
 *  
 * @complexity O(n\log n)
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
const int mod = 998244353;

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
      int n, k;
      in >> n >> k;
      vi a(n), b(k);
      rep(i, n) in >> a[i];
      rep(i, k) in >> b[i];
      map<int, int> pos;
      rep(i, k) pos[b[i]] = i + 1;
      int ans = 1;
      rep(i, n) {
        if (pos[a[i]] == 0) continue;
        int sum = 0;
        if (i > 0 && pos[a[i-1]] < pos[a[i]]) {
          sum += 1;
        }
        if (i + 1 < n && pos[a[i+1]] < pos[a[i]]) {
          sum += 1;
        }
        ans = mul(ans, sum);
      }
      out << ans << '\n';
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