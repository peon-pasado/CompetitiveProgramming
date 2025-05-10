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


int main() {
    cout<<setprecision(8)<<fixed;
    Point<double> c;
    double r;
    cin>>c>>r;
    int q;
    cin>>q;
    while (q--) {
        Point<double> a, b;
        cin >> a >> b;
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
        cout << r1 << ' ' << r2 << '\n';
    }
    return 0;
}