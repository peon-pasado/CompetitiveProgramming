/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag geometry, polygon
 * @idea
 *      - simple geometry problem
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
const double PI = 3.14159265358979323846;
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

struct Point {
    double x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    Point operator-(Point other) {
      return Point(x-other.x, y-other.y);
    }
    double operator*(Point q) {
      return q.x * x + q.y * y;
    }
    double operator^(Point q) {
      return x * q.y - y * q.x;
    }
    double length() {
      return sqrt((*this) * (*this));
    }
};

class UVA10445 {
public:
    void solveOne(istream& in, ostream& out) {
      int n;
      while (in >> n) {
        if (n < 3) break;
        vector<Point> p(n);
        for (int i = 0; i < n; ++i) {
          int x, y;
          in >> x >> y;
          p[i] = Point(x, y);
        }
        auto nxt = [&](int i)->int {
          return (i + 1) % n;
        };
        auto prv = [&](int i)->int {
          return (i + n - 1) % n;
        };
        double sum = 0;
        for (int i = 0; i < n; ++i) {
          sum += p[i] ^ p[nxt(i)];
        }
        if (sum < 0) {
          //cerr << "polygon reverse" << endl;
          reverse(p.begin(), p.end());
        }
        double min_angle = 10000, max_angle = 0;
        for (int i = 0; i < n; ++i) {
          int a = nxt(i), b = i, c = prv(i);
          auto A = (p[a] - p[b]);
          auto B = (p[c] - p[b]);
          double angle = atan2(A ^ B, A * B);
          if (angle < 1e-8) angle += 2 * PI;
          min_angle = min(min_angle, angle);
          max_angle = max(max_angle, angle);
        }
        out << min_angle * 180 / PI << " " << max_angle * 180 / PI << endl;
      }
    }

    void solve(istream& in, ostream& out) {
        out.precision(6);
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
    UVA10445 solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}
