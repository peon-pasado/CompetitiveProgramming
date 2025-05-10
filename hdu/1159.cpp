#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5;
string X, Y;
int dp[2][maxN];

int main() {

	while (cin >> X >> Y) {

		for (int i = 0; i <= Y.size(); ++i)
			dp[0][i] = 0;	

		for (int i = 1; i <= X.size(); ++i) {

			for (int j = 1; j <= Y.size(); ++j)
				if (X[i-1] == Y[j-1])
					dp[i&1][j] = dp[i&1^1][j-1] + 1;
				else
					dp[i&1][j] = max(dp[i&1][j-1], dp[i&1^1][j]);
		
		}

		printf("%d\n", dp[X.size()&1][Y.size()]);
	}


	return 0;
}