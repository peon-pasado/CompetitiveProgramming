#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1e4 + 10;
int B, N;
struct data {
	int node, a, b;
};
vector<data> G[MAXN];
vector<int> order;
bool vis[MAXN];
int cost[MAXN], pre[MAXN];
bool best[MAXN];
long long val[MAXN];

void topo(int x) {
	vis[x] = 1;
	for (auto v : G[x])
		if (not vis[v.node])
			topo(v.node);
	order.emplace_back(x);
}


int main() {

	while(cin >> B >> N) {
	
		map<string, int> id; 
		string p, q, r;
		int a, b;
		int elem = 0;
		
		for (int i = 0; i < 10000; ++i) G[i].clear();
		for (int i = 1; i <= N; ++i) {
			cin >> p >> q >> r >> a >> b;
			if (not id.count(p)) id[p] = elem++;
			if (not id.count(q)) id[q] = elem++;

			G[id[q]].push_back({id[p], b, a});
		}

		order.clear();
		for (int i = 0; i < elem; ++i) vis[i] = 0;
		for (int i = 0; i < elem; ++i)
			if (not vis[i]) topo(i);

	
		reverse(order.begin(), order.end());
		for (int i = 0; i < elem; ++i) {
			cost[i] = 100000;
			pre[i] = 0;	
			vis[i] = 0;
		}
		for (int i = 0; i < elem; ++i) {
			int x = order[i];

			if (not vis[x]) cost[x] = 0;

			for (auto v : G[x]) {
				vis[v.node] = 1;
				if (cost[v.node] > cost[x] + v.b) {
					cost[v.node] = cost[x] + v.b;
					pre[v.node] = pre[x] + v.a;
				} else if (cost[v.node] == cost[x] + v.b) {
					pre[v.node] = max(pre[v.node], pre[x] + v.a);
				}
			}
		}


		memset(best, 0, sizeof best);
		best[0] = 1; val[0] = 0;
		for (int i = 0; i < elem; ++i)
			if (cost[i] == 0) val[0] += pre[i];

		for (int i = 0; i < elem; ++i) {
			if (cost[i] == 0) continue;
			for (int j = B; j >= cost[i]; --j) {
				if (best[j-cost[i]]) {
					if (best[j]) val[j] = max(val[j], val[j-cost[i]] + pre[i]);
					else best[j] = 1, val[j] = val[j-cost[i]] + pre[i];
				}
			}
		}

		int c = 0;
		long long ans = -1;
		for (int i = 0; i <= B; ++i) {
			if (best[i]) {	
				if (ans < val[i]) ans = val[i], c = i;
			}
		}

		printf("%lld\n%d\n", ans, c);
	}

	return 0;
}