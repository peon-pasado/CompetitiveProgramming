#include <bits/stdc++.h>
using namespace std;
typedef long double T;

const int maxn = 22;
struct Point {
	T x, y;
	Point(T x=0, T y=0): x(x), y(y) {}
	Point operator -(Point other) {return Point(x-other.x, y-other.y);}
	Point operator +(Point other) {return Point(x+other.x, y+other.y);}	
	T operator ^(Point other) {return x * other.y - y * other.x;}	
	T operator *(Point other) {return x * other.x + y * other.y;}
	T norm() {return sqrt((*this) * (*this));}
};
T x[maxn], y[maxn];
int n;

int nxt(int x, int n) {
	return x + 1 < n ? x + 1 : x + 1 - n;
}

int prv(int x, int n) {
	return x - 1 < 0 ? x + n - 1 : x - 1;
}

vector<Point> convex_hull(vector<Point> P) {
	vector<Point> CH;
	int n = P.size(), m = 0;
	for (int i = 0; i < n; ++i) {
		while (m >= 2 and ((CH[m-1] - CH[m-2]) ^ (P[i] - CH[m-2])) >= 0) m -= 1;
		CH.resize(m+1);
		CH[m++] = P[i];
	}
	for (int i = n-2, t = m-1; i >= 0; --i) {
		while (m >= t + 2 and ((CH[m-1] - CH[m-2]) ^ (P[i] - CH[m-2])) >= 0) m -= 1;
		CH.resize(m+1);
		CH[m++] = P[i];
	}
	CH.pop_back();
	return CH;
}

struct Segment {
	Point a, ab;
	Segment(Point a = Point(), Point b = Point()): a(a), ab(b-a) {}
	Point b () {return a + ab;}
	T dist(Point X) {
		if (abs(ab.x) < 1e-3) return 1e9;
		return abs(X.y - (a.y + (X.x - a.x) * ab.y / ab.x));
	}
};

long double area(Point A, Point B, Point C) {
	return abs((B - A) ^ (C - A));
}

long double lower_width(vector<Point>& P) {
	long double res = 1e9;
	int n = P.size();
	for (int i = 0, j = nxt(0, n); i < n; ++i) {
		while (area(P[i], P[nxt(i, n)], P[nxt(j, n)]) > area(P[i], P[nxt(i, n)], P[j])) {
			j = nxt(j, n);
		}
		res = min(res, Segment(P[i], P[nxt(i, n)]).dist(P[j]));
	}
	return res;
}

bool p(long double m) {
	vector<Point> P;
	for (int i = n-2; i >= 0; --i) {
		if (x[i] <= m) {
			long double t = (m - x[i]) / (x[i+1] - x[i]); 
			long double p = y[i] + t * (y[i+1] - y[i]);
			for (int j = 0; j <= i; ++j) {
				P.push_back({x[j], y[j]});
			}
			P.push_back({m, p});
			break;	
		}
	}
	P = convex_hull(P);
	long double res = lower_width(P);
	return res < 1 + 1e-8;
}

int main() {
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++i) {
			scanf("%Lf%Lf", x+i, y+i);
		}	
		long double lo = x[1], hi = x[n-1] + 1e-3;
		for (int i = 0; i < 22; ++i) {
			long double mi = lo + (hi-lo) / 2;
			if (p(mi)) lo = mi;
			else hi = mi;
		}
		if (lo >= x[n-1]) {
			puts("Through all the pipe.");
		} else {
			printf("%.2Lf\n", lo);
		}
	}
	return 0;
}