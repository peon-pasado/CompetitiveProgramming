#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>
using namespace std;

const int MAXN = 1e5, OFFSET = 2;
const int mod = 1e9 + 7;
char s[MAXN + OFFSET];
int t, n;
int dp[26 + OFFSET];

int add (int a, int b) {
	return (a + b) % mod;
}

int mul (long long a, long long b) {
	return a * b % mod;
}

int main () {

	scanf ("%d\n", &t);

	while (t --) {

		scanf ("%s", s);
		
		memset (dp, 0, sizeof dp);
		int sum = 0;		
		for (int i = 0; s[i]; ++i) {
			int pos = s[i] - 'A';
			int cur = add ( sum, 1 );

			sum = add( add (sum, cur), mod - dp[pos] );	
			
			dp[pos] = cur;
		}
	
		printf ("%d\n", accumulate (dp, dp+26, 1, add));
	}

	return 0;
}

