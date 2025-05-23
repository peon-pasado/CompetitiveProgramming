/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const {return tie(x, y) < tie(p.x, p.y);}
    bool operator==(P p) const {return tie(x, y)==tie(p.x, p.y);}
    P operator+(P other) const {return P(x+other.x, y+other.y);}
    P operator-(P other) const {return P(x-other.x, y-other.y);}
    P operator*(T c) const {return P(x*c, y*c);}
    P operator/(T c) const {return P(x/c, y/c);}
    friend T operator*(T c, const P p) {return p*c;}
    T operator*(P other) const {return x*other.x + y*other.y;}
    T operator^(P other) const {return x*other.y - y*other.x;}
    T dot(P other) const {return (*this)*other;}
    T cross(P other) const {return (*this)^other;}
    T cross(P a, P b) const {return (a-*this).cross(b-*this);}
    T norm2() const {return x*x + y*y;}
    double norm() const {return sqrt((double)norm2());}
    double dist(P p) {return (p-(*this)).norm();}
    // angle to x-axis in interval [-pi, pi]
    double angle() const {return atan2(y, x);}
    P unit() const {return *this/norm();} // makes dist()=1
    P perp() const {return P(-y, x);} // rotates +90 degrees
    P normal() const {return perp().unit();}
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
      return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));}
    P rotate(Point other, double a) const {
      return (*this-other).rotate(a) + other;}
    friend istream& operator>>(istream& is, P& other) {
      return is >> other.x >> other.y;}
    friend ostream& operator<<(ostream& os, P other) {
      return os << "(" << other.x << "," << other.y << ")";}
};

template<class T>
struct Segment {
    Point<T> a, ab;
    bool isLine;
    Segment() {}
    Segment(Point<T> a, Point<T> b, bool isLine=false):
            a(a), ab(b - a), isLine(isLine) {}
    Point<T> b() {return a + ab;}
    bool intercept(Segment q) {
      T s = ab^q.ab;
      if (s == 0) { //parallel
        if (((q.a - a)^ab) == 0) { //same line
          return (q.a.x <= b().x && a.x <= q.b().x
                 && q.a.y <= b().y && a.y <= q.b().y)
                 || q.isLine || isLine;
        }
        return 0;
      }
      T t1 = q.ab^(a - q.a);
      T t2 = ab^(q.a - a);
      if (s < 0) t1 = -t1;
      if (s > 0) t2 = -t2;
      bool r1 = (0 <= t1 && t1 <= abs(s)) || isLine;
      bool r2 = (0 <= t2 && t2 <= abs(s)) || q.isLine;
      return r1 && r2;
    }
    double dist(Point<T> p) {
      if (!isLine) {
        if ((p - a) * ab <= 0) return p.dist(a);
        if ((p - b()) * ab >= 0) return p.dist(b());
      }
      return abs((p - a) ^ ab) / ab.norm();
    }
    double dist(Segment p) {
      if (intercept(p)) return 0;
      if (isLine && p.isLine) return abs((ab ^ (p.a - a))) / ab.norm();
      double d1 = min(p.dist(a), p.dist(b()));
      double d2 = min(dist(p.a), dist(p.b()));
      if (isLine) return d2;
      if (p.isLine) return d1;
      return min(d1, d2);
    }
};

class UVA191 {
public:
    void solveOne(istream& in, ostream& out) {
      Point<int> A, B, R[2];
      in >> A >> B >> R[0] >> R[1];
      if (R[0].x > R[1].x) swap(R[0].x, R[1].x);
      if (R[0].y > R[1].y) swap(R[0].y, R[1].y);
      Segment<int> s(A, B);
      auto inside = [&](Point<int> p) {
        return R[0].x <= p.x && p.x <= R[1].x && R[0].y <= p.y && p.y <= R[1].y;
      };
      bool inter = inside(A) | inside(B);
      re(i, 0, 2) {
        Point<int> C = R[i];
        re(j, 0, 2) {
          Point<int> D = R[i];
          if (j == 0) D.x = R[i^1].x;
          if (j == 1) D.y = R[i^1].y;
          inter |= s.intercept(Segment<int>(C, D));
        }
      }
      out << (inter ? "T" : "F") << endl;
    }

    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        in >> testNumber;
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
    UVA191 solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}