/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag dp, minqueue, knapsack
 * @idea
 *      - we can do a sweep line with dp, keeping 
 *      a minimum queue for the numbers of the form 
 *      b [i] * q + r. 
 */

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <complex>
#include <climits>
#include <iomanip>
#include <numeric>
#include <functional>
#include <fstream>
#include <cassert>
#include <chrono>
#include <random>
#include <bitset>
#include <stack>
#define sz(x) (int)x.size()
#define trav(v, x) for (auto v : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define set_to(x, v) fill(all(x), v)
#define eb emplace_back
#define lso(x) ((x)&-(x))
#define mset(m ,v) memset(m, v, sizeof(m))
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using si = set<int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

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

const int inf = 1.2e9;
const int maxn = 20000 + 10;
int dp[201][maxn];
int tr[201][maxn];

template <class T>
struct minQueue {
    stack<T> l, r;
    T right_min;
    minQueue(): right_min({inf, inf}) {}
    void add(T c) {
      r.push(c);
      right_min = min(right_min, c);
    }
    void pop() {
      if (l.empty()) {
        right_min = T({inf, inf});
        while (!r.empty()) {
          if (l.empty()) l.push(r.top());
          else l.push(min(l.top(), r.top()));
          r.pop();
        }
        if (!l.empty()) l.pop();
      } else l.pop();
    }
    T get_min() {
      if (l.empty()) return right_min;
      return min(l.top(), right_min);
    }
};

class POI05_Banknote {
public:
    void solveOne(istream& in, ostream& out) {
      int n;
      in >> n;
      vi b(n), c(n);
      re(i, 0, n) in >> b[i];
      re(i, 0, n) in >> c[i];
      int k;
      in >> k;
      memset(dp, 1, sizeof dp);
      dp[0][0] = 0;
      re(i, 0, c[0]) {
        if ((i + 1) * b[0] > k) break;
        dp[0][(i + 1) * b[0]] = (i+1);
        tr[0][(i + 1) * b[0]] = (i+1);
      }
      re(i, 1, n) {
        re(j, 0, b[i]) {
          minQueue<pair<int, int>> Q;
          for (int p = 0; p*b[i] + j <= k; ++p) {
            int cur = p * b[i] + j;
            Q.add({dp[i-1][cur] - p, p});
            if (p > c[i]) Q.pop();
            auto temp = Q.get_min();
            dp[i][cur] = temp.first + p;
            tr[i][cur] = p - temp.second;
          }
        }
      }
      out << dp[n-1][k] << endl;
      vi res;
      re(i, 0, n) {
        int cnt = tr[n-1-i][k];
        res.eb(cnt);
        k -= cnt * b[n-1-i];
      }
      reverse(all(res));
      trav(e, res) out << e << " ";
      out << endl;
    }

    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        //in >> testNumber;
        re(tc, 1, testNumber+1) {
            //out << "Case #" << tc << ": ";
            solveOne(in, out);
        }
    }
};


int main() {
    //freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    POI05_Banknote solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}
