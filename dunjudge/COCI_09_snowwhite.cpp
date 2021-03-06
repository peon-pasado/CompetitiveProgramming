/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag sweep_line, offline, randomized
 * @idea
 *      - we can solve the problem offline with a sweep line, 
 *      for each range we consult the number of times that an 
 *      element is repeated, to do this we can consult in l-1 
 *      what values will be consulted and in r finish counting.
 *
 *  @complexity: O(n + q*(logq + ITER)), where ITER is the number 
 *  of count queries per range.
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
const int maxn = 5e5 + 10;

class COCI_09_snowwhite {
public:
    void solveOne(istream& in, ostream& out) {
      int n, c;
      in >> n >> c;
      vi a(n + 1);
      re(i, 1, n+1) in >> a[i];
      int m;
      in >> m;
      struct Query {
          int pos, id;
      };
      vector<Query> queries;
      vector<ii> query(m);
      const int ITER = 30;
      vector<vector<ii>> res(m, vector<ii>(ITER));
      re(i, 0, m) {
        int l, r;
        in >> l >> r;
        query[i] = {l, r};
        queries.push_back({l-1, -(i + 1)});
        queries.push_back({r, i + 1});
      }
      sort(all(queries), [](Query p, Query q) {
        return p.pos < q.pos;
      });
      vi cnt(c + 1);
      for (int i = 0, j = 0; i <= n; ++i) {
        cnt[a[i]] += 1;
        while (j < sz(queries) and queries[j].pos == i) {
          if (queries[j].id < 0) {
            int id = -(queries[j].id + 1);
            int r = query[id].second;
            for (int k = 0; k < ITER; ++k) {
              int pos = random(i + 1, r);
              res[id][k] = {a[pos], -cnt[a[pos]]};
            }
          } else {
            int id = queries[j].id - 1;
            for (int k = 0; k < ITER; ++k) {
              res[id][k].second += cnt[res[id][k].first];
            }
          }
          j += 1;
        }
      }
      for (int i = 0; i < m; ++i) {
        int ans = -1;
        int min_len = (query[i].second - query[i].first + 1) / 2;
        for (int j = 0; j < ITER; ++j) {
          if (res[i][j].second > min_len) {
            ans = res[i][j].first;
            //break;
          }
        }
        if (~ans) out << "yes " << ans << '\n';
        else out << "no" << '\n';
      }
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
    COCI_09_snowwhite solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}
