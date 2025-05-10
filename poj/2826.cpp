#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#define S Segment
#define P Point
#define T double
using namespace std;
const double eps = 1e-9;

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
    bool r1 = (0 <= t1 && t1 <= s) || p.is_line;
    bool r2 = (0 <= t2 && t2 <= s) || q.is_line;
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
            return xa <= xb ? make_pair(1, xa) : make_pair(0, P(0, 0));
        } 
        return make_pair(0, P(0, 0));
    }
    T t1 = q.ab^(p.a - q.a);
    T t2 = p.ab^(p.a - q.a);
    if (s < 0) t1 = -t1, t2 = -t2, s = -s;
    bool r1 = (0 <= t1 && t1 <= s) || p.is_line;
    bool r2 = (0 <= t2 && t2 <= s) || q.is_line;
    return make_pair(r1 && r2, p.a + p.ab * t1 / s);
}


struct cmp {
    P zero;
    cmp(P zero): zero(zero) {}
    bool operator()(const P& p, const P& q) { //no dos puntos en el rayo desde zero.
        return p > zero == q > zero ? (p - zero).cross(q - zero) > 0 : p > zero;
    }
};

int main() {
    cout << setprecision(2) << fixed;
    int t;
    cin>>t;
    while (t--) {
        P p, q, r, s;
        cin>>p>>q>>r>>s;
        if (p.y < q.y) swap(p, q);
        if (r.y < s.y) swap(r, s);
        S s1(p, q), s2(r, s);
        T ymax = min(s1.a.y, s2.a.y);
        S s3(P(-10000, ymax), P(10000, ymax));
        pair<bool, P> A = intersect(s1, s2);
        pair<bool, P> B = intersect(s1, s3);
        pair<bool, P> C = intersect(s2, s3);
        

        S s4 = S(s1.a, s1.a + P(0, 10000));
        S s5 = S(s2.a, s2.a + P(0, 10000));

        bool ok = 1;
        if (intersect_test(s4, s2) || intersect_test(s5, s1)) {
            ok = 0;
        }

        if (ok && A.first && B.first && C.first) {
            double area = A.second.cross(B.second) 
                        + B.second.cross(C.second) 
                        + C.second.cross(A.second); 
            cout << abs(area) * 0.5 + eps << '\n';
        } else {
            cout << 0. << '\n';
        }
    }
    return 0;
} 