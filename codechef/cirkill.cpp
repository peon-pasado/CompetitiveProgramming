#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
struct Point {
	double x, y;
	Point(double x=0, double y=0): x(x), y(y) {}
	Point operator +(Point p) {return Point(x + p.x, y + p.y);}
	Point operator -(Point p) {return Point(x - p.x, y - p.y);}
	Point operator *(double c) {return Point(c * x, c * y);}
	Point operator /(double c) {return Point(x / c, y / c);}
	double operator *(Point p) {return x * p.x + y * p.y;}
	double operator ^(Point p) {return x * p.y - y * p.x;}
	Point orto () {return Point(-y, x);}
	friend double abs(Point p) {return p * p;}
} P[55];

struct Segment {
	Point a, ab;
	Segment(Point a, Point b, bool twoPoints=1): a(a), ab(twoPoints?b-a:b) {}
	Point b() {return a + ab;}
};
int t, n;

Point Intersect(Segment s1, Segment s2) {
	double s = s2.ab ^ s1.ab;
	double t = (s1.a - s2.a) ^ s2.ab;
	return s1.a + s1.ab * t / s;
}


int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			cin >> P[i].x >> P[i].y;
		}
		int num = 0, den = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i+1; j <= n; ++j) {
				for (int k = j+1; k <= n; ++k) {
					if (abs((P[k] - P[i]) ^ (P[j] - P[i])) < eps) {
						for (int l = 1; l <= n; ++l) {
							if (l == i or l == j or l == k) continue;
							den += 1;
						}
						continue;
					}
					Point center = Intersect(
						Segment((P[i] + P[j]) / 2.d, (P[i] - P[j]).orto(), 0),
						Segment((P[i] + P[k]) / 2.d, (P[i] - P[k]).orto(), 0)
					);
					for (int l = 1; l <= n; ++l) {
						if (l == i or l == j or l == k) continue;
						den += 1;
						if (eps + abs(P[i] - center) >= abs(P[l] - center)) num += 1;
					}
				}
			}
		}
		cout << 1.d * num / den << endl;
	}
	return 0;
}