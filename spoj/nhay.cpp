#include <bits/stdc++.h>
using namespace std;
const int p = 1e9 + 7;
const int b = 257;
const int maxN = 1e6 + 10;
char s[maxN];
int n;

int ex(int a, int b) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = (r*1ll*a) % p;
		a = (a*1ll*a) % p;
		b >>= 1;
	}
	return r;
}

int main() {
	int tc = 0;
	while (scanf("%d\n", &n) == 1) {
		if (tc++) puts("");
		int h = 0;
		int B = 1;
		for (int i = 0; i < n; ++i) {	
			h = (h + (getchar() - 'a') *1ll* B) % p;
			B = (B *1ll* b) % p;
		}	
		getchar();	
		B = 1;
		int h2 = 0;
		int i = 1;
		int ib = ex(b, p-2);
		while ((s[i] = getchar()) != '\n') {
			h2 = (h2 + (s[i] - 'a') *1ll* B) % p;
			if (i < n) {
				B = (B *1ll* b) % p;
			} else {
				if (h == h2) {
					printf("%d\n", i - n);
				}
				h2 = (h2 + p - s[i - n + 1] + 'a') % p;
				h2 = (h2 *1ll* ib) % p;	
			} 
			i += 1;
		}
	}
	return 0;
}
