/**
 * @author Miguel Mini
 * @tag dp, sweep_line
 * @idea
 *      - to adchieve maximum number
 *      of disjoint ranges we can
 *      proceed with greedy approach.
 * 
 *      - to consider number of '?'
 *      characters we can maintain an
 *      sweepline dp.
 * 
 *      - As for position i, and because 
 *      we want the maximum #disjoint ranges, 
 *      then the previous maximums #disjoint ranges
 *      must always be considered, for this we have
 *      a maximum prefix of (cnt, cost).
 * 
 * @complexity O(n + m)
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
      string s;
      in >> n >> s >> m;
      vii len1(n), len2(n);
      if (s[n-1] == 'a') {
        len1[n-1] = {1, 0};
      }
      if (s[n-1] == '?') {
        len1[n-1] = {1, 1};
        len2[n-1] = {1, 1};
      }
      if (s[n-1] == 'b') {
        len2[n-1] = {1, 0};
      }
      for (int i = n-2; i >= 0; --i) {
        if (s[i] == 'a' || s[i] == '?') {
          len1[i] = i + 2 < n ? len1[i+2] : make_pair(0, 0);
          len1[i].first += 1;
          len1[i].second += s[i] == '?';
        }
        if (s[i] == 'b' || s[i] == '?') {
          len2[i] = i + 2 < n ? len2[i+2] : make_pair(0, 0);
          len2[i].first += 1;
          len2[i].second += s[i] == '?';
        }
      }
      vector<int> cst(n, 1e9);
      rep(i, n - m + 1) {
        if (len1[i].first >= (m + 1) / 2 && len2[i + 1].first >= m / 2) {
          if (m%2 == 0) {
            cst[i] = len1[i].second + len2[i+1].second;
            if (i + m < n) cst[i] -= len1[i+m].second;
            if (i + m + 1 < n) cst[i] -= len2[i+m+1].second;
          } else {
            cst[i] = len1[i].second;
            if (i + 1 < n) cst[i] += len2[i+1].second;
            if (i + m < n) cst[i] -= len2[i+m].second;
            if (i + m + 1 < n) cst[i] -= len1[i+m+1].second;
          }
        }
      }
      ii res = {0, 0};
      vii dp(n);
      rep(i, n) {
        if (i + m - 1 < n) {
          dp[i + m - 1] = res;
          dp[i + m - 1].first += cst[i] <= n;
          dp[i + m - 1].second -= cst[i];
        }
        res = max(res, dp[i]);
      }
      out << -res.second << '\n';
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