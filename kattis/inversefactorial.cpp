#include <bits/stdc++.h>
using namespace std;

char s[1000006];
int main() {

	scanf("%s", s);

	int len = strlen(s);

	if (len <= 15) {
		long long n;
		sscanf(s, "%lld", &n);
		long long f = 1;
		for (int i = 1; i <= 50; ++i) {		
			f *= i;
			if (f == n) {
				printf("%d\n", i);
				break;
			}
		}
	} else {
		long double dig = 1;
		int pos = 0;
		for (int i = 1; i <= 1000000; ++i) {
			dig += log10(i);
			if (floor(dig) > len) {
				printf("%d\n", i-1);
				break;
			}
		}
	}

	return 0;
}