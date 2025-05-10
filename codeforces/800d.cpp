#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
using ll = long long;
int G[maxn][3];
int F[maxn];
int pot[maxn];

int add(int a, int b) {
	return (a+b)%mod;
}

int mul(ll a, ll b) {
	return a*b%mod;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		G[x][0] = add(G[x][0], x);
		G[x][1] = add(G[x][1], mul(x, x));
		G[x][2]++;
	}
	int ten[10] = {1};
	for (int i = 1; i < 10; ++i)
		ten[i] = 10 * ten[i-1];
	auto getu = [&](int x, int i) {
			return (x/ten[i])%10;
	};
	pot[0] = 1;
	for (int i = 1; i < maxn; ++i)
		pot[i] = add(pot[i-1], pot[i-1]);
	for (int i = 0; i < 6; ++i)
		for (int j = 999999; j >= 0; --j) {
			if (getu(j, i) != 9) {
				for (int d = 0; d < 3; ++d)
					G[j][d] = add(G[j][d], G[j+ten[i]][d]);
			}	
		}
	for (int i = 0; i < maxn; ++i) {
		int temp = pot[G[i][2]];
		temp = mul(temp, (mod+1)/2);
		temp = mul(temp, (mod+1)/2);
		F[i] = mul(temp, add(mul(G[i][0], G[i][0]), G[i][1]));
	}
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 1000000; ++j) {
			if (getu(j, i) != 9) {
				F[j] = add(F[j], mod - F[j+ten[i]]);
			}	
		}
	long long ans = 0;
	for (int i = 0; i < 1000000; ++i)
		ans ^= i*1ll*F[i];
	cout << ans << '\n';
	return 0;
}