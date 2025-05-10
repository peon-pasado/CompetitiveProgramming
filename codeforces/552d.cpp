#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int maxN = 2010;
int n;
int x[maxN], y[maxN];
unordered_map<long long, int> tri[maxN];
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", x+i, y+i);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == j) {
				continue;
			}
			int vx = x[i] - x[j];
			int vy = y[i] - y[j];		
			int g = gcd(abs(vx), abs(vy));
			vx /= g;
			vy /= g;
			if (vx < 0 or vx == 0 and vy < 0) {
				vx = -vx;
				vy = -vy;
			}
			tri[i][vx*1000000000LL +  vy] += 1;
		}
	}		
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (auto v : tri[i]) {
			ans += (n-1 - v.second) * v.second; 
		}
	}
	printf("%lld\n", ans / 6);
	return 0;
}