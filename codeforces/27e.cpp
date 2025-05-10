#include <bits/stdc++.h>
using namespace std;

const int maxN = 1010;
bool composite[100];
vector<int> prime;
int id[maxN];
int n;

void sieve(int n) {
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.push_back(i);
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) break;
		}
	}
}

vector<int> d;
const long long inf = 2e18;
bool vis[25][100];
long long memo[25][100];
long long dp(int pos, int i) {
	if (pos == prime.size()) return i == 0 ? 1 : inf;
	if (vis[pos][i]) return memo[pos][i];
	long long ans = inf;
	for (int di : d) {
		if (d[i] % di == 0) {
			int k = di - 1;
			long long pot = 1;
			bool ok = 1;
			for (int j = 0; j < k; ++j) {
				if (pot > inf / prime[pos]) {
					ok = 0;
					break;
				}
				pot *= prime[pos]; 
			}
			if (ok) {
				long long temp = dp(pos+1, id[d[i] / di]);
				if (temp <= ans / pot) {
					ans = min(ans, temp * pot);
				}
			}
		}
	}
	vis[pos][i] = 1;
	return memo[pos][i] = ans;
}

int main() {
	cin >> n;
	if (n == 1) {
		return cout << 1 << endl, 0;
	}
	sieve(50);
	for (int i = 1; i*i <= n; ++i) {
		if (n % i == 0) {
			d.push_back(i);
			if (i != n/i) d.push_back(n/i);
		}
	}
	sort(begin(d), end(d));
	for (int i = 0; i < d.size(); ++i) id[d[i]] = i;	
	cout << dp(0, id[n]) << endl;
	return 0;
}