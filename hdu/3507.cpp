#include "bits/stdc++.h"
using namespace std;

const int maxN = 5e5 + 5;

struct convexHull {

	struct point {
		long long x, y;
	};
	friend long long cross (const point& o, const point& a, const point& b) {
		return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); 
	}
	point T[maxN];
	int back, front;
	
	void clear () {
		back = 0; front = -1;
	}

	void add (point p) { 	
		while (front > back and cross (T[front-1], T[front], p) >= 0) front--;
		T[++front] = p;
	}

	long long query (long long x) {
		while (back < front and x * T[back].x + T[back].y >= x * T[back+1].x + T[back+1].y) back++;
 		return x * T[back].x + T[back].y;
	}
} cht;
long long dp[maxN], sum[maxN];
int c[maxN];
int n, m;

int main () {

	while (~scanf ("%d %d", &n, &m)) {
		cht.clear();	
		for (int i = 1; i <= n; ++i)
			scanf("%d", c+i);

		for (int i = 1; i <= n; ++i)
			sum[i] = c[i] + sum[i-1];

		cht.add({0, 0});
		for (int i = 1; i <= n; ++i) {	
			long long q = cht.query (sum[i]);		
			dp[i] = q + sum[i] * sum[i] + m;
			cht.add({-2 * sum[i], dp[i] + sum[i] * sum[i]});
		}
		printf ("%lld\n", dp[n]);
	}	

	return 0;
}

