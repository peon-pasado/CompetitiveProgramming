#include <iostream>
using namespace std;

const int MAXN = 5005;
const int mod = 1e9+7;
int add(int a, int b) {
	return (a+b)%mod;
}
int mul(long long a, long long b) {
	return a*b%mod;
}

int dp[MAXN][MAXN];
int S[MAXN];
const int p = 257;
string s;

int main() {
	
	cin >> s;
	for (int i = 0; i < s.size(); ++i) {
		int H = 0, R = 0;
		int P = 1;
		for (int j = i; j < s.size(); ++j) {
			H = add(H, mul(s[j], P)), P = mul(P, p); 
			R = add(mul(R, p), s[j]);
			
			if (i == j) dp[i][j] = 1;
 			else dp[i][j] = H == R ? dp[i][i + ((j-i>>1)-((j-i)%2==0))] + 1: 0;
			
			S[dp[i][j]] += 1;
		}
	}
	
	for (int i = (int)s.size()-2; i >= 0; --i)
		S[i] += S[i+1];
	
	for (int i = 1; i <= s.size(); ++i)
		cout << S[i] << " "; cout << endl;
	
	
	return 0;
}