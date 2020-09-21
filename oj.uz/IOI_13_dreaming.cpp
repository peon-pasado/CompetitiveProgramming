/**
 * @author Miguel Mini
 * @tag dp, rerooting, diameter, greedy
 * @idea
 *    - We can see that it is always convenient
 *    for us to join the trees in the center, 
 *    this can be seen for two and tested for 
 *    k by induction.
 *
 *    - luego si yo uniera el que tiene el radio
 *    mayor con cualquier otro, entonces el nuevo 
 *    radio seria max(min_radius + L, max_radius). 
 *
 *    - then the radius will be the maximum of all 
 *    the radius smaller than the greater + L, or 
 *    the greater.
 *
 *    - the final diameter is therefore defined in 
 *    the 3 largest radius. Note that the problem 
 *    can be solved in O(n) to find the 3 largest.
**/

#include <bits/stdc++.h>
#include "dreaming.h"
using namespace std;

const int maxn = 1e5 + 10;
vector<pair<int, int>> g[maxn];
pair<int, int> len[maxn];
bool vis[maxn];
int arr[maxn];
int k = 0;

void add(int x, int t) {
	if (t >= len[x].first) {
		len[x].second = len[x].first;
		len[x].first = t;
	} else {
		len[x].second = max(len[x].second, t);
	}
}

void dfs(int x, int p) {
	vis[x] = 1;
	len[x] = {0, 0};
	for (auto e : g[x]) {
		if (e.first == p) continue;
		dfs(e.first, x);
		add(x, len[e.first].first+e.second);
	}
}

int dfs_reroot(int x, int p, int r) {
	if (p != -1) {
		if (len[p].first == len[x].first+r) {
			add(x, len[p].second+r);
		} else {
			add(x, len[p].first+r);
		}
	}
	int ans = len[x].first;
	for (auto e : g[x]) {
		if (e.first == p) continue;
		ans = min(ans, dfs_reroot(e.first, x, e.second));
	}
	return ans;
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
	for (int i=0; i<N; ++i) g[i].clear(), vis[i] = 0;
	for (int i=0; i<M; ++i) {
		g[A[i]].emplace_back(B[i], T[i]);
		g[B[i]].emplace_back(A[i], T[i]);
	}
	for (int i=0; i<N; ++i) {
		if (vis[i]) continue;
		dfs(i, -1);
		arr[k++] = dfs_reroot(i, -1, 0);
	}
	int ans = 0;
	for (int i = 0; i < N; ++i) ans = max(ans, len[i].first + len[i].second);
	sort(arr, arr+k, greater<int>());
	if (k >= 2) ans = max(ans, arr[0] + arr[1] + L);
	if (k >= 3) ans = max(ans, arr[1] + arr[2] + 2 * L);
	return ans;
}
