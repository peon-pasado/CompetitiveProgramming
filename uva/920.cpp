/**
 * @author Miguel Mini
 * @tag sweep_line, geometry
 * @idea 
 *      - geometry tools application.
 * @complexity O(n\log n)
 */ 
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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

int add(int a, int b, int m = mod) {
    return a + b < m ? a + b : a + b - m;
}

int mul(ll a, ll b, int m = mod) {
    return a * b % m;
}

int ex(int a, int b, int m = mod) {
    int r;
    for (r=1; b>0; b/=2) {
        if (b&1) r = mul(r, a, m);
        a = mul(a, a, m);
    }
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
    T cross(P other) const { return (*this) ^ other; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
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

template <class T>
struct Segment
{
    Point<T> a, ab;
    bool isLine;
    Segment() {}
    Segment(Point<T> a, Point<T> b, bool isLine = false) : a(a), ab(b - a), isLine(isLine) {}
    Point<T> b() { return a + ab; }
    int intercept(Segment q, Point<T> &res)
    {
        enum type
        {
            NONE = 0,
            ONE,
            IN
        };
        T s = ab ^ q.ab;
        if (s == 0)
        { //parallel
            if (((q.a - a) ^ ab) == 0)
            { //same line
                if (q.isLine || isLine)
                    return IN; //una incluye a la otra
                auto la = a, lb = b();
                auto ra = q.a, rb = q.b();
                if (la > lb)
                    swap(la, lb);
                if (ra > rb)
                    swap(ra, rb);
                res = max(la, ra);
                return min(lb, rb) - max(la, ra) >= Point<T>(0, 0);
            }
            return 0;
        }
        T t1 = q.ab ^ (a - q.a);
        T t2 = ab ^ (q.a - a);
        if (s > 0)
            t2 = -t2;
        if (s < 0)
            t1 = -t1, s = -s;
        bool r1 = (0 <= t1 && t1 <= abs(s)) || isLine;
        bool r2 = (0 <= t2 && t2 <= abs(s)) || q.isLine;
        res = a + t1 * ab / s; //need double
        return (r1 && r2) ? ONE : NONE;
    }
    double dist(Point<T> p)
    {
        if (!isLine)
        {
            if ((p - a) * ab <= 0)
                return p.dist(a);
            if ((p - b()) * ab >= 0)
                return p.dist(b());
        }
        return abs((p - a) ^ ab) / ab.norm();
    }
    double dist(Segment p)
    {
        Point<T> r;
        if (intercept(p, r))
            return 0;
        if (isLine && p.isLine)
            return abs((ab ^ (p.a - a))) / ab.norm();
        double d1 = min(p.dist(a), p.dist(b()));
        double d2 = min(dist(p.a), dist(p.b()));
        if (isLine)
            return d2;
        if (p.isLine)
            return d1;
        return min(d1, d2);
    }
    Point<T> closest(Point<T> p)
    {
        if (!isLine)
        {
            if ((p - a) * ab <= 0)
                return a;
            if ((p - b()) * ab >= 0)
                return b();
        }
        return ab * (ab * (p - a)) / (ab * ab) + a;
    }
};

const int inf = 1.2e9;

struct Solver {
    void solve_one(istream &in, ostream &out) {
        int n;
        in >> n;
        vector<Point<double>> p(n);
        forn(i, n) in >> p[i];
        sort(rall(p));
        double y = 0;
        double length = 0;
        rep(i, 0, n) {
            if (y >= p[i].y) continue;
            Point<double> t;
            Segment<double>(p[i], p[i-1])
                .intercept(Segment<double>(Point<double>(-1e9, y), Point<double>(1e9, y)), t);
            length += p[i].dist(t);
            y = p[i].y;
        }
        out << length << '\n';
    }
    void solve(istream &in, ostream &out) {
        out.precision(2);
        out << fixed;
        int test_number = 1;
        in >> test_number;
        forn(tc, test_number) {
            //out << "Case #" << tc+1 << ": ";
            solve_one(in, out);
        }
    }
};

int main() {
    Solver solver;
    if (!file_base.empty()) {
        ifstream in(file_base + ".in");
        ofstream out(file_base + ".out");
        in.exceptions(in.failbit);
        solver.solve(in, out);
    } else {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}