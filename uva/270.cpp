#include <algorithm>
#include <bitset>
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

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

struct Solver {
    string line;

    void normalize(Point<ll>& p) {
        auto g = gcd(abs(p.x), abs(p.y));
        p = p / g;
        if (p < Point<ll>(0, 0)) 
            p = -1 * p;
    }

    bool solve_one(istream &in, ostream &out) {
        vector<Point<ll>> p;
        while (getline(cin, line) && line != "") {
            istringstream ss(line);
            Point<ll> r;
            ss >> r;
            p.psb(r);
        }
        int n = sz(p);
        int ans = 1;
        forn(i, n) {
            vector<Point<ll>> v;
            rep(j, i+1, n) {
                Point<ll> d = p[j] - p[i];
                normalize(d);
                v.psb(d);
            }
            ans = max(ans, 1+(!v.empty()));
            sort(all(v));
            int cnt = 1;
            rep(i, 1, sz(v)) {
                if (v[i] == v[i-1]) cnt++;
                else cnt = 1;
                ans = max(ans, cnt + 1);
            }
        }
        out << ans << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        in >> test_number;
        // getchar();
        getline(cin, line);
        getline(cin, line);
        forn(tc, test_number) {
            //out << "Case #" << tc+1 << ": ";
            if (tc) out << '\n';
            if (solve_one(in, out)) break;
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
        //cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}