#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6 + 10;
struct Point {
	long long x, y, a;
	Point(long long x=0, long long y=0, long long a=0): x(x), y(y), a(a) {}
	Point operator -(Point other) {return Point(x - other.x, y - other.y);}
	long double operator ^(Point other) {return x*1.L*other.y - y*1.L*other.x;}
	bool operator <(Point other) {return x < other.x or x == other.x and y < other.y;}
} p[maxN];
long long a[maxN];
long long dp[maxN];
int n;

vector<Point> ch;
void add(Point p) {
	int n = ch.size();
	while (n >= 2 and ((ch[n-1] - ch[n-2])^(p - ch[n-2])) >= 0) n -= 1;
	ch.resize(n+1);
	ch[n] = p;
}

long long query(int x) {
	Point q = Point(-1, x);
	int lo = 0, hi = (int)ch.size() - 1;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if ((ch[mid] ^ q) < (ch[mid+1] ^ q)) lo = mid+1;
		else hi = mid;
	}
	return ch[lo] ^ q;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld %lld %lld", &p[i].x, &p[i].y, &p[i].a);
	}
	sort(p+1, p+n+1);
	add(Point());
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		dp[i] = query(-p[i].y) + p[i].x * p[i].y - p[i].a;
		add(Point(p[i].x, dp[i]));
		ans = max(ans, dp[i]);
	}
	cout << ans << endl;
	return 0;
}