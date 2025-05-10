#include <iostream>
#include <cstdio>
using namespace std;

string s;
int n;
const int maxN = 105;
int dp[maxN][maxN];

int oposite (int x) {
	if (x == '(') return ')';
	if (x == '[') return ']';
	return 'u';
}

int main () {
	
	while(cin >> s, s != "end"){
		for (int t = 2; t <= s.size(); ++t)
			for (int i = 0; i + t <= s.size(); ++i){
				int& ans = dp[i][i+t-1] = max(dp[i+1][i+t-1], dp[i][i+t-2]);
				
				if (oposite(s[i]) == s[i+t-1])
					ans = max(ans, dp[i+1][i+t-2] + 2);
			
				for (int k = i+1; k < i+t-1; ++k)
					if (oposite(s[i]) == s[k])
						ans = max(ans, dp[i][k] + dp[k+1][i+t-1]);
			}
	
		printf ("%d\n", dp[0][(int)s.size()-1]);
	}

	return 0;
}