#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6 + 10;
vector<int> prime;
bool composite[maxN];
int Min[maxN];

void sieve(int n) {
	for (int i = 2; i < n; ++i) {
		if (not composite[i]) {
			prime.emplace_back(i);
			Min[i] = i;
		}
		for (int p : prime) {
			if (p * i >= n) break;
			composite[p * i] = 1;
			Min[p * i] = p;
			if (i % p == 0) break;
		}
	}	
}

int cnt[maxN];
int cnt2[maxN];

int main() {
	sieve(maxN);
	int n, k;
	scanf("%d %d", &n, &k);
	while (Min[k]) {
		int e = 0;
		int f = Min[k];
		while (k % f == 0) k /= f, e += 1;
		cnt[f] = e;
	}
	int r = 0;
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);		
		while (Min[x]) {
			int e = 0;
			int f = Min[x];
			while (x % f == 0) x /= f, e += 1;
			cnt2[f] = max(cnt2[f], e);
		}
	}
	bool isPossible = true;
	for (int i = 2; i <= 1000000; ++i) {
		if (cnt[i] > cnt2[i]) isPossible = false;
	}
	if (isPossible) puts("Yes");
	else puts("No");
	return 0;
}