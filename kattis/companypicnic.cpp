#include <bits/stdc++.h>
#define double float
using namespace std;

typedef pair<int, double> ii;
const int MAXN = 1e3 + 10;
vector<int> g[MAXN];
ii dp[MAXN][2];
double c[MAXN];
int n;

ii ss(ii v, ii u) {
	return {v.first + u.first, v.second + u.second};
}

ii rr(ii v, ii u)  {
	return {v.first - u.first, v.second - u.second};
}


ii dfs(int x, int p) {

	for (auto v : g[x])
		if (v != p) {
			dfs(v, x);
		}

	ii sum = {0, 0.}; 
	for (auto v : g[x])
		if (v != p) {
			sum = ss(sum, max(dp[v][0], dp[v][1]));
		}

	dp[x][0] = sum;
	for (auto v : g[x]) {
		if (v != p) {
			dp[x][1] = max(dp[x][1], ss(ss(rr(sum, max(dp[v][0], dp[v][1])), dp[v][0]), {1, min(c[x], c[v])}));
		}
	}

	return max(dp[x][0], dp[x][1]);
}


int main() {

	int t = 1;
	map<string, int> id;

	scanf("%d\n", &n);
	string a, b;
	double s;
	string ceo;
	for (int i = 0; i < n; ++i) {
		cin >> a >> s >> b;
			
		if (b == "CEO") ceo = a;
		if (not id.count(a)) id[a] = t++;
		if (b!="CEO" and not id.count(b)) id[b] = t++;
	
		c[id[a]] = s;

		if (b != "CEO") {
			g[id[a]].push_back(id[b]);
			g[id[b]].push_back(id[a]);
		}
	}

	auto q = dfs(id[ceo], 0);
	printf("%d %.4f\n", q.first, q.second/q.first);
	return 0;
}