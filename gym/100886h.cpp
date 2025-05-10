#include <bits/stdc++.h>
#define sz(v) ((int)v.size())
using namespace std;

// Redefine epsilon and infinity as necessary. Be mindful of precision errors.
const long double eps = 1e-9, inf = 1e9; 

inline char nc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
 
inline bool read(int &sum) {
    char ch = nc();
    if (ch == EOF)
        return 0;
    sum = 0;
    while (!(ch >= '0' && ch <= '9')) ch = nc();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = nc();
    return sum;
}


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

using ll = long long;
const int maxn = 5e5 + 2;
int n, m, t;
pair<Point<ll>, int> q[maxn];
Point<ll> p[maxn];
Point<ll> hull[maxn];
ll ans[maxn];

int main() {
    read(n);
    for (int i=0; i<n; ++i) {
        int x, y;
        read(x); read(y);
        q[i].first.x = x;
        q[i].first.y = y; 
        q[i].second=i;
    }
    sort(q, q+n, [](auto x, auto y) {return ccw(x.first, y.first)>0;});
    read(m);
    for (int i=0; i<m; ++i) {
        int x, y;
        read(x); read(y);
        p[i].x = x;
        p[i].y = y;
    }
    sort(p, p+m);
    hull[t++] = p[0];
    for (int i=1; i<m; ++i) {
        while (t>1&&ccw(hull[t-1]-hull[t-2], p[i]-hull[t-2])<=0) t--;
        hull[t++] = p[i];
    }
    for (int i=0, j=0; i<n; ++i) {
        while (j + 1 < t && dot(hull[j] - hull[j+1], q[i].first) >= 0) ++j;
        ans[q[i].second] = dot(hull[j], q[i].first);
    }
    for (int i=0; i<n; ++i) printf("%lld%c", ans[i], " \n"[i+1==n]);
    return 0;
}