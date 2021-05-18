/**
 * @author Miguel Mini
 * @tag kmp, greedy, fibonacci
 * @idea
 *      - we have two cases:
 * 
 *          1. minimum period divide |s|.
 * 
 *              final string is t^{\infty}
 * 
 *              where t is prefix min period.
 * 
 *          2. minimum period doesnt divide |s|.
 * 
 *              observe that f(2 x S) = 2 x (S + t) 
 * 
 *              new string has period S, thus
 * 
 *              f^2(2 x S) = 2 x (S + t + S) 
 * 
 *              and period is S + t ...
 * 
 *              we can see that:
 * 
 *                   f^m(2 x S) = 2 x (f^{m-1}(S) + f^{m-2}(S))
 * 
 *              first half have fibonacci pattern.
 *      
 * @complexity O(n + log(r) x sigma)
 */ 

#include <bits/stdc++.h>
using namespace std;

int kmp(string& s) {
	int n = s.size();
	vector<int> b(n + 1);
	b[0] = -1;
	for (int i = 1; i <= n; ++i) {
		int	j = b[i-1];
		while (~j && s[j] != s[i-1]) j = b[j];
		b[i] = j+1;
	}
	return n - b[n];
}

long long f[100];
long long cc[100][26];
vector<long long> get(string s, long long r) {
	vector<long long> cnt(26);
	int n = 0;
	while (f[n] <= 1e18) n++;
	for (int i = n-1; i >= 0; --i) {
		if (r < f[i]) continue;
		r -= f[i];
		for (int j = 0; j < 26; ++j) {
			cnt[j] += cc[i][j];
		}
	}
	for (int i = 0; i < r; ++i) {
		cnt[s[i] - 'a'] += 1; 
	}
	return cnt;
}

int main() {
	string s;
	cin >> s;
	s.resize(s.size() / 2);
	int t = kmp(s);
	long long l, r;
	cin >> l >> r;
	int n = s.size();
	f[0] = n;
	for (int i = 0; i < n; ++i) {
		cc[0][s[i] - 'a'] += 1;	
	}
	f[1] = n+t;
	for (int i = 0; i < 26; ++i) {
		cc[1][i] = cc[0][i];
	}
	for (int i = 0; i < t; ++i) {
		cc[1][s[i] - 'a'] += 1;
	}
	for (int i = 2; i < 100; ++i) {
		f[i] = f[i-1] + f[i-2];
		for (int j = 0; j < 26; ++j) {
			cc[i][j] = cc[i-1][j] + cc[i-2][j];	
		}
	}
	auto R = get(s, r);
	auto L = get(s, l-1);
	for (int i = 0; i < 26; ++i) {
		R[i] -= L[i];
		cout << R[i] << " ";
	}
	cout << endl;
	return 0;
}
