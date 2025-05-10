#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e4 + 5;
const int maxM = 1e2 + 5;
bool vis1[maxN][maxM], vis2[maxN][maxM];
int memo1[maxN][maxM], memo2[maxN][maxM];
int range[maxN];
int par[maxN];
string s;
int M, P;

int dpMin(int, int, int, int);

int dpMax(int l, int r, int m, int p) {
	if (l == r) return s[r]-'0';
	if (vis1[l][P<M?m:p]) return memo1[l][P<M?m:p];
	vis1[l][P<M?m:p] = 1;
	int ans = -1e9;
	int fl = isdigit(s[l+1]) ? l+1 : par[l+1];
	int h = range[fl+1] - range[l];
	if (m < p) {
		for (int i = 0; i <= min(h, m); ++i) {
			if (m >= i and p >= h-i) {
				 if (m >= i+1) ans = max(ans, dpMax(l+1, fl, i, h-i) + dpMax(fl+2, r-1, m-i-1, p-h+i));
				 if (p >= h-i+1) ans = max(ans, dpMax(l+1, fl, i, h-i) - dpMin(fl+2, r-1, m-i, p-h+i-1));
			}
		}
	} else {
		for (int i = 0; i <= min(h, p); ++i) {
			if (m >= h-i and p >= i) {
				 if (m >= h-i+1) ans = max(ans, dpMax(l+1, fl, h-i, i) + dpMax(fl+2, r-1, m-h+i-1, p-i));
				 if (p >= i+1) ans = max(ans, dpMax(l+1, fl, h-i, i) - dpMin(fl+2, r-1, m-h+i, p-i-1));
			}
		}
	}
	return memo1[l][P<M?m:p] = ans;
}

int dpMin(int l, int r, int m, int p) {
	if (l == r) return s[r]-'0';
	if (vis2[l][P<M?m:p]) return memo2[l][P<M?m:p];
	vis2[l][P<M?m:p] = 1;
	int ans = 1e9;
	int fl = isdigit(s[l+1]) ? l+1 : par[l+1];
	int h = range[fl+1] - range[l];
	if (m < p) {
		for (int i = 0; i <= min(h, m); ++i) {
			if (p >= h-i) {
				 if (m >= i+1) ans = min(ans, dpMin(l+1, fl, i, h-i) + dpMin(fl+2, r-1, m-i-1, p-h+i));
				 if (p >= h-i+1) ans = min(ans, dpMin(l+1, fl, i, h-i) - dpMax(fl+2, r-1, m-i, p-h+i-1));
			}
		}
	} else {
		for (int i = 0; i <= min(h, p); ++i) {
			if (m >= h-i) {
				 if (m >= h-i+1) ans = min(ans, dpMin(l+1, fl, h-i, i) + dpMin(fl+2, r-1, m-h+i-1, p-i));
				 if (p >= i+1) ans = min(ans, dpMin(l+1, fl, h-i, i) - dpMax(fl+2, r-1, m-h+i, p-i-1));
			}
		}
	}
	return memo2[l][P<M?m:p] = ans;
}

int main() {
	cin >> s;
	cin >> P >> M;
	stack<int> k;
	for (int i = 0; i < s.size(); ++i) {
		range[i+1] = range[i];
		char c = s[i];
		if (c == '(') k.push(i);
		else if (c == ')') par[k.top()] = i, k.pop();
		else if (c == '?') range[i+1] += 1;
	}
	printf("%d\n", dpMax(0, (int)s.size()-1, P, M));
	
	return 0;
}