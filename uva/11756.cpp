#include <bits/stdc++.h>
#define sz(v) ((int)v.size())
#define double long double
using namespace std;

// Redefine epsilon and infinity as necessary. Be mindful of precision errors.
const double eps = 1e-9, inf = 1e9; 

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

    bool operator<(const P& p) const {return x < p.x || (fabs(x-p.x)<eps && y < p.y);}
    bool operator>(const P& p) const {return p < *this;}
    bool operator==(const P& p) const {return x == p.x && y == p.y;}
};

template<typename T>
struct Line { 

    Point<T> a, ab; 

    Line() {}
    Line(const Point<T>& a, const Point<T>& b) : a(a), ab(b - a) {}

    Point<T> b() const {return a + ab;}


    template<typename U>
    explicit operator Line<U>() const {return Line<U>(Point<U>(a), Point<U>(b()));} 

    friend bool operator<(const Line& r, const Line& s) {        
        if (r.a < r.b() == s.a < s.b()) return ccw(r.ab, s.ab) > eps;
        return r.a < r.b();
    }

    friend Point<T> inter(const Line& I, const Line& J) {
        return I.a + I.ab * ccw(J.a - I.a, J.ab) / ccw(I.ab, J.ab);
    }

    friend bool out(const Line& I, const Point<T> p) {
        return ccw(I.ab, p - I.a) < -eps;
    }

    friend bool test(const Line& H, const Line& I, const Line& J) {
        return out(H, inter(I, J));
    }

    //friend bool test(const Line& H, const Line& I, const Line& J) { //infinite precision (needs integer type)
    //    if (ccw(I.ab, J.ab) > 0)
    //        return (__int128_t)ccw(H.ab, I.a - H.a) * ccw(I.ab, J.ab) < (__int128_t)ccw(J.ab, J.a - I.a) * ccw(H.ab, I.ab);
    //    else
    //        return (__int128_t)ccw(H.ab, I.a - H.a) * ccw(I.ab, J.ab) > (__int128_t)ccw(J.ab, J.a - I.a) * ccw(H.ab, I.ab);
    //} 
};

template<typename T>
vector<Line<T>> hp_intersect(vector<Line<T>>& H) { 
    sort(H.begin(), H.end());
    deque<Line<T>> dq;
    for(auto h : H) {
        while (sz(dq) > 1 && test(h, dq[sz(dq)-1], dq[sz(dq)-2])) dq.pop_back();
        while (sz(dq) > 1 && test(h, dq[0], dq[1])) dq.pop_front();
        if (sz(dq) > 0 && fabs(ccw(h.ab, dq[sz(dq)-1].ab)) < eps) {
            if (ccw(h.ab, dq[sz(dq)-1].a - h.a) < -eps) dq.back() = h;
        } else dq.push_back(h);
    }
    while (sz(dq) > 2 && test(dq[0], dq[sz(dq)-1], dq[sz(dq)-2])) dq.pop_back();
    if (sz(dq) < 3) return {};
    return {dq.begin(), dq.end()};
}


template<typename T, typename U>
vector<Point<U>> get_points(vector<Line<T>> H) {
    vector<Point<U>> ret(sz(H));
    for(int i = 0; i < sz(H); i++) ret[i] = inter((Line<U>)H[i], (Line<U>)H[(i+1)%sz(H)]);
    //auto equals = [&](const Point<U>& p, const Point<U>& q) {return p == q;};
    //ret.erase(unique(ret.begin(), ret.end(), equals), ret.end());
    //if (sz(ret) > 1 && equals(ret.back(), ret[0])) ret.pop_back();
    return ret;
}

int next(int i, int n) {
    return (i + 1) % n;
}

int back(int i, int n) {
    return (i + n - 1) % n;
}

template<class P>
double sign_area(vector<P> p) {
    int n = p.size();
    double res = 0.;
    for (int i=0;i<n; ++i) {
        res += ccw(p[i], p[next(i, n)]);
    }
    return res;
}


double solve(vector<Line<double>> s) {
    return abs(sign_area(get_points<double, double>(hp_intersect(s)))) * 0.5;
}

using ll = long long;

int main() {
    cout<<setprecision(6)<<fixed;
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        vector<Line<double>> s;
        for (int i=0; i<n; ++i) {
            Point<double> p, q;
            cin>>p>>q;
            assert(fabs(p.x-q.x) > eps);
            s.push_back(Line<double>(p, q));
        }
        for (int i=0; i<n; ++i) {
            if (s[i].ab.x < 0) s[i].ab = s[i].ab * - 1;
        }
        double xl, xu;
        cin>>xl>>xu;
        s.push_back(Line<double>(Point<double>(xl, 1), Point<double>(xl, 0)));
        s.push_back(Line<double>(Point<double>(xu, 0), Point<double>(xu, 1)));
        double yl = 1e20, yr = -1e20;
        for (int i=0; i<n; ++i) {
            auto r = inter(s[n], s[i]);
            yl = min(yl, r.y);
            yr = max(yr, r.y);    
        }
        for (int i=0; i<n; ++i) {
            auto r = inter(s[n+1], s[i]);
            yl = min(yl, r.y);
            yr = max(yr, r.y);    
        }
        s.push_back(Line<double>(Point<double>(0, yl), Point<double>(1, yl)));
        s.push_back(Line<double>(Point<double>(1, yr), Point<double>(0, yr)));
        double area = (yr - yl) * (xu - xl);    
        area -= solve(s);
        for (int i=0; i<n; ++i) s[i].ab = s[i].ab * -1;
        area -= solve(s);
        cout << area << '\n';
    }
    return 0;
}