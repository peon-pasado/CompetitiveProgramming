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

// -- rotate matrix 
//  [cos, -sin,  0]
//  [sin,  cos,  0]
//  [  0,    0,  1]
Point<double> rotate(Point<double> p, double a, double b, double c) {
    return Point<double>(p.x * b - p.y * a, p.x * a + p.y * b) / c;
}


vector<Point<double>> tangentCC(Point<double> c1, double r1, Point<double> c2, double r2) {
    auto cc = c1;
    double rc = r1;
    if (r1 < r2) {
        swap(r1, r2);
        swap(c1, c2);
    }
    vector<Point<double>> vect;
    double d12 = dist(c1, c2);
    if (d12 + r2 > r1) {
        double a = r1 - r2;
        double c = norm(c1 - c2);
        double b = sqrtl(c*c - a*a);
        Point<double> v = c1 - c2;
        Point<double> u1 = perp(rotate(Point<double>() - v, -a, b, c));
        Point<double> u2 = perp(rotate(v, a, b, c));

        Point<double> r11 = c1 + u1 * r1 / norm(u1);
        Point<double> r12 = c2 + u1 * r2 / norm(u1);

        if (fabs(dist(cc, r11) - rc) < eps) vect.push_back(r11);
        if (fabs(dist(cc, r12) - rc) < eps) vect.push_back(r12);

        Point<double> r21 = c1 + u2 * r1 / norm(u2);
        Point<double> r22 = c2 + u2 * r2 / norm(u2);

        if (fabs(dist(cc, r21) - rc) < eps) vect.push_back(r21);
        if (fabs(dist(cc, r22) - rc) < eps) vect.push_back(r22);

    } else if (fabs(d12 + r2 - r1) < eps) {
        Point<double> v = c2 - c1;
        Point<double> r = c1 + v * r1 / norm(v);

        vect.push_back(r);
    }

    if (r1 + r2 < d12) {
        Point<double> v = c2 - c1;
        double b = r1;
        double c = d12 * r1 / (r1 + r2);
        double a = sqrtl(c*c - b*b);

        Point<double> cx = v * r1 / (r1 + r2);

        Point<double> v1 = rotate(v, -a, b, c);

        Point<double> u1 = v1 * r1 / norm(v1);
        Point<double> w1 = u1 + (cx - u1) * (r1 + r2) / r1;

        u1 = u1 + c1;
        w1 = w1 + c1;

        if (fabs(dist(cc, u1) - rc) < eps) vect.push_back(u1);
        if (fabs(dist(cc, w1) - rc) < eps) vect.push_back(w1);

        Point<double> v2 = rotate(v, a, b, c);

        Point<double> u2 = v2 * r1 / norm(v2);
        Point<double> w2 = u2 + (cx - u2) * (r1 + r2) / r1;

        u2 = u2 + c1;
        w2 = w2 + c1;

        if (fabs(dist(cc, u2) - rc) < eps) vect.push_back(u2);
        if (fabs(dist(cc, w2) - rc) < eps) vect.push_back(w2);
    } else if (fabs(d12 - r1 - r2) < eps) {
        Point<double> v = c2 - c1;
        Point<double> r = c1 + v * r1 / norm(v);

        vect.push_back(r);
    }

    sort(vect.begin(), vect.end());
    return vect;
}

int main() {
    cout << setprecision(8) << fixed;
    Point<double> c1, c2;
    double r1, r2;
    cin>>c1>>r1>>c2>>r2;
    auto v = tangentCC(c1, r1, c2, r2);
    for (auto e : v) {
        cout << e << '\n';
    }
    return 0;
}