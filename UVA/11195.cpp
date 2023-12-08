/**
 * @idea backtracking
 * 
 *  - simple simulation
 * 
 **/

#include <bits/stdc++.h>
using namespace std;
const int maxN = 16;
bool valid[maxN][maxN];
int n;

int backtrack(int row, int c, int d1, int d2) {
	if (row == n) return 1;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (not valid[row][i]) continue;
		if (c & (1<<i)) continue;
		if (d1 & (1<<row + i)) continue;
		if (d2 & (1<<row - i + n)) continue;
		ans += backtrack(row+1, c|(1<<i), d1|(1<<row+i), d2 | (1<<row-i+n));
	}
	return ans;
}

int main() {
	int nc = 1;
	while(scanf("%d\n", &n), n) {
		memset(valid, 1, sizeof valid);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int ch = getchar();
				if (ch == '*') {
					valid[i][j] = 0;
				}
			}
			getchar();
		}
		printf("Case %d: %d\n", nc++, backtrack(0, 0, 0, 0));
	}
	return 0;
}