/**
 * @idea backtracking + IEP
 * 
 *  - we can count the number of elements
 *  with n restrictions.
 * 
 *  - we can solve with IEP for intersection of restrictions,
 *  
 *  xi <= ri -> ri < x  <-> ri+1 <= x and reduce ri+1 in final sum.
 * 
 *  - final problem is a combinatorial problem x1+...xn = s'
 * 
 *      answer is \binom{s' + n - 1}{n - 1}
 * 
 *  note that binomial coefficient take O(n) for calculation.
 * 
 *  final complexity: O(2^n x n)
**/

#include <bits/stdc++.h>
using namespace std;
 
const int N = 23;
const int MOD = 1000000007;
long long f[N], s;
int dp[N];
int n;
 
int expfast(long long n, int m){
	int r = 1;
	while(m){
		if(m&1) r = r*n%MOD;
		n = n*n%MOD;
		m >>= 1;
	}
	return r;
}
 
int C(long long n, int k){
	if(n < k) return 0;
	int ans = 1;
	for(int i = 0; i < k; ++i)
		ans = ans*((n-i+MOD)%MOD)%MOD;
	return 1LL*ans*dp[k]%MOD;
}

int main(){
	dp[0] = 1;
	for(int i = 1; i < N; ++i)	
		dp[i] = 1LL*dp[i-1]*expfast(i, MOD-2)%MOD; 
	cin >> n >> s;
	for(int i = 0; i < n; ++i) {
		scanf("%lld", f+i);
    }
    auto bt = [&](auto&& bt, int pos, long long sum) {
        if (pos == n) return C(s - sum + n - 1, n - 1);
        return (bt(bt, pos+1, sum) + MOD - bt(bt, pos+1, sum+f[pos]+1)) % MOD;
    };
	cout << bt(bt, 0, 0) << endl;
	return 0;
}