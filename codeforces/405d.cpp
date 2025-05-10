#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6 + 10;
bool vis[maxN];
int n;
int main() {
	int s = 1e6;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		vis[x] = 1;
	}
	vector<int> sol;
	queue<int> q;
	int pending = 0;
	for (int i = 1; i+i <= s; ++i) {
		if (vis[i] and not vis[s+1-i]) {
			sol.push_back(s+1-i);
		}
		if (not vis[i] and vis[s+1-i]) {
			sol.emplace_back(i);
		}
		if (not vis[i] and not vis[s+1-i]) {
			q.emplace(i);
			q.push(s+1-i);
		}
		if (vis[i] and vis[s+1-i]) {
			pending += 1;
		}
	}
	while (not q.empty() and pending) {	
		sol.emplace_back(q.front()); q.pop();
		sol.emplace_back(q.front()); q.pop();
		pending -= 1;	
	}
	printf("%d\n", (int)sol.size());
	for (int e : sol) {
		printf("%d ", e);
	} puts("");
	return 0;
}