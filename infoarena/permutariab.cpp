/**
 * @author Miguel Mini
 * @tag fenwick_tree, permutation
 * @idea
 *      - relabel b vector with 
 *      a order.
 * 
 *      - count number of inversions,
 *      note that a transposition
 *      of two consecutive elements
 *      reduce number of inversions
 *      in one.
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

const int maxn = 1e5 + 5;
int ft[maxn];
void upd(int x) {
  while (x<maxn) {
    ft[x]++;
    x += x&-x;
  }
}

int qry(int x) {
  int ans = 0;
  while (x > 0) {
    ans += ft[x];
    x -= x&-x;
  }
  return ans;
}

int id[maxn];

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int n; 
      in >> n;
      vi a(n), b(n);
      rep(i, n) in >> a[i];
      rep(i, n) in >> b[i];
      rep(i, n) id[a[i]] = i + 1;
      rep(i, n) b[i] = id[b[i]];
      ll ans = 0;
      rep(i, n) {
        ans += qry(b[i]);
        upd(b[i]);
      }
      out << n*1ll*(n-1) / 2 - ans << '\n';
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
    string file = "permutariab";
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