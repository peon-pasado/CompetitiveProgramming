#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#define S Segment
#define P Point
#define T long long
using namespace std;
const double eps = 1e-7;


struct Point {
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P other) const {return x<other.x || (abs(x-other.x)<eps && y<other.y);}
    bool operator>(P other) const {return other < *this;}
    bool operator==(P other) const {return abs(x-other.x)<eps && abs(y-other.y)<eps;}
    bool operator<=(P other) const {return *this == other || *this < other;}
    bool operator>=(P other) const {return other <= *this;}
    P operator+(P other) const {return P(x+other.x, y+other.y);}
    P operator-(P other) const {return P(x-other.x, y-other.y);}
    P operator*(T c) const {return P(x*c, y*c);}
    P operator/(T c) const {return P(x/c, y/c);}
    friend P operator*(T c, const P p) {return p*c;}
    T operator*(P other) const {return x*other.x + y*other.y;}
    T operator^(P other) const {return x*other.y - y*other.x;}
    T dot(P other) const {return (*this)*other;}
    T cross(P other) const {return (*this)^other;}
    T cross(P a, P b) const {return (a-*this).cross(b-*this);}
    T norm2() const {return x*x + y*y;}
    double norm() const {return sqrt((double)norm2());}
    double dist(P p) {return (p-(*this)).norm();}
    // angle to x-axis in interval [-pi, pi]
    double angle() const {return atan2(y, x);}
    double angle(P p) const {return atan2(*this ^ p, *this * p);} //[-pi, pi]
    P unit() const {return *this/norm();} // makes dist()=1
    P perp() const {return P(-y, x);} // rotates +90 degrees
    P normal() const {return perp().unit();}
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
      return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));}
    P rotate(Point other, double a) const {
      return (*this-other).rotate(a) + other;}
    friend istream& operator>>(istream& is, P& other) {
      is.get();
      is.get();
      is >> other.x;
      is.get();
      is >> other.y;
      is.get();
      other.x *= 2;
      other.y *= 2;
      //cout << other.x << " " << other.y << endl;
      return is;
    }
    friend ostream& operator<<(ostream& os, P other) {
      return os << other.x << " " << other.y;}
};

struct Segment {
    P a, ab;
    bool is_line;
    Segment() {}
    Segment(P a, P b, bool is_line=false):
            a(a), ab(b - a), is_line(is_line) {}
    P b() {return a + ab;}
};

bool intersect_test(S p, S q) {
    T s = p.ab ^ q.ab;
    if (abs(s) < eps) {
        if (abs((q.a - p.a) ^ p.ab) < eps) { 
            if (p.is_line || q.is_line) return 1;
            P la = p.a, lb = p.b();
            P ra = q.a, rb = q.b();
            if (la > lb) swap(la, lb);
            if (ra > rb) swap(ra, rb);
            return max(la, ra) <= min(lb, rb);
        } 
        return 0;
    }
    T t1 = q.ab^(p.a - q.a);
    T t2 = p.ab^(p.a - q.a);
    if (s < 0) t1 = -t1, t2 = -t2, s = -s;
    bool r1 = (0 <= t1 && t1 <= s) || p.is_line;
    bool r2 = (0 <= t2 && t2 <= s) || q.is_line;
    return r1 && r2;
}

pair<bool, P> intersect(S p, S q) {
    T s = p.ab ^ q.ab;
    if (abs(s) < eps) {
        if (abs((q.a - p.a) ^ p.ab) < eps) { 
            if (p.is_line || q.is_line) return make_pair(1, p.a);
            P la = p.a, lb = p.b();
            P ra = q.a, rb = q.b();
            if (la > lb) swap(la, lb);
            if (ra > rb) swap(ra, rb);
            P xa = max(la, ra);
            P xb = min(lb, rb);
            return xa <= xb ? make_pair(1, xa) : make_pair(0, P(0, 0));
        } 
        return make_pair(0, P(0, 0));
    }
    T t1 = q.ab^(p.a - q.a);
    T t2 = p.ab^(p.a - q.a);
    if (s < 0) t1 = -t1, t2 = -t2, s = -s;
    bool r1 = (0 <= t1 && t1 <= s) || p.is_line;
    bool r2 = (0 <= t2 && t2 <= s) || q.is_line;
    return make_pair(r1 && r2, p.a + p.ab * t1 / s);
}

struct cmp {
    P zero;
    cmp(P zero): zero(zero) {}
    bool operator()(const P& p, const P& q) { //no dos puntos en el rayo desde zero.
        return p > zero == q > zero ? (p - zero).cross(q - zero) > 0 : p > zero;
    }
};

vector<S> get_poly(int n) {
    vector<P> points(n);
    for (int i=0; i<n; ++i) {
        cin >> points[i];
    }
    vector<S> s(n);
    for (int i=0; i<n; ++i) {
        s[i] = S(points[i], points[(i+1)%n]);
    }
    return s;
}

vector<S> get_square() {
    //cout << "rr" << endl;   
    P p[4];
    cin>>p[0];
    cin>>p[2];
    P mi = (p[0] + p[2]) / 2;
    p[3] = mi + (p[2] - mi).perp();
    p[1] = mi - (p[2] - mi).perp();
    vector<S> s(4);
    for (int i=0; i<4; ++i) {
        s[i] = S(p[i], p[(i+1)%4]);
    }
    return s;
}

vector<S> get_rectangle() {
    P p[4];
    for (int i=0; i<3; ++i) {
        cin>>p[i];
    }
    P mi = (p[0] + p[2]) / 2;
    p[3] = mi - (p[1] - mi);
    vector<S> s(4);
    for (int i=0; i<4; ++i) {
        s[i] = S(p[i], p[(i+1)%4]);
    }
    return s;
}

bool intersectPP(vector<S>& r, vector<S>& s) {
    for (int i=0; i<r.size(); ++i) {
        for (int j=0; j<s.size(); ++j) {
            if (intersect_test(r[i], s[j])) {
                return 1;
            }
        }
    }
    return 0;
}

vector<S> process(string& name) {
    if (name == "square") {
        return get_square();
    }
    if (name == "rectangle") {
        return get_rectangle();
    }
    if (name == "triangle") {
        return get_poly(3);
    }
    if (name == "line") {
        return get_poly(2);
    }
    int n;
    cin>>n;
    return get_poly(n);
}

struct cmp1 {
    vector<string> names;
    cmp1(vector<string> names): names(names) {}
    bool operator()(int i, int j) {
        return names[i] < names[j];
    }
};

int main() {
    string shape;
    while (cin >> shape, shape != ".") {    
        //cout << shape << endl;
        vector<string> names;
        string type;
        cin>>type;
        //cout << type << endl;
        names.push_back(shape);
        vector<vector<S> > ss;
        ss.push_back(process(type));
        ///cout << "debug" << endl;
        while (cin >> shape, shape != "-") {
            //cout << ":: " << shape << endl;
            names.push_back(shape);
            cin>>type;
            //cout << type << endl;
            ss.push_back(process(type));
            //cout << shape << endl;
            //exit(0);
        }
        vector<int> id(names.size());
        for (int i=0; i<id.size(); ++i) id[i]=i;
        sort(id.begin(), id.end(), cmp1(names));

        for (int i=0; i<names.size(); ++i) {
            vector<int> ids;
            for (int j=0; j<names.size(); ++j) {
                if (i == j) continue;
                if (intersectPP(ss[id[i]], ss[id[j]])) {
                    ids.push_back(id[j]);
                }
            }
            cout << names[id[i]] << " ";
            if (ids.empty()) cout << "has no intersections\n";
            else if (ids.size() == 1) cout << "intersects with " << names[ids[0]] << '\n';
            else {
                //sort(ids.begin(), ids.end(), cmp1(names));
                cout << "intersects with ";
                cout << names[ids[0]];
                for (int j=1; j+1<ids.size(); ++j) {
                    cout << ", " << names[ids[j]];
                }
                if (ids.size() == 2) cout << " and " << names[ids[1]] << '\n';
                else cout << ", and " << names[ids.back()] << '\n';
            }
        } 
        cout << '\n';
    }
    return 0;
}