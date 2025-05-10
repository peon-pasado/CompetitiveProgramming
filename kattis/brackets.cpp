#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
bool vis[MAXN][MAXN][3];
bool dp[MAXN][MAXN][3];
int v[MAXN];
int n;

bool valid(int pos, int sum, int state) {
	
	if (state > 2) return 0;
	if (sum < 0) return 0;
	if (vis[pos][sum][state])  return dp[pos][sum][state];	
	if (pos == n) {
		return sum == 0;
	}	

	bool ans = valid(pos, sum, state+1);
	if (state == 0) {
		ans = ans || valid(pos+1, sum + v[pos], 0);
	} else if (state == 1) {
		ans = ans || valid(pos+1, sum + -1*v[pos], 1);
	} else if (state == 2) {
		ans = ans || valid(pos+1, sum + v[pos], 2);
	}
	
	vis[pos][sum][state] = 1;
	return dp[pos][sum][state] = ans;
}


int main() {

	n = 0;
	for (int i = getchar(); i != '\n'; i = getchar()) {
		v[n++] = (i == '(' ? 1 : -1);
	}

	if (valid(0, 0, 0)) puts("possible");
	else puts("impossible");

	return 0;
}