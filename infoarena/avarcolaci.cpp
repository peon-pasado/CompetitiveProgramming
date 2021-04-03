/**
 * @author Miguel Mini
 * @tag moore's_voting_algorithm
 * @idea
 *      - direct application.
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


class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int n;
      in >> n;
      n <<= 1;
      vector<int> arr(n);
      for (int i = 0; i < n; ++i) {
        in >> arr[i];
      }
      ii c = {arr[0], 1};
      for (int i = 1; i < n; ++i) {
        if (c.first == arr[i]) {
          c.second += 1;
        } else {
          c.second -= 1;
          if (c.second < 0) {
            c = {arr[i], 1};
          }
        }
      }
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        if (c.first == arr[i]) cnt += 1;
      }
      if (2 * cnt > n) out << c.first << '\n';
      else out << "Mozart" << '\n';
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
    string file = "avarcolaci";
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