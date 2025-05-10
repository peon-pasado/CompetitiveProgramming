#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#define S Segment
#define P Point
#define T double
using namespace std;
const double eps = 1e-8;

struct Point {
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P other) const {return x<other.x || ((x-other.x)<eps && y<other.y);}
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
            return max(la, ra) < min(lb, rb);
        } 
        return 0;
    }
    T t1 = q.ab^(p.a - q.a);
    T t2 = p.ab^(q.a - p.a);
    if (s > 0) t2 = -t2;
    if (s < 0) t1 = -t1, s = -s;
    bool r1 = (0 <= t1 && t1 <= s) || p.is_line;
    bool r2 = (0 <= t2 && t2 <= s) || q.is_line;
    return r1 && r2;
}

struct cmp {
    bool operator()(const P& p, const P& q) {
        P zero = P(50, 50);
        if (p > zero == q > zero) return (p - zero).cross(q - zero) > 0;
        return p > zero;
    }
};

int main() {
    int n;
    cin>>n;
    vector<S> segments;
    for (int i=0; i<n; ++i) {
        P p, q;
        cin>>p>>q;
        segments.push_back(S(p, q));
    }
    segments.push_back(S(P(0, 0), P(100, 0)));
    segments.push_back(S(P(100, 0), P(100, 100)));
    segments.push_back(S(P(100, 100), P(0, 100)));
    segments.push_back(S(P(0, 100), P(0, 0)));
    P s;
    cin>>s;
    vector<P> order;
    for (int i=0; i<segments.size(); ++i) {
        order.push_back(segments[i].a);
        order.push_back(segments[i].b());
    }
    sort(order.begin(), order.end(), cmp());
    int ans = n + 1;
    for (int i=0; i<order.size(); ++i) {
        P p = order[i];
        P q = order[i+1==order.size()?0:i+1];
        P mid = (p + q) * 0.5;
        S query_segment(s, mid);
        int query_ans = 0;
        for (int j=0; j<segments.size(); ++j) {
            query_ans += intersect_test(query_segment, segments[j]);
        }
        ans = min(ans, query_ans);
    }
    cout << "Number of doors = " << ans << '\n';
    return 0;
}