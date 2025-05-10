#include <bits/stdc++.h>
using namespace std;
const int maxN = 10;
int s[maxN][maxN];
long long fr = 0, target;
int block[2][2][10];
int row[10][10], col[10][10];
int t;

bool valid(int i, int j, int k) {
	int x = row[i][k];
	int y = col[j][k];
	int z = block[i>>2][j>>2][k];
	if (x > 1 or y > 1 or z > 2) return 0;
	return 1;
}

int one(long long x) {
	for (int i = 0; i < 64; ++i) {
		if (x&(1ll<<i)) return i;
	}
}

bool sol = 0;
void sudoku() {
	if (sol) return;
	if (fr == 0ll) {
		puts("YES");
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				printf("%d%c", s[i][j], j==7?'\n':' ');
			}
		}
		sol = 1;
		return;
	}
	int x = one(fr);
	int i = x / 8;
	int j = x % 8;
	for (int k = 1; k <= 8; ++k) {
		block[i>>2][j>>2][k] += 1;
		row[i][k] += 1;
		col[j][k] += 1;
		fr ^= 1ll<<x;
		s[i][j] = k;
		if (valid(i, j, k)) {
			sudoku();
		}
		fr ^= 1ll<<x;
		block[i>>2][j>>2][k] -= 1;
		row[i][k] -= 1;
		col[j][k] -= 1;
		if (sol) break;
	}
}

int main() {
	
	scanf("%d", &t);
	for (int nc = 1; nc <= t; ++nc) {
		memset(block, 0, sizeof block);
		memset(row, 0, sizeof row);
		memset(col, 0, sizeof col);
		bool ok = 1;
		fr = 0;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				scanf("%d", s[i]+j);
				if (s[i][j] == 0) {
					fr |= (1ll<<8*i+j);
				} else {
					row[i][s[i][j]] += 1;
					col[j][s[i][j]] += 1;
					block[i>>2][j>>2][s[i][j]] += 1;
					ok &= valid(i, j, s[i][j]);
				}
			}
		}
		printf("Test case #%d: ", nc);
		if (ok) {
			sol = 0;
			sudoku();
			if (not sol) puts("NO");
		} else {
			puts("NO");
		}
	}
	return 0;
}