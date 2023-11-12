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

const int maxn = 1e5 + 10;
Point<long long> P[maxn];
ll id[maxn];
void solve(int l, int r) {
    if (r <= l + 1) return;

    auto pivot = partition(id+l+1, id+r, [&](int idx) {
        return P[id[idx]] > P[id[l]]; 
    });
    
    auto cmp = [&](int idx) {
        return 
    };
    sort(id+l+1, pivot, cmp);
    sort(pivot, id+r, cmp);
}


int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        vector<Point<long long>> P(n);
        for (int i=0; i<n; ++i) cin>>P[i];


    }
    return 0;
}