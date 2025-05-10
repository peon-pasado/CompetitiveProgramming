#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int n;
string s;
string patt = "ICPCASIASG";
int dx[] = {-1, 1, -1, 1, 2, -2, 2, -2};
int dy[] = {2, -2, -2, 2, -1, 1, 1, -1};
bool vis[MAXN][MAXN][11], memo[MAXN][MAXN][11];
char M[MAXN][MAXN];

bool valid(int x, int y) {
	return x >= 0 and x < n and y >= 0 and y < n; 
}

bool dp(int x, int y, int k) {
	if (k+1 == patt.size()) return 1;
	if (vis[x][y][k]) return memo[x][y][k];	

	bool ans = 0;
	for (int i = 0; i < 8; ++i)	{
		int nx = x + dx[i];
		int ny = y + dy[i];		
		if (not valid(nx, ny)) continue;
		if (M[nx][ny] != patt[k+1]) continue;

		ans |= dp(nx, ny, k+1); 
	}

	vis[x][y][k] = 1;
	return memo[x][y][k] = ans;
}

int main() {

	scanf("%d\n", &n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			M[i][j] = getchar();

	bool ans = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (M[i][j] == patt[0])
				ans |= dp(i, j, 0);

	puts(ans ? "YES" : "NO");

	return 0;
}