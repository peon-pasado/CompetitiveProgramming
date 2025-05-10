#include <bits/stdc++.h>
using namespace std;

int main() {
	long long s;
	while (cin >> s) {
		int cnt = 0;
		while (s != 0) {
			if (s&1) {
				if (((s+1)&3) or s == 3) s -= 1;
				else s += 1;
			} else s /= 2;
			cnt += 1;
		}
		printf("%d\n", cnt);
	}
	return 0;
}