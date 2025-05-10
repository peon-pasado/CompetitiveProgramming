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

template<typename T>
struct Segment {
    using S = Segment<T>;
    using P = Point<T>;
    P a, ab;
    bool line;
    Segment() {}
    Segment(P a, P b, bool line=0): a(a), ab(b - a), line(line) {}
    P b() {return a + ab;}


    friend bool to_left(S s, P p) {
        return ccw(s.ab, p-s.a) > eps;
    }

    friend pair<bool, P> intersect(S p, S q) {
        T s = ccw(p.ab, q.ab);
        if (abs(s) < eps) {
            if (abs(ccw(q.a - p.a, p.ab)) < eps) { 
                if (p.line || q.line) return {1, p.a};
                P la = p.a, lb = p.b();
                P ra = q.a, rb = q.b();
                if (lb < la) swap(la, lb);
                if (rb < ra) swap(ra, rb);
                return {max(la, ra) <= min(lb, rb), max(la, ra)};
            } 
            return {0, P()};
        }
        T t1 = ccw(q.ab, p.a - q.a);
        T t2 = ccw(p.ab, p.a - q.a);
        if (s < 0) t1 = -t1, t2 = -t2, s = -s;
        bool r1 = (0 <= t1 && t1 <= s) || p.line;
        bool r2 = (0 <= t2 && t2 <= s) || q.line;
        return {r1 && r2, p.a + p.ab * t1 / s};
    }

    friend double dist(S s, P p) {
        if (!s.line) {
            if (dot(p - s.a, s.ab) <= 0) return dist(p, s.a);
            if (dot(p - s.b(), s.ab) >= 0) return dist(p, s.b());
        }
        return abs(ccw(p - s.a, s.ab)) / norm(s.ab);
    }

    friend bool operator<(S r, S s) {
        if (P() < r.ab == P() < s.ab) {
            return ccw(r.ab, s.ab) > eps;
        }
        return P() < r.ab;
    }    
};


pair<Point<double>, double> incenter(Point<double> a, Point<double> b, Point<double> c) {
    Point<double> ua = b - a;
    Point<double> va = c - a;
    Point<double> ub = a - b;
    Point<double> vb = c - b;
    Segment<double> s1(a, ua * norm(va) + va * norm(ua) + a);
    Segment<double> s2(b, ub * norm(vb) + vb * norm(ub) + b);
    Point<double> ce = intersect(s1, s2).second;
    return make_pair(ce, abs(ccw(b-a, ce-a) / norm(b-a)));
}


int main() {
    cout<<setprecision(8)<<fixed;
    int q=1;
    while (q--) {
        Point<double> a, b, c;
        cin >> a >> b >> c;
        auto res = incenter(a, b, c);
        cout << res.first << ' ' << res.second << '\n';
    }
    return 0;
}