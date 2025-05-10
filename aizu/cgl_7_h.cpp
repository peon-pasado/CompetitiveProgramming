#include <bits/stdc++.h>
#define sz(v) ((int)v.size())
#define double long double
using namespace std;

// Redefine epsilon and infinity as necessary. Be mindful of precision errors.
const double eps = 1e-12, inf = 1e9; 

template<typename T>
struct Point {
    using P = Point;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}

    template<class U>
    explicit operator Point<U> () const {return Point<U>(x, y);}

    P operator+(P other) const {return P(x+other.x, y+other.y);}
    P operator-(P other) const {return P(x-other.x, y-other.y);}
    P operator*(const T& c) const {return P(x*c, y*c);}
    P operator/(const T& c) const {return P(x/c, y/c);}
    
    friend T dot(const P& p, const P& q) {return p.x * q.x + p.y * q.y;}
    friend T ccw(const P& p, const P& q) {return p.x * q.y - p.y * q.x;} 
    friend P perp(const P& p) {return P(-p.y, p.x);}
    friend double norm(const P& p) {return sqrtl(dot(p, p));}
    friend double dist(const P& p, const P& q) {return norm(p-q);}
    friend double angle(const P& p) {return atan2l(p.y, p.x);}
    friend istream& operator>>(istream& is, P& other) {return is >> other.x >> other.y;}
    friend ostream& operator<<(ostream& os, const P& other) {return os << other.x << " " << other.y;}

    bool operator<(const P& p) const {return x < p.x || (x == p.x && y < p.y);}
    bool operator>(const P& p) const {return p < *this;}
    bool operator==(const P& p) const {return x == p.x && y == p.y;}
};
//given a circle(c, r) and a line(a, b), obtain intersection if exists.
pair<Point<double>, Point<double>> intersection_CL(Point<double> c, double r, Point<double> a, Point<double> b) {
    if (a == c) swap(a, b);
    Point<double> v(b - a);
    Point<double> A(c - a);
    double norm_v = dot(v, v);
    double X = dot(v, A);
    double Y = ccw(v, A);
    double d = sqrtl(r * r * norm_v - Y * Y); 
    Point<double> r1 = a + v * (X + d) / norm_v;
    Point<double> r2 = a + v * (X - d) / norm_v;
    if (r2 < r1) swap(r1, r2);
    return {r1, r2};
}

double dist_PS(Point<double> p, Point<double> q, Point<double> c) {
    if (dot(c - p, q - p) <= 0) return dist(c, p);
    if (dot(c - q, q - p) >= 0) return dist(c, q);
    return fabs(ccw(c - p, q - p)) / norm(q - p);
}


double angle_between(Point<double> p, Point<double> q) {
    return atan2l(ccw(p, q), dot(p, q));
}

double area_inter_CT(Point<double> p, Point<double> q, Point<double> c, double r) {
    double area = ccw(p, q);
    int sign = 1;
    if (area < 0) {
        area = fabs(area);
        sign = -1;
        swap(p, q);
    }
    if (fabs(area) < eps) return 0;
    double np = norm(p);
    double nq = norm(q);
    double ans = 0;
    if (np <= r && nq <= r) {
        ans = area;
    } else if (min(np, nq) < r && max(np, nq) >= r) {
        auto e = intersection_CL(c, r, p, q);
        auto t = e.first;
        auto u = e.second;
        if (fabs(dist(p, t) + dist(q, t) - dist(p, q)) < eps) {
            u = t;
        }
        if (np >= nq) {
            ans += angle_between(p, u) * r * r;
            ans += ccw(u, q);
        } else {
            ans += angle_between(u, q) * r * r;
            ans += ccw(p, u);
        }
    } else if (dist_PS(p, q, c) >= r) {
        ans = angle_between(p, q) * r * r;
    } else {
        auto e = intersection_CL(c, r, p, q);
        auto t = e.first;
        auto u = e.second;
        if (dist(p, t) > dist(p, u)) swap(t, u);
        ans += angle_between(p, t) * r * r;
        ans += ccw(t, u);
        ans += angle_between(u, q) * r * r;
    }
    return sign * ans / 2;
}

int main() {
    cout<<setprecision(8)<<fixed;
    Point<double> c(0, 0);
    int n, r;
    cin>>n>>r;
    vector<Point<double>> p(n);
    for (int i=0; i<n; ++i) cin>>p[i];
    double ans = 0;
    for (int i=0; i<n; ++i) {
        ans += area_inter_CT(p[i], p[(i+1)%n], c, r);
    }
    cout << fabs(ans) << '\n';
    return 0;
}