#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>
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

struct Obstacle {
    Point p;
    double y;
};

double get_x(P p, P q, double y) {
    // X        y       1
    // p.x     p.y      1
    // q.x     q.y      1

    return (y * (q.x - p.x) + (p ^ q)) / (q.y - p.y); 
}

int main() {
    cout<<setprecision(2)<<fixed;
    Obstacle home, property;
    while (cin>>home.p>>home.y, abs(home.p.x+home.p.y+home.y) > eps) {
        cin>>property.p>>property.y;
        int n;
        cin>>n;
        vector<Obstacle> obstacles(n);
        vector<P> segments;
        for (int i=0; i<n; ++i) {
            cin>>obstacles[i].p>>obstacles[i].y;
            if (obstacles[i].y <= property.y || obstacles[i].y >= home.y) continue;
            double a = get_x(P(home.p.y, home.y), P(obstacles[i].p.x, obstacles[i].y), property.y);
            double b = get_x(P(home.p.x, home.y), P(obstacles[i].p.y, obstacles[i].y), property.y);
            a = max(a, property.p.x);
            b = min(b, property.p.y);
            if (a >= b) continue;
            segments.push_back(P(a, b));
        }
        sort(segments.begin(), segments.end());
        double max_s = 0.;
        double r = property.p.x;
        for (int i=0; i<segments.size(); ++i) {
            if (segments[i].x <= r) r = max(r, segments[i].y);
            else {
                max_s = max(max_s, segments[i].x  - r);
                r = segments[i].y;
            }
        }
        max_s = max(max_s, property.p.y - r);
        if (max_s < eps) cout << "No View" << '\n';
        else cout << max_s << '\n';
    }
    return 0;
}