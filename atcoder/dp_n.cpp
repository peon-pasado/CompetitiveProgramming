/**
 * @author Miguel Mini
 * @tag dp
 * @idea
 *      - build from final
 *      to start position.
 * 
 *      - use dp
 * 
 * @complexity O(n^3)
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
const int maxn = 410;
ll sum[maxn];
bool vis[maxn][maxn];
ll memo[maxn][maxn];

ll dp(int l, int r) {
  if (l == r) return 0;
  if (vis[l][r]) return memo[l][r];
  ll ans = 1e18;
  reu(i, l, r) {
    ans = min(ans, dp(l, i) + dp(i + 1, r) + sum[r] - sum[l-1]);
  }
  vis[l][r] = 1;
  return memo[l][r] = ans;
}


class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int n;
      in >> n;
      for (int i = 1; i <= n; ++i) {
        in >> sum[i];
        sum[i] += sum[i-1];
      }
      out << dp(1, n) << '\n';
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