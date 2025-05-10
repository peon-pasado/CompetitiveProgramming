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

const int maxn = 1e5 + 2;
int pi[maxn], rnk[maxn];
int n, l, r, ll, rr;
Point<long long> p[maxn];
int a[maxn], b[maxn];
int od[maxn];
int comp[maxn];
long long f[maxn];
int min_[maxn];

int get(int x) {return x==pi[x]?x:pi[x]=get(pi[x]);}
void merge(int x, int y) {
    x = get(x); y = get(y);
    if (rnk[x]<rnk[y]) swap(x, y);
    pi[y]=x;
    rnk[x]+=rnk[x]==rnk[y];
}

void insert(int id[], int& n, int i) {
    while (n>1&&ccw(p[id[n-1]]-p[id[n-2]], p[i]-p[id[n-2]])<=0) n--;
    id[n++]=i;
}

int query(int id[], int& l, int n, int i) {
    while (l+1<n&&dot(p[id[l]]-p[id[l+1]], p[i]) >= 0) l++;
    return id[l];
}

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

int main() {
    int t;
    read(t);
    while (t--) {
        read(n);
        for (int i=0; i<n; ++i) {
            int x, y;
            read(x); read(y);
            p[i].x = x;
            p[i].y = y; 
            rnk[i]=0;
        }
        iota(pi, pi+n, 0);        
        sort(p, p+n);
        iota(od, od+n, 0);
        sort(od, od+n, [&](int i, int j) {
            return ccw(p[i], p[j]) > 0;
        });
        long long ans = 0;
        int m = n;
        while (m != 1) {
            for (int i=0; i<n; ++i) f[i] = 1e18;
            int s = 0;
            for (int i=0; i<n; ++i) {
                if (get(i) == i) {
                    comp[i] = s++;
                }
            }
            for (int k=0; (1<<k) < s; ++k) {
                ll=rr=l=r=0;
                for (int i=0; i<n; ++i) {
                    if (comp[pi[i]]&(1<<k)) insert(a, l, i);
                    else insert(b, r, i);
                }
                int nxt;
                for (int i=0; i<n; ++i) {
                    int rt = pi[od[i]];
                    if (comp[rt]&(1<<k)) nxt = query(b, rr, r, od[i]);
                    else nxt = query(a, ll, l, od[i]);
                    if (dot(p[od[i]], p[nxt]) < f[rt]) {
                        min_[rt] = nxt;
                        f[rt] = dot(p[od[i]], p[nxt]);
                    }
                }
            }
            for (int i=0; i<n; ++i) {
                if (min_[i] == -1) continue;
                if (get(i) != get(min_[i])) {
                    ans += f[i];
                    m--;
                    merge(min_[i], i);
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}