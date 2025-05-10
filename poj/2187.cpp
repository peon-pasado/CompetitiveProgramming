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
//#include <tuple>
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
#define ll long long
const int mod = 1e9 + 7;
const string file_base = "";

int add(int a, int b, int m = mod) {
    return a + b < m ? a + b : a + b - m;
}

int mul(ll a, ll b, int m = mod) {
    return a * b % m;
}

int ex(int a, int b, int m = mod) {
    int r=1;
    for (; b>0; b/=2, a=mul(a,a,m))
        if (b&1) r = mul(r, a, m);
    return r;
}

const int inf = 1.2e9;

template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return make_pair(x, y) < make_pair(p.x, p.y); }
    bool operator>(P p) const { return p < *this; }
    bool operator<=(P p) const { return !(*this > p); }
    bool operator>=(P p) const { return !(*this < p); }
    bool operator==(P p) const { return make_pair(x, y) == make_pair(p.x, p.y); }
    P operator+(P other) const { return P(x + other.x, y + other.y); }
    P operator-(P other) const { return P(x - other.x, y - other.y); }
    P operator*(T c) const { return P(x * c, y * c); }
    P operator/(T c) const { return P(x / c, y / c); }
    friend P operator*(T c, const P p) { return p * c; }
    T operator*(P other) const { return x * other.x + y * other.y; }
    T operator^(P other) const { return x * other.y - y * other.x; }
    T dot(P other) const { return (*this) * other; }
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

vector<Point<ll> > convex_hull(vector<Point<ll> > p) {
    sort(all(p));
    vector<Point<ll> > hull;
    for (int i = 0; i < sz(p); ++i) {
        while (sz(hull) >= 2 && hull[sz(hull)-2].ccw(hull.back(), p[i]) >= 0) {
            hull.pop_back();
        }
        hull.psb(p[i]);
    }
    int m = sz(hull);
    for (int i = sz(p)-2; i >= 0; --i) {
        while (sz(hull) >= m+1 && hull[sz(hull)-2].ccw(hull.back(), p[i]) >= 0) {
            hull.pop_back();
        }
        hull.psb(p[i]);
    }
    hull.pop_back();
    return hull;
}

int n;
int nxt(int i) {
    return i+1<n?i+1:0;
}

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        in >> n;
        vector<Point<ll> > p(n);
        forn(i, n) in >> p[i];
        vector<Point<ll> > ch = convex_hull(p);
        int i = 0, j = 0;
        forn(i, sz(ch)) if (ch[i].y >= ch[j].y) j = i;
        ll ans = (ch[i] - ch[j]).norm2();
        n = sz(ch); 
        while (i != n-1) {
            Point<ll> u = ch[nxt(i)] - ch[i];
            Point<ll> v = ch[nxt(j)] - ch[j];
            if ((u^v) < 0) j = nxt(j);
            else i = nxt(i);
            ans = max(ans, (ch[i] - ch[j]).norm2());
        }
        out << ans << endl;
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        //in >> test_number;
        forn(tc, test_number) {
            //out << "Case #" << tc+1 << ": ";
            if (solve_one(in, out)) break;
        }
    }
};

int main() {
    Solver solver;
    if (!file_base.empty()) {
        //ifstream in(file_base + ".in");
        //ofstream out(file_base + ".out");
        //in.exceptions(in.failbit);
        //solver.solve(in, out);
    } else {
        //cin.tie(nullptr)->sync_with_stdio(false);
        //cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}