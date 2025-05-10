#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
bool composite[maxn];
int phi[maxn];
vector<int> prime;

void totient(int n) {
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!composite[i]) {
			prime.emplace_back(i);
			phi[i] = i-1;
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				phi[p * i] = p * phi[i];
				break;
			} else {
				phi[p * i] = (p - 1) * phi[i];
			}
		}
	}	
}

int main() {
	totient(1e4);
	for (int i = 2; i < maxn; ++i) {
		phi[i] += phi[i-1];
	}
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		cout << phi[n] *1ll* phi[n] << endl;
	}
	return 0;
} 