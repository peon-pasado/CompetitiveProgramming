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
    bool operator!=(P p) const { return !(*this == p);}
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

const int inf = 1.2e9;
const int maxn = 1010;
int lnk[maxn], rnk[maxn];
int components;

int get(int x) {return x==lnk[x]?x:lnk[x]=get(lnk[x]);}

void merge(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return;
    if (rnk[x]<rnk[y]) {
        swap(x, y);
    }
    rnk[x] += rnk[x]==rnk[y];
    lnk[y] = x;
    components--;
}

const long double pi = acos(-1);
void merge_tree(vector<Point<int>>& p, vector<pair<Point<int>, int>>& c, int idx) {
    Point<int> o = p[idx];
    int n = sz(p), m = sz(c);
    vector<pair<double, int>> angles;
    forn(i, n) if (p[i] != o) angles.psb({(p[i]-o).angle(), i});
    forn(i, m) {
        double angle = (c[i].first-o).angle();
        double delta = asin(c[i].second / (c[i].first-o).norm());
        rep(j, 0, 3) {
            angles.psb({angle - delta + (j-1) * 2 * pi, i - (j+1) * m});
            angles.psb({angle + delta + (j-1) * 2 * pi, i - (j+1) * m});
        }
    }
    sort(all(angles));
    set<ii> Q;
    trav(e, angles) {
        if (e.second < 0) {
            int idc = (m - abs(e.second) % m) % m, r = c[idc].second;
            ii q = {(c[idc].first-o).norm2() - r*r, e.second};
            if (Q.count(q)) Q.erase(q);
            else Q.insert(q);
        } else if (Q.empty() || (p[e.second] - o).norm2() < (Q.begin())->first) {
            merge(idx, e.second);
        }
    }
}

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int n, m;
        in >> n >> m;
        vector<Point<int>> p(n);
        vector<pair<Point<int>, int>> c(m);
        forn(i, n) in >> p[i];
        forn(i, m) in >> c[i].first >> c[i].second;
        components = n;
        forn(i, n) rnk[lnk[i]=i] = 0;
        forn(i, n) merge_tree(p, c, i);
        out << components - 1 << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        in >> test_number;
        forn(tc, test_number) {
            //out << "Case #" << tc+1 << ": ";
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