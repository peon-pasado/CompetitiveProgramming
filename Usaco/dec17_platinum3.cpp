/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag greedy, sorting, binary_search 
 * @idea:
 *      - We should note that the cows that receive 
 *      gifts are in a continuous range of indices.
 *
 *      - To prove that mid belongs to that range, 
 *      we can assume that there is a cycle and see 
 *      if for any turn it is possible to exit, obviously 
 *      the worst case scenario is that the one with the 
 *      least c occurs first and we simply simulate this process.
 *
 *      - with a bit trick we can solve this in O(nlogn)
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

class dec17_platinum3 {
public:
    void solveOne(istream& in, ostream& out) {
      int n;
      in >> n;
      vi a(n);
      trav(&x, a) in >> x;
      multiset<int> order;
      int pt = -1;
      auto p = [&](int x) {
          while (pt + 1 < x) order.insert(a[++pt]);
          while (pt >= x) order.erase(order.lower_bound(a[pt--]));
          int best = n - x - 1;
          for (auto e : order) {
            if (e > best) return 0;
            best += 1;
          }
          return 1;
      };
      int lo = 0, hi = n-1;
      while (lo < hi) {
        int mid = lo + (hi-lo+1)/2;
        if (p(mid)) lo = mid;
        else hi = mid-1;
      }
      out << n - lo - 1 << endl;
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
    freopen("greedy.in", "r", stdin);
    freopen("greedy.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    dec17_platinum3 solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}
