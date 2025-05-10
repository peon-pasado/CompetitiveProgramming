#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define S Segment
#define P Point
#define T long long
using namespace std;
const double eps = 1e-7;


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

struct cmp {
    P zero;
    cmp(P zero): zero(zero) {}
    bool operator()(const P& p, const P& q) { //no dos puntos en el rayo desde zero.
        return p > zero == q > zero ? (p - zero).cross(q - zero) > 0 : p > zero;
    }
};

bool test(S s, P b[4]) {
    bool is_in[2] = {1, 1};
    for (int i=0; i<4; ++i) {
        S sb = S(b[i], b[(i+1)&3]);
        if (intersect_test(s, sb)) return 1;
        is_in[0] = is_in[0] && (sb.ab.cross(s.a - sb.a) >= 0);
        is_in[1] = is_in[1] && (sb.ab.cross(s.b() - sb.a) >= 0);
    }
    return is_in[0] || is_in[1];
}

int main() {
    int n;
    cin>>n;
    while (n--) {
        P p, q, b[4];
        cin>>p>>q>>b[0]>>b[2];
        if (b[0].x > b[2].x) swap(b[0].x, b[2].x);
        if (b[0].y < b[2].y) swap(b[0].y, b[2].y);
        b[1] = P(b[0].x, b[2].y);
        b[3] = P(b[2].x, b[0].y);
        cout << (test(S(p, q), b) ? 'T' : 'F') << '\n';
    }
    return 0;
}