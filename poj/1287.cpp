#include <iostream>
#include <vector>
using namespace std;
const int maxn = 1e5 + 10;
pair<pair<int, int>, int> color[maxn];
bool check[maxn];
int n, m;
vector<pair<int, int> > g[maxn];
int p[maxn];
int rnk[maxn];

int get(int x) {return x == p[x] ? x : p[x] = get(p[x]);}
bool merge(int x, int y) {
	x = get(x); y = get(y);
	if (x == y) return 0;
	if (rnk[x] < rnk[y]) swap(x, y);
	rnk[x] += rnk[x] == rnk[y];
	p[y] = x;
}

int main() {
	while (cin >> n, n) {
		cin >> m;
		for (int i = 1; i <= n; ++i) g[i].clear();
		for (int i = 1; i <= m; ++i) {
			int a, b, w;
			cin >> a >> b >> w; 
			g[a].push_back(make_pair(b, w));
			g[b].push_back(make_pair(a, w));
		}
		for (int i = 1; i <= n; ++i) {
			p[i] = i;
			rnk[i] = 0;
		}
		int mst = 0;
		int arist = 0;
		while (true) {
			for (int i = 1; i <= n; ++i) check[i] = 0;	
			for (int x = 1; x <= n; ++x) {
				for (int j = 0; j < g[x].size(); ++j) {
					pair<int, int> node = g[x][j];
					if (get(x) != get(node.first)) {
						if (not check[get(x)]) {
							check[get(x)] = 1;
							color[get(x)] = {{x, node.first}, node.second};
						} else {
							if (color[get(x)].second > node.second) {
								color[get(x)] = {{x, node.first}, node.second};
							}
						}
					}
				}
			}
			bool fun = 0;
			for (int i = 1; i <= n; ++i) {
				if (check[i]) {
					fun = 1;
					if (get(color[i].first.first) != get(color[i].first.second)) {
						merge(color[i].first.first, color[i].first.second);
						arist += 1;
						mst += color[i].second;
					}
				}
			}
			if (not fun) break;
			if (arist == n-1) break;
		}
		cout << mst << endl;
	}
	return 0;
}
