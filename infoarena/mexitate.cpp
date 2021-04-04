/**
 * @author Miguel Mini
 * @tag sqrt_decomposition
 * @idea
 *      - we can update mex
 *      adding o erasing an 
 *      element in O(1) with
 *      query in O(sqrt(n*m)):
 * 
 *          - maintain complete
 *          sets in blocks of 
 *          length sqrt(n * m).
 *          we can query in
 *          2 * sqrt(n * m).  
 *      
 *      - (assume n <= m) we need 
 *          (n - k + 1) * (m - l + 1)
 *      queries.
 * 
 *      - we can compute a row 
 *      in k * (m - l + 1).
 * 
 *      - we can change the row
 *      in O(l).
 * 
 *      - we need compute (n - k + 1)
 *      rows and change (n - k).
 * 
 * @complexity O(m * n * (n + sqrt(n * m)))
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
const int maxn = 4e5 + 10;
const int sq = 640;
int sum_block[640];
int sum[maxn];

void update(int x, int v) {
  if (v == 1) {
    sum[x]++;
    sum_block[x / sq] += sum[x] == 1;
  } else {
    sum[x]--;
    sum_block[x / sq] -= sum[x] == 0; 
  }
}

int mex() {
  int i = 0;
  while (sum_block[i] == sq) ++i;
  i *= sq;
  while (sum[i] > 0) ++i;
  return i + 1;
}


class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      int n, m, k, l;
      in >> n >> m >> k >> l;
      bool swp = 0;
      if (n > m) {
        swap(n, m);
        swap(k, l);
        swp = 1;
      }
      vector<vi> A(n, vi(m));
      if (!swp) {
        rep(i, n) rep(j, m) {
          in >> A[i][j];
          A[i][j] -= 1;
        }
      } else {
        rep(j, m) rep(i, n) {
          in >> A[i][j];
          A[i][j] -= 1;
        }
      }
      rep(i, k-1)
        rep(j, l)
          update(A[i][j], 1);     
      int ans = 1;
      rep(i, n-k+1) {
        if (i % 2 == 0) {
          rep(j, l) update(A[i+k-1][j], 1);
          ans = mul(ans, mex());
          reu(j, l, m) {
            rep(h, k) {
              update(A[i+h][j], 1);
              update(A[i+h][j-l], -1);
            }
            ans = mul(ans, mex());
          }
          rep(j, l) update(A[i][m-1-j], -1);
        } else {
          rep(j, l) update(A[i+k-1][m-1-j], 1);
          ans = mul(ans, mex());
          reu(j, l, m) {
            rep(h, k) {
              update(A[i+h][m-1-j], 1);
              update(A[i+h][m-1-j+l], -1);
            }
            ans = mul(ans, mex());
          }
          rep(j, l) update(A[i][j], -1);
        }
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
    string file = "mexitate";
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