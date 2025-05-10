#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <vector>
#define sz(c) ((int)c.size())
#define trav(it, c) for (auto it : c)
#define rep(var, begin, end) for (int var = begin; var < end; ++var)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(c) c.begin(), c.end()
#define rall(c) c.rbegin(), c.rend()
#define compress(c) (sort(all(c)), c.erase(unique(all(c)), c.end()))
#define emb emplace_back
#define psb push_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int mod = 1e9 + 7;
const string file_base = "";

int add(int a, int b, int m = mod)
{
    return a + b < m ? a + b : a + b - m;
}

int mul(ll a, ll b, int m = mod)
{
    return a * b % m;
}

int ex(int a, int b, int m = mod)
{
    int r = 1;
    for (; b > 0; b /= 2, a = mul(a, a, m))
        if (b & 1)
            r = mul(r, a, m);
    return r;
}

template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator>(P p) const { return p < *this; }
    bool operator<=(P p) const { return !(*this > p); }
    bool operator>=(P p) const { return !(*this < p); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P other) const { return P(x + other.x, y + other.y); }
    P operator-(P other) const { return P(x - other.x, y - other.y); }
    P operator*(T c) const { return P(x * c, y * c); }
    P operator/(T c) const { return P(x / c, y / c); }
    friend P operator*(T c, const P p) { return p * c; }
    T operator*(P other) const { return x * other.x + y * other.y; }
    T operator^(P other) const { return x * other.y - y * other.x; }
    T dot(P other) const { return (*this) * other; }
    T dot(P a, P b) const { return (a - *this) * (b - *this); }
    T cross(P other) const { return (*this) ^ other; }
    T ccw(P a, P b) const { return (a - *this).cross(b - *this); }
    T norm2() const { return x * x + y * y; }
    double norm() const { return sqrt((double)norm2()); }
    double dist(P p) { return (p - (*this)).norm(); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    double angle(P p) const { return atan2(*this ^ p, *this * p); } //[-pi, pi]
    P unit() const { return *this / norm(); }                       // makes dist()=1
    P perp() const { return P(-y, x); }                             // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    P rotate(Point other, double a) const
    {
        return (*this - other).rotate(a) + other;
    }
    friend istream &operator>>(istream &is, P &other)
    {
        return is >> other.x >> other.y;
    }
    friend ostream &operator<<(ostream &os, P other)
    {
        return os << other.x << " " << other.y;
    }
};

const int inf = 1.2e9;

struct Solver
{
    bool solve_one(istream &in, ostream &out)
    {
        int n;
        in >> n;
        vector<Point<double>> p(n);
        forn(i, n) in >> p[i];
        auto f = [&](double alpha) { 
            double l1 = 1e18, l2 = -1e18;
            double h1 = 1e18, h2 = -1e18;
            forn(i, sz(p)) {
                Point<double> v = p[i].rotate(alpha);
                l2 = max(l2, v.x);
                l1 = min(l1, v.x);
                h2 = max(h2, v.y);
                h1 = min(h1, v.y);
            }
            double b = max(l2-l1, h2-h1);
            return b*b;
        };
        double lo = 0, hi = acos(-1);
        for (int i = 0; i < 80; ++i) {
            double m1 = lo + (hi - lo) / 3;
            double m2 = lo + 2 * (hi - lo) / 3;
            if (f(m1) < f(m2)) hi = m2;
            else lo = m1;            
        }
        out << f(lo) << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out)
    {
        out.precision(2);
        out << fixed;
        int test_number = 1;
        in >> test_number;
        forn(tc, test_number)
        {
            //out << "Case #" << tc+1 << ": ";
            if (solve_one(in, out))
                break;
        }
    }
};

int main()
{
    Solver solver;
    if (!file_base.empty())
    {
        ifstream in(file_base + ".in");
        ofstream out(file_base + ".out");
        in.exceptions(in.failbit);
        solver.solve(in, out);
    }
    else
    {
        cin.tie(nullptr)->sync_with_stdio(false);
        //cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}