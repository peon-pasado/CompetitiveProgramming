/**
 *	@author Miguel Mini
 *  @tag geometry, dijkstra
 *  @idea
 *      - distance between two
 *      circles is max(0, dist(center_i, center_j) - radius_i - radius_j)
 *
 *      - we can run dijkstra O(n^2) from circle ((x_s, y_s), 0) to
 *      ((x_t, y_t), 0).
**/

#include <bits/stdc++.h>
using namespace std;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
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

const int maxn = 1010;
double dist[maxn][maxn];
double dd[maxn];
using ll = long long;
bool vis[maxn];

int main() {
    Point<double> s, t;
    cin >> s >> t;
    int n;
    cin >> n;
    n += 2;
    vector<Point<double>> c(n);
    c[0] = s; c[1] = t;
    vector<int> r(n);
    for (int i = 2; i < n; ++i) {
        cin >> c[i] >> r[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = max(0.d, c[i].dist(c[j]) - r[i] - r[j]);
        }
    }
    for (int i = 0; i < n; ++i) dd[i] = 1e18;
    dd[0] = 0;
    for (int i = 0; i < n-1; ++i) {
        double d = 1e18;
        int x = -1;
        for (int j = 0; j < n; ++j) {
            if (!vis[j] && d > dd[j]) {
                x = j;
                d = dd[j];
            }
        }
        vis[x] = 1;
        for (int j = 0; j < n; ++j) {
            if (!vis[j] && d + dist[x][j] < dd[j]) {
                dd[j] = d + dist[x][j];
            }
        }
    }
    cout << setprecision(11) << fixed << dd[1] << endl;
    return 0;
}