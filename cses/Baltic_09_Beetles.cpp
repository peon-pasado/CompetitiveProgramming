/**
 *  @author Miguel Mini
 *  @tag dynamic programming, brute_force
 *  @idea
 *      - fix number of non zero used drops.  
 *      
 *      - solve with dp, dp[#negatives, #positives, op]:
 *      sum of times to traverse the closer #negative negative and
 *      #positive positive drops finish in op == 0 ? negative : positive
 *      
 *      - note that the best response is achieved in a continuous range.
 *
 *      - for a range with t elements, the dp is constructed by the two included 
 *      ranges of length t-1.
 *
 *      - final answer max(k * m - min(dp[l][r][0], dp[l][r][1]) with l + r >= k).
 *
 *  @complexity O(n^3).
**/


#include <bits/stdc++.h>
using namespace std;

const int maxn = 310;
int memo[maxn][maxn][2];
vector<int> xp, xn;
int n, m;

int main() {
	cin >> n >> m;
	xp.push_back(0);
	xn.push_back(0);
	int add = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		if (x < 0) xn.push_back(x);
		else if (x > 0) xp.push_back(x);
		else add += m;
	}
	sort(xn.rbegin(), xn.rend());
	sort(xp.begin(), xp.end());
	memo[0][0][0] = 0;
	memo[0][0][1] = 0;
	int res = 0;
	for (int k = 1; k <= n; ++k) {
		for (int len = 1; len < maxn; ++len) {
			for (int i = 0; i < min(len+1, (int)xn.size()); ++i) {
				int j = len - i;
				int tn = i + j;
				if (tn > k) break;
				if (j >= xp.size()) continue;
				if (j < 0) continue;
				for (int d = 0; d < 2; ++d) {
					int &ans = memo[i][j][d] = 2e9;
					for (int e = 0; e < 2; ++e) {
						int ni = d==0?i-1:i;
						int nj = d==0?j:j-1;
						if (ni == -1 || nj == -1) continue;
						auto temp = memo[ni][nj][e];
						int p = d==0?xn[i]:xp[j];
						int q = e==0?xn[ni]:xp[nj];
						temp += (k - tn + 1) * abs(p - q);
						ans = min(ans, temp);
					}
					if (tn == k) res = max(res, m * k - ans);
				}
			}
		}
	}
	cout << add + res << endl;
	return 0;
}
