#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#define S Segment
#define P Point
#define T double
using namespace std;
const double eps = 1e-8;


struct Point {
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P other) const {return x<other.x || (abs(x-other.x)<eps && y<other.y);}
    bool operator>(P other) const {return other < *this;}
    bool operator==(P other) const {return abs(x-other.x)<eps && abs(y-other.y)<eps;}
    bool operator<=(P other) const {return *this == other || *this < other;}
    bool operator>=(P other) const {return other <= *this;}
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

struct Segment {
    P a, ab;
    bool is_line;
    Segment() {}
    Segment(P a, P b, bool is_line=false):
            a(a), ab(b - a), is_line(is_line) {}
    P b() {return a + ab;}
};

bool intersect_test(S p, S q) {
    T s = p.ab ^ q.ab;
    if (abs(s) < eps) {
        if (abs((q.a - p.a) ^ p.ab) < eps) { 
            if (p.is_line || q.is_line) return 1;
            P la = p.a, lb = p.b();
            P ra = q.a, rb = q.b();
            if (la > lb) swap(la, lb);
            if (ra > rb) swap(ra, rb);
            return max(la, ra) <= min(lb, rb);
        } 
        return 0;
    }
    T t1 = q.ab^(p.a - q.a);
    T t2 = p.ab^(p.a - q.a);
    if (s < 0) t1 = -t1, t2 = -t2, s = -s;
    bool r1 = (-eps <= t1 && t1 <= s + eps) || p.is_line;
    bool r2 = (-eps <= t2 && t2 <= s + eps) || q.is_line;
    return r1 && r2;
}

pair<bool, P> intersect(S p, S q) {
    T s = p.ab ^ q.ab;
    if (abs(s) < eps) {
        if (abs((q.a - p.a) ^ p.ab) < eps) { 
            if (p.is_line || q.is_line) return make_pair(1, p.a);
            P la = p.a, lb = p.b();
            P ra = q.a, rb = q.b();
            if (la > lb) swap(la, lb);
            if (ra > rb) swap(ra, rb);
            P xa = max(la, ra);
            P xb = min(lb, rb);
            return make_pair(xa < xb, xa);
        } 
        return make_pair(0, P(0, 0));
    }
    T t1 = q.ab^(p.a - q.a);
    T t2 = p.ab^(p.a - q.a);
    if (s < 0) t1 = -t1, t2 = -t2, s = -s;
    bool r1 = (0 <= t1 && t1 <= s) || p.is_line;
    bool r2 = (0 <= t2 && t2 <= s) || q.is_line;
    //cout << "ts: " << t1 / s << " " << t2 / s << endl;
    return make_pair(r1 && r2, p.a + p.ab * t1 / s);
}

struct cmp {
    P zero;
    cmp(P zero): zero(zero) {}
    bool operator()(const P& p, const P& q) { //no dos puntos en el rayo desde zero.
        return p > zero == q > zero ? (p - zero).cross(q - zero) > 0 : p > zero;
    }
};

P points[21];
int n;

double solve(P p, P q) {
    S s(p, q, 1);
    for (int i=0; i<n; ++i) {
        if (intersect_test(s, S(points[i], P(points[i].x, points[i].y-1)))) continue;
        if (i == 0) return points[i].x; T ans = points[i-1].x;
        pair<bool, P> q1 = intersect(s, S(points[i-1], points[i]));
        if (q1.first) ans = max(ans, q1.second.x);
        pair<bool, P> q2 = intersect(s, S(P(points[i-1].x, points[i-1].y-1), P(points[i].x, points[i].y-1)));
        if (q2.first) ans = max(ans, q2.second.x);
        return ans;
    }
    return points[n-1].x;
}

int main() {
    //cin.tie(0)->sync_with_stdio(0);
    //cout << setprecision(2) << fixed;
    while (scanf("%d", &n), n) {
        for (int i=0; i<n; ++i) {
            scanf("%lf%lf", &points[i].x, &points[i].y);
        }
        double ans = points[0].x;
        for (int i=0; i<n; ++i) {
            for (int j=i+1; j<n; ++j) {
                P p = points[i];
                P q = points[j];
                q.y -= 1;
                ans = max(ans, solve(p, q));
                q.y += 1;
                p.y -= 1;
                ans = max(ans, solve(p, q));
                if (abs(ans - points[n-1].x) < eps) break; 
            }
            if (abs(ans - points[n-1].x) < eps) break; 
        }
        if (abs(ans - points[n-1].x) < eps) puts("Through all the pipe.");
        else printf("%.2lf\n", ans);
    }
    return 0;
}