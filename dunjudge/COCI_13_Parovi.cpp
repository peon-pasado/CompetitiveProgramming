/**
 *  @author Miguel Mini
 *  @tag implementation, brute_force
 *  @idea:
 *      - we can solve for each digit
 *
 *      - solve the difference: 
 *        solve(B) - solve(A - 1)
 *
 *      - the number of digits d in 
 *      position i with numbers from
 *      0 to X is:
 *
 *        floor(X / 10^{i+1}) * 10^i 
 *        + (10^i | if X[i] > d) 
 *        + (X % 10^{i+1} + 1 - d * 10^i | if X[i] == d)  
 *
 *      - use bruteforce with fixed position
 *      and digits.
**/

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

vector<vector<int>> solve(string X) {
	int ans = 0;
	int inv10 = (7ll*mod + 1) / 10;
	int t = 1;
	for (auto d : X) ans = (ans*10ll+d-'0') % mod;
	int sub = 0;
	reverse(X.begin(), X.end());
	vector<vector<int>> mat(X.size(), vector<int>(10)); 
	for (int i = 0; i < X.size(); ++i) {
		sub = (sub + (X[i] - '0')*1ll*t%mod)%mod;
		ans = (ans + mod - (X[i] - '0')*1ll*t%mod)%mod;
		int tans = ans*1ll*inv10%mod;
		for (int k = 0; k < 10; ++k) {
			mat[i][k] = tans;
			if (X[i] - '0' > k) {
				mat[i][k] = (mat[i][k] + t) % mod;
			} else if (X[i] - '0' == k) {
				mat[i][k] = ((mat[i][k] + sub + 1)%mod + mod - k *1ll* t%mod)%mod;
			}
		}
		t = t * 10ll % mod;
	}
	return mat;
}

int main() {
	string A, B;
	cin >> A >> B;
	reverse(A.begin(), A.end());
	A.resize(B.size(), '0');
	reverse(A.begin(), A.end());
	vector<vector<int>> cnt = solve(B);	
	vector<vector<int>> temp = solve(A);
	for (int k = 0; k < B.size(); ++k) {
		for (int i = 0; i < 10; ++i) {
			cnt[k][i] = (cnt[k][i] + mod - temp[k][i]) % mod;
		}
	}
	for (int i = 0; i < A.size(); ++i) {
		int& t = cnt[(int)A.size()-i-1][A[i]-'0']; 
		t = (t + 1) % mod;
	}
	int ans = 0;
	for (int i = 0; i < B.size(); ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k=0; k < 10; ++k) {
				int temp = abs(j - k)*1ll*(cnt[i][k]*1ll*cnt[i][j]%mod)%mod; 
				ans = (ans + temp)%mod;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
