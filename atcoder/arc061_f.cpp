/**
 * @author Miguel Mini
 * @tag combinatorics 
 * @idea
 *      - we can transform the problem:
 * 
 *          "given a sequence, count the
 *          number of ABC-strings with a 
 *          prefix with last character A and 
 *          #A = n, #B <= m and #C <= k".
 * 
 *      - fix A is comb(i-1, n-1).
 * 
 *      - others n+m+K-i characters can
 *      be of 3^{n+m+k-i} ways.
 * 
 *      - we can fix B and C with the following
 *      summation:
 * 
 *          \sum_{max(0, i-n-k)}^{m} comb(i-n, j)
 * 
 *      - we can preprocess this sum with 
 *          two sums:
 * 
 *          \sum_{0}^{m} comb(i-n, j)
 * 
 *      and
 * 
 *          \sum_{0}^{i-n-k-1} comb(i-n, j)
 * 
 *      - first summation is:
 * 
 *          s(0, m) = 1
 *          s(i-n, m) = 2 * s(i-n-1, m) - comb(i-n-1, m)    
 * 
 *      - second is:
 * 
 *          d(i-n, 0) = 1
 *          d(i-n, i-n-k-1) = 2 * d(i-n-1, i-n-k-2) + comb(i-n-2, i-n-k-1)     
 * 
 * @complexity O(n+m+K)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
int f[maxn], pot[maxn];
int r[maxn], rf[maxn];

int add(int a, int b) {
	return (a+b)%mod;
}

int mul(long long a, long long b) {
	return a*b%mod;
}

int comb(int n, int m) {
	if (m > n) return 0;
	return mul(f[n], mul(rf[m], rf[n-m]));
}

int val = 0;
int next_s(int i, int m) {
	if (i == 0) return val = 1;
	return val = add(add(val, val), mod - comb(i-1, m));
}

int val2 = 0;
int next_d(int n, int m) {
	if (m == 0) return val2 = 1;
	return val2 = add(add(val2, val2), comb(n-1, m));
}

int main() {
	pot[0] = f[0] = rf[0] = r[1] = 1;
	for (int i = 1; i < maxn; ++i) {
		if (i > 1) r[i] = mul(r[mod%i], mod - mod/i);
		f[i] = mul(i, f[i-1]);
		rf[i] = mul(r[i], rf[i-1]);
		pot[i] = mul(pot[i-1], 3);
	}
	int n, m, k;
	cin >> n >> m >> k;
	int ans = 0;
	for (int i = n; i <= n+k+m; ++i) {
		ans = add(ans, mul(mul(comb(i-1, n-1), next_s(i-n, m)), pot[n+m+k-i]));
	}
	for (int i = n+k+1; i <= n+k+m; ++i) {
		ans = add(ans, mul(mod - mul(comb(i-1, n-1), next_d(i-n, i-n-k-1)), pot[n+m+k-i]));
	}
	cout << ans << endl;
	return 0;
}