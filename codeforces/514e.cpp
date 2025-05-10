#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxN = 100;
int n, x;
int cnt[maxN + 10];
int memo[maxN + 10];

int add(int a, int b) {
	return (a+b)%mod;
}

int mul(long long a, long long b) {
	return a * b % mod;
}

struct Matrix {
	vector<vector<int>> at;
	void zero() {
		at.clear();
		at.resize(maxN+1, vector<int>(maxN+1, 0));
	}		
	void one() {
		this->zero();
		for (int i = 0; i <= maxN; ++i) {
			at[i][i] = 1;
		}
	}
	Matrix operator *(const Matrix x) {
		Matrix R; R.zero();
		for (int i = 0; i <= maxN; ++i) {
			for (int j = 0; j <= maxN; ++j) {	
				for (int k = 0; k <= maxN; ++k) {
					R.at[i][j] = add(R.at[i][j], mul(at[i][k], x.at[k][j]));
				}
			}
		}
		return R;
	}
};

Matrix ex(Matrix A, int T) {
	Matrix R; R.one();
	while (T > 0) {
		if (T&1) R = R * A;
		A = A * A;
		T >>= 1;
	}
	return R;
}

int main() {
	cin >> n >> x;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		cnt[a] += 1;
	}
	memo[0] = 1;
	for (int i = 1; i <= maxN; ++i) memo[i] = cnt[i];
	for (int i = 1; i <= maxN; ++i) {
		for (int j = 1; i+j <= maxN; ++j) {
			memo[i + j] = add(memo[i + j], mul(memo[i], cnt[j])); 
		}
	}
	Matrix dp; dp.zero();
	for (int i = 0; i+1 < maxN; ++i) dp.at[i][i+1] = 1;
	for (int i = 0; i < maxN; ++i) dp.at[maxN-1][maxN-i-1] = cnt[i+1];
	dp.at[maxN][0] = dp.at[maxN][maxN] = 1;
	Matrix R = ex(dp, x);
	int ans = 0;
	for (int i = 0; i < maxN; ++i) {
		ans = add(ans, mul(memo[i+1], R.at[maxN][i]));
	}
	ans = add(ans, R.at[maxN][maxN]);
	cout << ans << endl;
	return 0;
}