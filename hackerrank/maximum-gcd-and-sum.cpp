#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6 + 10;
bool inA[maxN], inB[maxN];

int find(int m) {
	for (int i = m; i >= 1; --i) {
		int maxA = -1, maxB = -1;
		for (int j = i; j <= m; j += i) {
			if (inA[j]) {
				maxA = j;
			}
			if (inB[j]) {
				maxB = j;
			}
		}
		if (maxA != -1 and maxB != -1) return maxA + maxB;
	}
return -1;
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		inA[x] = 1;
	}
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		inB[x] = 1;
	}
	printf("%d\n", find(1e6));
	return 0;
}