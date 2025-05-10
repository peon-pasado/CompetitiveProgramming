#include <bits/stdc++.h>
using namespace std;

int n, m;
const int maxN = 1e3 + 2;
struct convexHull {

	struct point {
		long long x, y;
	};

	friend long long cross (const point& o, const point& a, const point& b) {
		return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	}

	point T[maxN];
	int back, front;

	void clear () {back = 0, front = -1;}

	void add (point p) {
		while (back < front and cross (T[front - 1], T[front], p) >= 0) front--;
		T[++front] = p;
	}

	long long query (long long x) {
		while (back < front and x * T[back].x + T[back].y >= x * T[back+1].x + T[back+1].y) back++;
		return x * T[back].x + T[back].y;
	}
} cht;

long long dp[maxN][maxN];
int a[maxN];
long long S[maxN], W[maxN];

int main () {

	while (scanf ("%d %d", &n, &m), n+m) {

		for (int i = 1; i <= n; ++i)
			scanf ("%d", a + i);
		
		S[n + 1] = 0;
		for (int i = n; i >= 1; --i)
			S[i] = a[i] + S[i + 1];

		W[n + 1] = 0;
		for (int i = n; i >= 1; --i)
			W[i] = a[i] * S[i + 1] + W[i + 1];

		for (int i = 1; i <= n; ++i)
			dp[i][0] = W[1] - W[i + 1] - S[i + 1] * (S[1] - S[i + 1]); 
		
		for (int j = 1; j <= m; ++j) {
			cht.clear (); cht.add({S[1], W[1]});				
			for (int i = 1; i <= n; ++i) {
				dp[i][j] = cht.query (-S[i+1]) + S[i + 1] * S[i + 1] - W[i + 1];
				cht.add ({S[i + 1], dp[i][j - 1] + W[i + 1]});
			}
		}

		printf ("%lld\n", dp[n][m]);
	}


	return 0;
}