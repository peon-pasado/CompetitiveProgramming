#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

int c3 (int a) {
	a = abs(a);
	return a*a*a;
}

int n;
bool valid(int x, int y) {
	return x >= 0 and x <= n and y >= 0 and y <= n;
}

int X[105];
int Y[105];
int Max[105][1000];
int Min[105][1000];
vector<pair<int, int>> adj[100005];

int main () {
	int k;
	scanf("%d %d", &n, &k);
	
	for (int i = 0; i < k; ++i)
		for (int j = -470; j <= 470; ++j)
			Max[i][j+470] = Min[i][j+470] = -10000;
	
	for (int i = 0; i < k; ++i) {
		int x, y, b;
		scanf("%d %d %d", &x, &y, &b);
		for (int dx = -470; dx <= 470; ++dx)
			for (int dy = -470; dy <= 470; ++dy) {
				if (valid(x+dx, y+dy) and c3(dx) + c3(dy) <= b) {
					if (Max[i][470+dx] == -10000) {
						Max[i][470+dx] = dy;
						Min[i][470+dx] = dy;
					} else {
						Max[i][470+dx] = max(Max[i][470+dx], dy);
						Min[i][470+dx] = min(Min[i][470+dx], dy);					
					}	
				}
			}
		X[i] = x;
		Y[i] = y;
	}
		
	map<int, int> id;
	int t = 0;
	for (int i = -470; i <= 470; ++i) {
		for (int j = 0; j < k; ++j)
			if (Max[j][470+i] != -10000 and not id.count(X[j] + i)) id[X[j]+i] = t++;
	} 		

	
	for (int i = -470; i <= 470; ++i) {
		for (int j = 0; j < k; ++j)
			if (Max[j][470+i] != -10000)
				adj[id[X[j]+i]].push_back({Y[j] + Min[j][470+i], Y[j] + Max[j][470+i]});
	} 
	
	int rest = 0;
	int maxr;
	for (int i = 0; i < t; ++i) {
		if (adj[i].empty()) continue;
		sort(adj[i].begin(), adj[i].end());
		maxr = -1;
		for (int j = 0; j < adj[i].size(); ++j) {
			int l = max(adj[i][j].first, maxr+1);
			int r = adj[i][j].second;			
			if (r >= l) rest += r-l+1;
			maxr = max(r, maxr);
		}
	}

	printf("%lld\n", (n+1)*1ll*(n+1) - rest);

	return 0;
}