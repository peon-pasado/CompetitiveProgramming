/**
 * @author Miguel Mini
 * @tag dp, big_number, memory_compression
 * @idea
 *      - this is a simple dp problem
 *      with big_numbers
 * 
 *      - use iterative version
 *  
 *      - strict memory limit
 * 
 * @complexity O(n^2) with small constant
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
const int maxn = 5010;
const ll dece = 1e18;
using bnum = vector<ll>;
bnum dp[2][5];
int n;

bnum operator+(bnum& x, bnum& y) {
  bnum res = bnum(max(sz(x), sz(y)), 0); 
  ll carry = 0;
  rep(i, sz(res)) {
    if (i < sz(x)) res[i] += x[i];
    if (i < sz(y)) res[i] += y[i];
    res[i] += carry;
    carry = 0;
    while (res[i] >= dece) {
      carry++;
      res[i] -= dece; 
    }
  }
  if (carry > 0) res.push_back(carry);
  return res;
}

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      in >> n;
      for (int i = 0; i < 5; ++i) {
        dp[n&1][i] = bnum({1});
      }
      for (int i = n-1; i >= 1; --i) {
        for (int j = 0; j < 5; ++j) {
          dp[i&1][j] = bnum({0});
          if (j > 0 && j < 4) dp[i&1][j] = dp[i&1^1][j-1] + dp[i&1^1][j+1];
          else if (j == 0) dp[i&1][j] = dp[i&1^1][j+1];
          else dp[i&1][j] = dp[i&1^1][j-1];
        }
        for (int j = 0; j < 5; ++j) dp[i&1^1][j].clear();
      }
      bnum ans = bnum({0});
      for (int i = 0; i < 5; ++i) ans = ans + dp[1][i];
      string res = "";
      for (int i = sz(ans) - 1; i >= 0; --i) {
        string u = to_string(ans[i]);
        string g = string(18 - sz(u), '0') + u;
        res += g;
      }
      reverse(all(res));
      while (res.size() > 1 && res.back() == '0') {
        res.pop_back();
      }
      reverse(all(res));
      out << res << '\n';
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
    string file = "culori3";
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