#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Point {
    T x, y;
    Point() {}
    Point(T x, T y): x(x), y(y) {}
    Point operator+(Point q) {return Point(x+q.x, y+q.y);}
    Point operator-(Point q) {return Point(x-q.x, y-q.y);}
    T operator*(Point q) {return x*q.x + y*q.y;}
    T operator^(Point q) {return x*q.y - y*q.x;}
    T norm2() {return (*this) * (*this);}
    double norm() {return sqrt(norm2());}
    friend double distance(Point p, Point q) {return (p-q).norm();}
};

template<class T>
struct Segment {
    Point<T> a, ab;
    bool isLine;
    Segment() {}
    Segment(Point<T> a, Point<T> b, bool isLine): 
    	a(a), ab(b - a), isLine(isLine) {}
    Point<T> b() { return a + ab; }
    bool intercept(Segment q) {
      T s = ab^q.ab;
      if (s == 0) {
      	if (isLine || q.isLine) {
      		return ((q.a - a) ^ ab) == 0;
      	}
      	if (((q.a - a)^ab) == 0) {
      		return q.a.x <= b().x && a.x <= q.b().x;
      	}
      	return 0;
      }
      T t1 = q.ab^(a - q.a);
      T t2 = ab^(q.a - a);
      if (s < 0) t1 = -t1;
      if (s > 0) t2 = -t2;
      bool r1 = (0 <= t1 && t1 <= abs(s)) || isLine;
      bool r2 = (0 <= t2 && t2 <= abs(s)) || q.isLine;
      return r1 && r2;
    }
};

template<class T>
double distance(Point<T> p, Segment<T> s) {
  if (!s.isLine && ((p - s.a) * s.ab) <= 0) return distance(p, s.a);
  if (!s.isLine && ((p - s.b()) * s.ab) >= 0) return distance(p, s.b());
  return abs((p - s.a) ^ s.ab) / s.ab.norm();
}

template<class T>
double distance(Segment<T> p, Segment<T> q) {
  if (p.intercept(q)) return 0;
  if (p.isLine && q.isLine) {
	return abs((p.ab ^ (q.a - p.a))) / p.ab.norm();
  }
  double d1 = p.isLine ? 1e9l : min(distance(p.a, q), distance(p.b(), q));
  double d2 = q.isLine ? 1e9l : min(distance(q.a, p), distance(q.b(), p));
  return min(d1, d2);
}

int main() {
	string text[2];
	Point<int> p[2], q[2];
	while (true) {
		for (int i = 0; i < 2; ++i) {
			cin >> p[i].x >> p[i].y >> q[i].x >> q[i].y >> text[i];
		}
		if (p[0].x > q[0].x) swap(p[0], q[0]);
		if (p[1].x > q[1].x) swap(p[1], q[1]);
		if (text[0] == "END") break;
		Segment<int> s1(p[0], q[0], text[0] == "L");
		Segment<int> s2(p[1], q[1], text[1] == "L");
		cout << setprecision(5) << fixed << distance(s1, s2) << endl;
	}
	return 0;
}