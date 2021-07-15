/**
 * @author Miguel Mini
 * @tag dp, matrix, automaton
 * @idea 
 *      - we can make a dp
 *      automaton of transition,
 *      avoiding columns.
 * 
 *      - we can exponentiate
 *      this automaton to obtain
 *      the answer.
 * 
 * @complexity O(8^n x \log m)
 */ 
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>
#include <fstream>
#include <stack>
#include <queue>
#include <math.h>
#include <tuple>
#include <climits>
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
    return a+b < m? a+b : a+b-m;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%m;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (b > 0) {
        if (b&1) r = mul(r, a, m);
        a = mul(a, a, m);
        b >>= 1;
    }
    return r;
}

const int inf = INT_MAX / 2.2;

class Solver {
public:
    int n;
    long long m;
    int g[1<<6][1<<6];
    void get_tr(int mask) {
      set<vector<int>> nxt;
      int pot = 1;
      for (int i = 0; i < n; ++i) pot *= 3;
      for (int s = 0; s < pot; ++s) {
        int nxt_mask = 0;
        int ts = s;
        vector<int> e;
        for (int j = 0; j < n; ++j) {
          if (mask & (1<<j)) continue;
          if (ts % 3 == 0) {
            e.push_back(0);
            if (j + 1 < n && ((~mask) & (1<<j+1))) {
              j++;
            } else {
              nxt_mask = -1;
              break;
            }
          } else if (ts % 3 == 1) {
            e.push_back(1);
            nxt_mask |= 1<<j;
          } else {
            e.push_back(2);
          }
          ts /= 3;
        }
        if (nxt_mask >= 0 && !nxt.count(e)) {
          nxt.insert(e);
          int v = nxt_mask;
          g[mask][v] += 1;
        }
      }
    }
    struct Matrix {
      int at[1<<6][1<<6];
      int n;
      Matrix() {}
      Matrix(int m[1<<6][1<<6], int n) {
        this->n = n;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            at[i][j] = m[i][j];
          }
        }
      }
      Matrix one(int n) {
        Matrix R;
        R.n = n;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            R.at[i][j] = i==j;
          }
        }
        return R;
      }
      Matrix operator*(Matrix B) {
        Matrix R;
        R.n = B.n;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            R.at[i][j] = 0;
            for (int k = 0; k < n; ++k) {
              R.at[i][j] = add(R.at[i][j], mul(at[i][k], B.at[k][j]));
            }
          }
        }
        return R;
      }
    };
    Matrix ex(Matrix A, ll T) {
      Matrix R = A.one(A.n);
      while (T > 0) {
        if (T&1) R = R * A;
        A = A * A;
        T >>= 1;
      }
      return R;
    }
    void solveOne(istream& in, ostream& out) {
      in >> n >> m;
      for (int i = 0; i < 1<<n; ++i) {
        for (int j = 0; j < 1<<n; ++j) {
          g[i][j] = 0;
        }
      }
      for (int i = 0; i < 1<<n; ++i) get_tr(i);
      Matrix dp(g, 1<<n);
      dp = ex(dp, m);
      cout << dp.at[0][0] << '\n'; 
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