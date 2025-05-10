#include <bits/stdc++.h>
using namespace std;
const int maxN = 110;
long long memo[maxN][maxN];
long long f[maxN];
long long c[maxN];
int n, m;

int main() {
	while (cin >> n >> m) {	
		f[0] = m;
		for (int i = 1; i < maxN; ++i) {
			f[i] = f[i-1] * 2 / 3;
		}
		memset(memo, 0, sizeof memo);
		for (int i = 1; i <= n; ++i) {
			cin >> c[i];
			memo[i][0] = c[i] = min(c[i], (long long)m);
		}	
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) {
				memo[i+1][j+1] = max(memo[i+1][j+1], memo[i][j] + min(f[j+1], c[i+1]));
				memo[i+2][j] = max(memo[i+2][j], memo[i][j] + min(f[j], c[i+2]));
				memo[i+3][0] = max(memo[i+3][0], memo[i][j] + c[i+3]);
			}
		}
		cout << *max_element(memo[n], memo[n]+n+1) << endl;
	}
	return 0;
}