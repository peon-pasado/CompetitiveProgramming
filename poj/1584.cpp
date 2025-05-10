#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#define S Segment
#define P Point
#define T double
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

double dist(S s, P p) {
    if (!s.is_line) {
        if ((p - s.a) * s.ab <= 0) return p.dist(s.a);
        if ((p - s.b()) * s.ab >= 0) return p.dist(s.b());
    }
    return abs((p - s.a) ^ s.ab) / s.ab.norm();
}

struct cmp {
    P zero;
    cmp(P zero): zero(zero) {}
    bool operator()(const P& p, const P& q) { //no dos puntos en el rayo desde zero.
        return p > zero == q > zero ? (p - zero).cross(q - zero) > 0 : p > zero;
    }
};

bool is_convex(vector<P> p) {
    int n = p.size();
    for (int i=0; i<n; ++i) {
        int l = (i+n-1)%n;
        int r = (i+1)%n;
        if ((p[i] - p[l]).cross(p[r] - p[l]) > 0) {
            return 0;
        }
    }
    return 1;
}

double sign_area(vector<P> p) {
    int n = p.size();
    double res = 0.;
    for (int i=0;i<n; ++i) {
        res += p[i].cross(p[(i+1)%n]);
    }
    return res / 2;
}

bool check(vector<P> p, P c, double R) {
    int n = p.size();
    for (int i=0; i<n; ++i) {
        if (dist(S(p[i], p[(i+1)%n]), c) < R) {
            return 0;
        }
    }
    return 1;
}
 
int widing(P p, S s) {
    if (s.a.y <= p.y) {
        if (s.b().y > p.y) {
            return (s.ab ^ (p - s.a)) > 0;
        }
    } else {
        if (s.b().y <= p.y) {
            return (s.ab ^ (p - s.a)) < 0 ? -1 : 0;
        }
    }
    return 0;
}

bool inside(vector<P> p, P c) {
    int n = p.size();
    int sum = 0;
    for (int i=0; i<n; ++i) {
        int nxt = (i + 1) % n;
        sum += widing(c, S(p[i], p[nxt]));
    }
    return sum != 0;
}

int main() {
    int n;
    while (cin>>n, n>=3) {
        double pegR;
        P pegp;
        cin>>pegR>>pegp;
        vector<P> polyg(n);
        for (int i=0; i<n; ++i) cin>>polyg[i];
        if (sign_area(polyg) > 0) {
            reverse(polyg.begin(), polyg.end());
        }
        if (!is_convex(polyg)) {
            cout << "HOLE IS ILL-FORMED" << '\n';
        } else if (inside(polyg, pegp) && check(polyg, pegp, pegR)) {
            cout << "PEG WILL FIT" << '\n';   
        } else {
            cout << "PEG WILL NOT FIT" << '\n';
        }
    }
    return 0;
}