/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag convex hull
 * @idea
 *     - keep the functions a_i + sqrt(x - b_i) for x >= b_i
 *     - these functions with different a_i only have at most
 *     one interception
 *     - Tricky cases, a function starts at a value greater
 *     than the current value of all functions in the convex hull
 *     - Compare the last with the penultimate and the new with
 *     the last, so you will avoid the previous case.
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
const int mod = 1e9 + 7;

int add(int a, int b, int m=mod) {
    return a+b < mod? a+b : a+b-mod;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%mod;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (r > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

const int inf = 1.2e9;
const int maxn = 5e5 + 10;

struct Node {
    int x, y;
};
deque<Node> lower;
int pot[maxn * 3];

int eval(Node p, int x) {
  return p.y + pot[abs(p.x - x)];
}

double eval2(Node p, int x) {
  return p.y + sqrt(abs(p.x-x));
}


using i64b = __int128;
bool is_left(Node o, Node a, Node b) {
  i64b alpha_x = a.x - o.x;
  i64b alpha_y = a.y - o.y;
  i64b beta_x = b.x - a.x;
  i64b beta_y = b.y - a.y;
  return ((alpha_x + alpha_y * alpha_y) * (alpha_x + alpha_y * alpha_y) + 4 * alpha_y * alpha_y * o.x)* beta_y * beta_y
      > ((beta_x + beta_y * beta_y)   * (beta_x + beta_y * beta_y) + 4 * beta_y * beta_y * a.x)* alpha_y * alpha_y;

}

void add(Node p) {
  int n = lower.size();
  if (!lower.empty() && lower[n-1].y >= p.y) {
    return;
  }
  while ((n >= 1 && eval(lower[n-1], p.x) <= p.y) || (n >= 2 && is_left(lower[n-2], lower[n-1], p))) {
    lower.pop_back();
    n -= 1;
  }
  lower.push_back(p);
}

int get(int x) {
  while (sz(lower) >= 2 && eval2(lower[0], x) < eval2(lower[1], x)) {
    lower.pop_front();
  }
  return eval(lower[0], x);
}

class POI_11_conductor {
public:
    void solveOne(istream& in, ostream& out) {
      int n;
      in >> n;
      vi h(n);
      re(i, 0, n) {
        in >> h[i];
      }
      re(i, 0, 1001) {
          re(j, i * i + 1, (i + 1) * (i + 1) + 1) {
            pot[j] = i + 1;
          }
      }
      vi ans = h;
      re(i, 0, n) {
        add({i, h[i]});
        ans[i] = max(ans[i], get(i));
      }
      reverse(all(ans));
      reverse(all(h));
      lower.clear();
      re(i, 0, n) {
        add({i, h[i]});
        ans[i] = max(ans[i], get(i));
      }
      reverse(all(ans));
      reverse(all(h));
      re(i, 0, n) {
        out << ans[i] - h[i] << '\n';
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
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    POI_11_conductor solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}