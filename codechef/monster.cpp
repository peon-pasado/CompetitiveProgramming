#include <bits/stdc++.h>
using namespace std;

const int maxn = (1<<17) + 5;
using ll = long long;
ll h[maxn], F[maxn];
int pos[maxn], ans[maxn<<1];
int q[maxn<<1][2];
int B = 1<<11;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> h[i];
	}
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		cin >> q[i][0] >> q[i][1]; 
		q[i][0] &= (1<<17)-1;
	}
	vector<int> ind(n);
	iota(ind.begin(), ind.end(), 0);
	for (int i = 0; i < Q; i += B) {
		memset(F, 0, sizeof F);
		for (int j = i; j < Q && j < i + B; ++j)
			F[q[j][0]] += q[j][1];
		for (int k = 0; k < 17; ++k)
			for (int s = 0; s < 1<<17; ++s)
				if (~s & (1<<k))
					F[s] += F[s^(1<<k)];
		vector<int> new_ind, killed;
		for (int ix : ind) {
			h[ix] -= F[ix];
			if (h[ix] <= 0) {
				killed.emplace_back(ix);
				h[ix] += F[ix];
			} else {
				new_ind.emplace_back(ix);
			}
		}
		for (int ix : killed) {
			for (int j = i; j < Q && j < i + B; ++j) {
				if ((ix & q[j][0]) == ix) {
					h[ix] -= q[j][1];
					if (h[ix] <= 0) {
						pos[ix] = j;
						break;
					}
				}
			}
		}
		ind = new_ind;
	}
	for (int i = 0; i < n; ++i) 
		if (h[i] <= 0)
			ans[pos[i]]--;
	for (int i = 1; i < Q; ++i)		
			ans[i] += ans[i-1];
	for (int i = 0; i < Q; ++i) 
		cout << n + ans[i] << '\n';
	return 0;
}