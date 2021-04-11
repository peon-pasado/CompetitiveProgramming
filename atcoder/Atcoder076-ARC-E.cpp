/**
 * @author Miguel Mini
 * @tag sweep_circle, stack
 * @idea
 *      - we can see that if there are 
 *      no pairs of points such that 
 *      both are on the edges, we can 
 *      progressively connect the points, 
 *      note that by doing this no point 
 *      is enclosed.
 * 
 *      - edge-points are the problem, and
 *      fixed a start, this sequence should
 *      by a balanced parentheses, we can
 *      sort points by angle and use an stack
 *      to verify this condition. 
 *      
 * @complexity O(n \log n)
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>
#include <fstream>
#include <stack>
#include <queue>
#include <math.h>
#include <tuple>
#include <climits>
#define sz(x) ((int)x.size())
#define trav(v, x) for (auto v : x)
#define reu(x, y, z) for (int x=y; x<z; ++x)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define eb emplace_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int mod = 1e9 + 7;

int add(int a, int b, int m=mod) {
    return a+b < m? a+b : a+b-m;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%m;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (b > 0) {
        if (b&1) r = mul(r, a, m);
        a = mul(a, a, m);
        b >>= 1;
    }
    return r;
}

const int inf = INT_MAX / 2.2;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const {return tie(x, y) < tie(p.x, p.y);}
    bool operator>(P p) const {return p < *this;}
    bool operator<=(P p) const {return !(*this>p);}
    bool operator>=(P p) const {return !(*this<p);}
    bool operator==(P p) const {return tie(x, y)==tie(p.x, p.y);}
    P operator+(P other) const {return P(x+other.x, y+other.y);}
    P operator-(P other) const {return P(x-other.x, y-other.y);}
    P operator*(T c) const {return P(x*c, y*c);}
    P operator/(T c) const {return P(x/c, y/c);}
    friend P operator*(T c, const P p) {return p*c;}
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
    double angle(P p) const {return atan2(*this ^ p, *this * p);} //[-pi, pi]
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
      return os << other.x << " " << other.y;}
};

template<typename T>
bool isAbove(Point<T> const& iPoint) {
    return (iPoint.y > 0) || (iPoint.y == 0 && iPoint.x > 0);
}

template<typename T>
bool projectiveOrder(Point<T> const& iLeft, Point<T> const& iRight) {
    return (isAbove(iLeft) == isAbove(iRight)) ^ ((iLeft ^ iRight) > 0);
}

const int maxn = 2e5 + 10;

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
        int r, c, n;
        in >> r >> c >> n;
        vector<Point<ll>> p(2*n);
        for (int i = 0; i < n; ++i) {
            in >> p[2 * i] >> p[2 * i + 1];
        }
        auto border = [&](int i)->bool {
            return p[i].x == 0 || p[i].x == r || p[i].y == 0 || p[i].y == c;
        };
        vector<int> can;
        for (int i = 0; i < n; ++i) {
            if (border(2 * i) && border(2 * i + 1)) {
                can.push_back(2 * i);
                can.push_back(2 * i + 1);
            }
        }
        Point<ll> center(r, c);
        for (int i = 0; i < 2 * n; ++i) {
            p[i] = 2 * p[i] - center;
        }
        auto pivot = partition(all(can), [&](int i) {
            return isAbove(p[i]); 
        });
        auto cmp = [&](int i, int j) {
           return (p[i] ^ p[j]) < 0;
        };
        sort(can.begin(), pivot, cmp);
        sort(pivot, can.end(), cmp);
        stack<int> s;
        vector<bool> inStack(n);
        if (!can.empty()) {
            for (int i = 0; i < 2 * n; ++i) {
                int ps = can[i % can.size()];
                if (inStack[ps / 2]) {
                    if (s.top() == ps / 2) {
                        s.pop();
                        inStack[ps / 2] = 0;
                    } else {
                        out << "NO" << '\n';
                        return;
                    }
                } else {
                    inStack[ps / 2] = 1;
                    s.push(ps / 2);
                }
            }
        }
        out << "YES" << '\n';
    }
    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        //in >> testNumber;
        rep(tc, testNumber) {
            //out << "Case #" << tc+1 << ": ";
            solveOne(in, out);
        }
    }
};

int main() {
    Solver solver;
    string file = "";
    if (!file.empty()) {
      ifstream in(file + ".in");
      ofstream out(file + ".out");
      in.tie(nullptr);
      in.exceptions(in.failbit);
      solver.solve(in, out);
    } else {
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);
      solver.solve(cin, cout);
    }
    return 0;
}