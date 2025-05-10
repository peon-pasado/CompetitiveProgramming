#include <bits/stdc++.h>
#define sz(v) ((int)v.size())
using namespace std;

// Redefine epsilon and infinity as necessary. Be mindful of precision errors.
const long double eps = 1e-9, inf = 1e9; 

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

pair<Point<double>, Point<double>> intersect_CC(Point<double> c1, double r1, Point<double> c2, double r2) {
    Point<double> v(c2 - c1);
    double d = norm(v);
    double x = 0.5 * (d + (r1*r1 - r2*r2) / d);
    double t = sqrtl(r1*r1 - x*x);
    Point<double> i1 = c1 + (v * x + perp(v) * t) / d;
    Point<double> i2 = c1 + (v * x - perp(v) * t) / d;
    if (i2 < i1) swap(i1, i2);
    return make_pair(i1, i2);
}

double area_inter_CC(Point<double> c1, double r1, Point<double> c2, double r2) {
    double d = dist(c1, c2);
    if (d >= r1 + r2) return 0;
    if (r1 < r2) {
        swap(r1, r2);
        swap(c1, c2); //bah
    }
    if (d + r2 <= r1) {
        return acos(-1) * r2 * r2;
    }
    auto in = intersect_CC(c1, r1, c2, r2);
    auto x = in.first;
    auto y = in.second;

    if (ccw(x - c1, y - c1) < 0) swap(x, y);
    double ans = 0;
    auto a1 = atan2l(ccw(x-c1, y-c1), dot(x-c1, y-c1));
    ans += (a1*r1*r1 - ccw(x-c1, y-c1)) / 2;

    if (ccw(x - c2, y - c2) < 0) {
        auto a2 = atan2l(ccw(y-c2, x-c2), dot(y-c2, x-c2));
        ans += (a2*r2*r2 - ccw(y-c2, x-c2))/2;
    } else {
        ans += acos(-1)*r2*r2;
        auto a2 = atan2l(ccw(x-c2, y-c2), dot(x-c2, y-c2));
        ans -= (a2*r2*r2 - ccw(x-c2, y-c2))/2;
    }
    return ans;
}


int main() {
    cout << setprecision(8) << fixed;
    Point<double> c1, c2;
    double r1, r2;
    cin>>c1>>r1>>c2>>r2;
    cout << area_inter_CC(c1, r1, c2, r2) << '\n';
    return 0;
}