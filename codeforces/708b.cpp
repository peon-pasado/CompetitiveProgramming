#include <bits/stdc++.h>
using namespace std;

int c2(int n) {
	return n * (n-1) / 2;
}

int main() {
	int a[2][2];
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			cin >> a[i][j];
		}
	}
	int zero = 0, one = 0;
	while (c2(zero) < a[0][0]) {
		zero += 1;
	}
	while (c2(one) < a[1][1]) {
		one += 1;
	}
	if (zero == 0) {
		zero += a[0][1] or a[1][0];
	}
	if (one == 0) {
		 one += a[0][1] or a[1][0];
	}
	if (one + zero == 0) one = 1; 
	if (c2(zero) != a[0][0] or c2(one) != a[1][1] or zero * one != a[0][1] + a[1][0]) {
		return puts("Impossible"), 0;
	} else {
		int n = one + zero;
		for (int i = 0; i < n; ++i) {
			if (zero <= a[1][0]) {
				printf("1");
				a[1][0] -= zero;
			} else {
				printf("0");
				zero -= 1;
			}
		}
		puts("");
	}
	return 0;
}