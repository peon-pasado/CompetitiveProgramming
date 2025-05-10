#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi num, st;
vector<vector<pii>> ed;
vector<int> w, dis;

int Time;

int dfs(int at, int par) {
	int me = num[at] = ++Time, e, y, top = me;
	trav(pa, ed[at]) if (pa.second != par) {
		tie(y, e) = pa;
		if (num[y]) {
			top = min(top, num[y]);
			//if (num[y] < me)
			//	st.push_back(e);
		} else {
			//int si = sz(st);
			int up = dfs(y, e);
			top = min(top, up);
			if (up == me) {
				//st.push_back(e);
				//f(vi(st.begin() + si, st.end()));
				//st.resize(si);
			}
			else if (up < me) {
			    //st.push_back(e);
			} else { 
			    /* e is a bridge */ 
			    w[e] = 1;
			}
		}
	}
	return top;
}

void bicomps() {
	num.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1);
}

pii bfs(int x) {
    deque<int> Q;
    dis.assign(ed.size(), 1e9);
    dis[x] = 0;
    Q.push_front(x);
    int q;
    while (!Q.empty()) {
        q = Q.front(); Q.pop_front();
        for (auto e : ed[q]) {
            if (dis[q] + w[e.second] < dis[e.first]) {
                dis[e.first] = dis[q] + w[e.second];
                if (w[e.second] == 0) {
                    Q.push_front(e.first);
                } else {
                    Q.push_back(e.first);
                }
            }   
        }
    }
    return {q, dis[q]};
}


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        ed.resize(n);
        for (int i = 0; i < n; ++i) {
            ed[i].clear();
        }
        w.assign(m, 0);
        int eid = 0;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            ed[a].emplace_back(b, eid);
            ed[b].emplace_back(a, eid++);
        }
        bicomps();
        cout << accumulate(all(w), 0) - bfs(bfs(0).first).second << '\n';   
    }
	return 0;
}
