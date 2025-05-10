#include <bits/stdc++.h>
using namespace std;
long long a[2], b[2];

bool check(long long a, long long b) {
	while (a % 2 == 0) a >>= 1;
	while (a % 3 == 0) a /= 3;
	while (b % 2 == 0) b >>= 1;	
	while (b % 3 == 0) b /= 3;
	return a == b;
}

const int maxN = 33;
int memo[71][40][71][40];
bool vis[71][40][71][40];
char tr[71][40][71][40];
int dp(int t1, int t2, int u1, int u2) {
	if (t1 == u1 and t2 == u2) return 0;
	if (vis[t1][t2][u1][u2]) return memo[t1][t2][u1][u2];
	vis[t1][t2][u1][u2] = 1;	
	int& ans = memo[t1][t2][u1][u2] = 10000;
	char& c = tr[t1][t2][u1][u2] = 0;	
	if (t2 > 0) {
		if (ans > dp(t1+1, t2-1, u1, u2) + 1) {
			ans = dp(t1+1, t2-1, u1, u2) + 1;
			c = 1;
		}
	}
	if (t1 > 0) {
		if (ans > dp(t1-1, t2, u1, u2) + 1) {
			ans = dp(t1-1, t2, u1, u2) + 1;
			c = 2;
		}
	}	
	if (u1 > 0) {
		if (ans > dp(t1, t2, u1-1, u2) + 1) {
			ans = dp(t1, t2, u1-1, u2) + 1;
			c = 3;
		}
	}
	if (u2 > 0) {
		if (ans > dp(t1, t2, u1+1, u2-1) + 1) {
			ans = dp(t1, t2, u1+1, u2-1) + 1;
			c = 4;
		}
	}
	return ans;
}


int main() {
	for (int i = 0; i < 2; ++i) {
		cin >> a[i] >> b[i];
	}
	if (check (a[0] * 1ll * b[0], a[1] *1ll* b[1])) {
		int two[2] = {0, 0};
		int three[2] = {0, 0};		
		long long n[2];
		for (int i = 0; i <= 1; ++i) {
			n[i] = a[i] *1ll* b[i];
			while (n[i] % 2 == 0) two[i] += 1, n[i] /= 2;
			while (n[i] % 3 == 0) three[i] += 1, n[i] /= 3;
		}		
		
		int temp = dp(two[0], three[0], two[1], three[1]);
		
		if (temp > 1000) {
			cout << -1 << endl;
		} else {
			cout << dp(two[0], three[0], two[1], three[1]) << endl;
			int d[] = {two[0], three[0], two[1], three[1]};
			while (true) {
				bool ok = a[0] *1ll* b[0] == a[1] *1ll* b[1];
				if (ok == 1) {
					break;
				}
				switch (tr[d[0]][d[1]][d[2]][d[3]]) {
					case 1: 
						if (a[0] % 3 == 0) a[0] /= 3, a[0] *= 2;
						else b[0] /= 3, b[0] *= 2;
						d[1] -= 1; d[0] += 1; break;
					case 2: 
						if (a[0] % 2 == 0) a[0] /= 2;
						else b[0] /= 2;
						d[0] -= 1; break;
					case 3: 
						if (a[1] % 2 == 0) a[1] /= 2;
						else b[1] /= 2;	
						d[2] -= 1; break;
					case 4:
						if (a[1] % 3 == 0) a[1] /= 3, a[1] *= 2;
						else b[1] /= 3, b[1] *= 2;
						d[3] -= 1; d[2] += 1; break;
				}
			}
			for (int i = 0; i < 2; ++i) {
				cout << a[i] << " " << b[i] << endl;
			}
		}
	} else {
		puts("-1");	
	}
	return 0;
}