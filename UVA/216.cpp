#include <bits/stdc++.h>
#define ones(s) __builtin_popcount(s)
#define max_pos(s) (31 - __builtin_clz(s))
using namespace std;

const int maxn = 10;
double dp[1<<maxn][maxn]; //comenzando en el elemento de menor indice
double w[maxn][maxn];
const double inf = 1e10;
int x[maxn], y[maxn];
int n;

int main() {
	cout << setprecision(2) << fixed;
	int tc = 1;
	while (cin >> n, n) {
		for (int i = 0; i < n; ++i) {
			cin >> x[i] >> y[i];
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				w[i][j] = 16 + hypot(x[i] - x[j], y[i] - y[j]);
			}
		}
		for (int s = 1; s < 1<<n; ++s) {
			if (ones(s) == 1) {
				for (int i = 0; i < n; ++i) {
					dp[s][i] = (s == (1<<i)) ? 0. : inf;
				}
			}	else {
				for (int i = 0; i < n; ++i) {
					dp[s][i] = inf;
					if (~s & (1<<i)) continue;
					for (int j = 0; j < n; ++j) {
						if (~s & (1<<j)) continue;
						if (i == j) continue;
						dp[s][i] = min(dp[s][i], dp[s ^ (1<<i)][j] + w[j][i]);
					}
				}
			}
		}
		cout << "**********************************************************\n";
		cout << "Network #" << tc << endl;
		tc += 1;
		int target = (1<<n) - 1;
		int v = min_element(dp[target], dp[target] + n) - dp[target];
		int s = target;
		for (int i = 0; i < n - 1; ++i) {
			double res = dp[s][v];
			s ^= (1<<v);
			int u = -1;
			for (int j = 0; j < n; ++j) {
				if (abs(dp[s][j] + w[j][v] - res) < 1e-4) {
					u = j;
					break;
				}
			}
			cout << "Cable requirement to connect " 
				<< "(" << x[v] << "," << y[v] << ") to " 
				<< "(" << x[u] << "," << y[u] << ") is "
				<< w[u][v] << " feet.\n";
			v = u;
		}
		cout << "Number of feet of cable required is " << dp[target][v] << ".\n";
	}
	return 0;
}