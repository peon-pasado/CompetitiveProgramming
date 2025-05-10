#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-10;


template<class T>
struct Point {
    using P = Point<T>;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    
    bool operator<(P other) const {return x<other.x || (abs(x-other.x)<eps && y<other.y);}
    bool operator==(P other) const {return abs(x-other.x)<eps && abs(y-other.y)<eps;}
    bool operator<=(P other) const {return *this == other || *this < other;}
   
    P operator+(P other) const {return P(x+other.x, y+other.y);}
    P operator-(P other) const {return P(x-other.x, y-other.y);}
    P operator*(T c) const {return P(x*c, y*c);}
    P operator/(T c) const {return P(x/c, y/c);}
    
    friend T dot(const P& p, const P& q) {
        return p.x * q.x + p.y * q.y;
    }
    friend T ccw(const P& p, const P& q) {
        return p.x * q.y - p.y * q.x;
    } 
    friend P perp(const P& p) {
        return P(-p.y, p.x);
    }
    friend double norm(const P& p) {
        return sqrtl(dot(p, p));
    }
    friend double dist(const P& p, const P& q) {
        return norm(p-q);
    }
    friend double angle(const P& p) {
        return atan2l(p.y, p.x);
    }
    friend istream& operator>>(istream& is, P& other) {
      return is >> other.x >> other.y;
    }
    friend ostream& operator<<(ostream& os, const P& other) {
      return os << other.x << " " << other.y;
    }
};

pair<Point<double>, Point<double>> tangent_PC(Point<double> c, double r, Point<double> p) {
    Point<double> v(c - p);
    auto d2 = dot(v, v);
    Point<double> r1 = p + (v * (d2 - r*r) + perp(v) * r * sqrtl(d2 - r*r)) / d2;
    Point<double> r2 = p + (v * (d2 - r*r) - perp(v) * r * sqrtl(d2 - r*r)) / d2;
    if (r2 < r1) swap(r1, r2);
    return make_pair(r1, r2);
}


int main() {
    cout<<setprecision(8)<<fixed;
    Point<double> p, c;
    double r;
    cin>>p>>c>>r;
    auto res = tangent_PC(c, r, p);
    cout << res.first << '\n' << res.second << '\n';
    return 0;
}