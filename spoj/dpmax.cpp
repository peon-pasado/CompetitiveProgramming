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

using ll = long long;
const int maxn = 2e5 + 2;
int n, tl, tu;
pair<Point<double>, int> p[maxn];
Point<double> uhull[maxn], lhull[maxn];
double ans[maxn];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<setprecision(3)<<fixed;
    cin>>n;
    for (int i=0; i<n; ++i) cin>>p[i].first, p[i].second=i;
    sort(p, p+n);
    lhull[tl++] = p[0].first;
    for (int i=1; i<n; ++i) {
        while (tl>1&&ccw(lhull[tl-1]-lhull[tl-2], p[i].first-lhull[tl-2])<=0) tl--;
        lhull[tl++] = p[i].first;
    }
    uhull[tu++] = p[0].first;
    for (int i=1; i<n; ++i) {
        while (tu>1&&ccw(uhull[tu-1]-uhull[tu-2], p[i].first-uhull[tu-2])>=0) tu--;
        uhull[tu++] = p[i].first;
    }    
    for (int i=0; i<n; ++i) {
        int lo=0, hi=tl-1;
        while (lo<hi) {
            int mi = (lo+hi)/2;
            if (dot(lhull[mi]-lhull[mi+1], p[i].first) <= 0) lo = mi+1;
            else hi = mi;
        }
        ans[p[i].second] = dot(lhull[lo], p[i].first);
        lo=0; hi=tu-1;
        while (lo<hi) {
            int mi = (lo+hi)/2;
            if (dot(uhull[mi]-uhull[mi+1], p[i].first) <= 0) lo = mi+1;
            else hi = mi;
        }
        ans[p[i].second] = max(ans[p[i].second], dot(uhull[lo], p[i].first));
    }
    for (int i=0; i<n; ++i) cout << ans[i] << '\n';
    return 0;
}