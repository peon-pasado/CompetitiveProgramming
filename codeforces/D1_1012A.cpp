/**
 * @author Miguel Mini
 * @tag multicase
 * @idea
 *      - there are two cases:
 * 
 *          - max(a) and min(a)
 *          is in x.
 * 
 *          - max(a) is in x and
 *          min(a) is in y.
 * 
 *      - suppose a sorted.
 *  
 *      - first case:
 * 
 *          - answer is:
 *  
 *            (max(a) - min(a)) * (a[i+n-1] - a[i])
 * 
 *          for i in range [2, n].
 *              
 *      - second case:
 *  
 *          (max(a) - a[n + 1]) * (a[n] - min(a))
 * 
 * @complexity O(n \log n)
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
      int n;
      in >> n;
      vi a(2 * n);
      rep(i, 2 * n) in >> a[i];
      sort(a.begin(), a.end());
      ll ans = (a[n-1] - a[0]) *1ll* (a[2*n-1] - a[n]);
      reu(i, 1, n) {
        ans = min(ans, (a[2*n-1]-a[0])*1ll*(a[i+n-1] - a[i]));
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