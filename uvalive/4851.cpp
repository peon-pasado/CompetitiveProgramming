#include<bits/stdc++.h>
using namespace::std;

const int N = 60000 + 5;

int n;
int m;
int x[N];
int y[N];
int best[N];
int mini[N];
int maxi[N];

int solve(){
	int lx = x[0];
	int rx = x[1];
	if(lx > rx) swap(lx, rx);
	int ans = 0;
	int min_dis = -1;
	for(int i = 0; i < m; i++) best[i] = INT_MAX;
	for(int i = lx; i <= rx; i++){
		if(mini[i] >= 0) min_dis = min(min_dis, y[0] - mini[i] - 1);
		if(maxi[i] < m) min_dis = min(min_dis, maxi[i] - y[0] - 1);
		best[i] = min(best[i], min_dis);
		min_dis++;
	}
	min_dis = -1;
	for(int i = rx; i >= lx; i--){
		if(mini[i] >= 0) min_dis = min(min_dis, y[0] - mini[i] - 1);
		if(maxi[i] < m) min_dis = min(min_dis, maxi[i] - y[0] - 1);
		best[i] = min(best[i], min_dis);
		min_dis++;
	}
	for(int i = lx; i <= rx; i++){
		if(best[i] < 0) continue;
		int l = max(0, y[0] - best[i]);
		int r = min(m - 1, y[0] + best[i]);
		ans += r - l + 1;
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &m, &n);
		for(int i = 0; i < n; i++){
			scanf("%d %d", x + i, y + i);
		}
		for(int i = 0; i < m; i++) mini[i] = -1, maxi[i] = m;
		for(int i = 2; i < n; i++){
			if(y[i] <= y[0]) mini[x[i]] = max(mini[x[i]], y[i]);
			else maxi[x[i]] = min(maxi[x[i]], y[i]);
		}
		printf("%d\n", solve());
	}
	return 0;
}