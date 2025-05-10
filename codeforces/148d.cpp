#include <bits/stdc++.h>
using namespace std;
const int maxN = 1010;
long double memo[maxN][maxN][2];
bool vis[maxN][maxN][2];

long double dp(int w, int b, int turn) {
	if (w + b == 0) return 0;
	if (w + b == 1) return w + (!turn) == 2;
	if (vis[w][b][turn]) return memo[w][b][turn];
	vis[w][b][turn] = 1;
	long double& p = memo[w][b][turn] = 0;
	if (turn) {
		if (b) {
			if (b >= 2) p += 1.L * b / (b + w) * (b-1) / (b + w - 1) * dp(w, b-2, 0);
			if (w) p += 1.L * b / (b + w) * w / (b + w - 1)  * dp(w-1, b-1, 0);
		}
	} else {
		if (w) {
			p += 1.L * w / (w + b);
		}
		if (b) {
			p += 1.L * b / (w + b) * dp(w, b-1, 1);
		}
	}
	return p;
} 

int main() {
	int w, b;
	cin >> w >> b;
	cout << setprecision(12) << fixed << dp(w, b, 0) << endl;
	return 0;
}