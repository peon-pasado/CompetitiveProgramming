/**
 * @idea: backtracking
 * 
 *  - simule every posibility.
 * 
 *  - we can reduce complexity if solve every possible scenario and 
 *  check in 91 * 8 steps.
*/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
int mat[maxn][maxn];

int backtrack(int row, int colSet, int d1Set, int d2Set) {
	if (row == 8) return 0;
	int ans = -1e9;
	for (int i = 0; i < 8; ++i) {
		if (colSet&(1<<i)) continue;
		if (d1Set&(1<<(row+i))) continue;
		if (d2Set&(1<<(row-i+8))) continue;
		ans = max(ans, 
				backtrack(row+1, 
						colSet | (1<<i), 
						d1Set | (1<<row+i), 
						d2Set | (1<<row-i+8)
						) + mat[row][i]
		);
	}
	return ans;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				cin >> mat[i][j];
			}
		}
		printf("%5d\n", backtrack(0, 0, 0, 0));
	}
	return 0;
}