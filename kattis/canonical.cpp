#include <bits/stdc++.h>
using namespace std;

int x[102];
int n;
int Min[2000007];

int main() {

	scanf ("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", x+i);
	}	
	
	memset(Min, 1, sizeof Min);
	Min[0] = 0;
	for (int i = 0; i < n; ++i) {
		for (int m = x[i]; m <= 2000000; ++m) {
			Min[m] = min(Min[m], Min[m-x[i]] + 1);
		}
	}

	bool ok = 1;
	for (int m = 2e6; m >= 1; --m) {
		int tm = m;
		int ans = 0;
		for (int i = n-1; i >= 0; --i) {
			if (tm >= x[i]) {
				ans += tm/x[i];				
				tm %= x[i];
			}
		}

		if (ans != Min[m]) {
			ok = 0;
			break;			
		}
	}


	puts(ok ? "canonical" : "non-canonical");
	
	return 0;
}