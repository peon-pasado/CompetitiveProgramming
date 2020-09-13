/**
 * @author Miguel Mini
 * @tag dp, brute_force, bitset
 * @idea
 *      - we can do a simple dp in O (l n^2), 
 *      but it is not enough for the time limits.
 *
 *      - if we analyze the bottom up form of 
 *      the dp, we have:
 *          dp[i][k] = (k != a[i]) + 
 *                      min(dp[i-1][v] | n - match(v, k) <= G)
 *
 *      - therefore we want to optimize the right part of the sum.
 *
 *      - to do this we can order the dp(i-1) in O(n \log n).
 *
 *      - then we can see that the smallest must take all possible k.
 *
 *      - we can see these as a set S_t, and we will only have to 
 *      consider the elements of S_t \ {U S_i | i < t}
 *
 *      - we can make these intersections in O (n / 32)
 *
 * @complexity O(l * (n \log n + n^2 / 32))
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 110;
const int maxs = 110;
const int maxl = 1e5 + 10;
int mat[maxn][maxs];
int a[maxl];
int dp[2][maxn];
using ll = long long;
bitset<maxn> adj[maxn];
char tr[maxl][maxn];
int n, s, g, l;


int main() {
	scanf("%d%d%d", &n, &s, &g);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < s; ++j) {
			scanf("%1d", mat[i]+j);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int sum = 0;
			for (int k = 0; k < s; ++k) {
				sum += mat[i][k] != mat[j][k];
			}
			adj[i][j] = sum <= g;
		}
	}
	scanf("%d", &l);
	for (int i = 0; i < l; ++i) {
		scanf("%d", a+i); a[i] -= 1;
	}
	for (int i = 0; i < n; ++i) dp[0][i] = i!=a[0];
	for (int i = 1; i < l; ++i) {
		vector<pair<int, int>> r;
		for (int j = 0; j < n; ++j) {
			r.emplace_back(dp[i&1^1][j], j);
		}
		sort(r.begin(), r.end());
		bitset<maxn> use; use.set();
		for (int j = 0; j < n; ++j) {
			bitset<maxn> temp = use & adj[r[j].second];
			for(int k=temp._Find_first(); k<temp.size() && k < n; k=temp._Find_next(k)) {
				dp[i&1][k] = r[j].first + (k != a[i]);
				tr[i][k] = r[j].second;
			}
			use = use & ~temp;
		}
	}
	int ans = 1e9, idx = -1;
	for (int i = 0; i < n; ++i) {
		if (ans > dp[l&1^1][i]) {
			idx = i;
			ans = dp[l&1^1][i];
		}
	}
	vector<int> sol = {idx + 1};
	for (int i = l-1; i > 0; --i) {
		idx = tr[i][idx];
		sol.push_back(idx + 1);
	}
	printf("%d\n", ans);
	reverse(sol.begin(), sol.end());
	for (int v : sol) printf("%d ", v);
	puts("");
	return 0;
}
