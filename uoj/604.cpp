#include <bits/stdc++.h>
using namespace std;

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

const int maxn = 502;
Point<long long> P[maxn];
int id[maxn];
void solve(int l, int r) {
    if (r <= l + 1) return;
    auto s = P[id[l]];
    auto m = P[id[l+1]];
    stack<int> L, R;
    for (int i=l+2; i<r; ++i) {
        if (ccw(P[id[i]] - s, m - s) > 0) {
            R.push(id[i]);
        } else {
            L.push(id[i]);
        }
    }
    if (ccw(P[id[r]] - s, m - s) < 0) swap(L, R);
    int mid = id[l+1];
    int idx = l;
    while (!L.empty()) id[++idx] = L.top(), L.pop();   
    id[++idx] = mid;
    mid = idx;
    while (!R.empty()) id[++idx] = R.top(), R.pop();
    solve(l, mid); solve(mid, r);
}


int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        for (int i=0; i<n; ++i) cin>>P[i];
        iota(id, id+n, 0);
        solve(0, n-1);
        for (int i=0; i<n; ++i) {
            cout << id[i]+1 << " \n"[i+1==n];
        }
    }
    return 0;
}