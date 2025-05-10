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

const int inf = 1.2e9;

template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    int c;
    Point(T x = 0, T y = 0, int c = 0) : x(x), y(y), c(c) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator>(P p) const { return p < *this; }
    bool operator<=(P p) const { return !(*this > p); }
    bool operator>=(P p) const { return !(*this < p); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P other) const { return P(x + other.x, y + other.y, c); }
    P operator-(P other) const { return P(x - other.x, y - other.y, c); }
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

template <typename T>
bool isAbove(Point<T> const &iPoint)
{
    return (iPoint.y > 0) || (iPoint.y == 0 && iPoint.x > 0);
}

template <typename T>
bool projectiveOrder(Point<T> const &iLeft, Point<T> const &iRight) {
    bool temp = isAbove(iLeft) == isAbove(iRight);
    T ori = iLeft ^ iRight;
    if (temp) {
        if (ori < 0) return 1; 
        if (ori > 0) return 0;
        if (isAbove(iLeft)) return iLeft * iLeft < iRight * iRight;
        else return iLeft * iLeft > iRight * iRight;
    } else {
        if (ori < 0) return 0;
        if (ori > 0) return 1;
        return isAbove(iLeft) > isAbove(iRight);
    }
}

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int n;
        in >> n;
        if (n == 0) return 1;
        vector<Point<ll>> p(n);
        forn(i, n) in >> p[i] >> p[i].c;
        auto cnt = [&](vector<Point<ll>>& p, Point<ll> o) {
            vector<Point<ll>> translated_p;
            forn(i, sz(p)) if (!(p[i] == o)) {
                translated_p.emb(p[i] - o);
            }
            sort(all(translated_p), projectiveOrder<ll>);
            int n_points[2][2] = {0};
            forn(i, sz(translated_p)) {
                bool is_a = isAbove(translated_p[i]);
                n_points[is_a][translated_p[i].c]++;
            }
            auto get = [&n_points]()->int {
                return max(n_points[0][0] + n_points[1][1], 
                            n_points[1][0] + n_points[0][1]);
            };
            int ans = get();
            forn(i, sz(translated_p)) {
                int j = i, cnt=1;
                while (j < sz(translated_p) && (translated_p[i] ^ translated_p[j]) == 0) {
                    bool is_a = isAbove(translated_p[j]);
                    n_points[is_a][translated_p[j++].c]--;
                    cnt++;
                }
                ans = max(ans, get() + cnt);
                j = i;
                while (j < sz(translated_p) && (translated_p[i] ^ translated_p[j]) == 0) {
                    bool is_a = isAbove(translated_p[j]);
                    n_points[!is_a][translated_p[j++].c]++;
                }
                i = j-1;
            }
            return ans;
        };
        int ans = 0;
        forn(i, sz(p)) ans = max(ans, cnt(p, p[i]));
        out << ans << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1e9;
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