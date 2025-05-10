#include <bits/stdc++.h>
using namespace std;

vector<int> masks;
int n, m;

set<vector<int>> res;

void add(int x) {
    vector<int> tmp;
    for (int i=0; i<n; ++i) {
        if (x & (1<<i)) {
            tmp.push_back(i+1);
        }
    }
    res.insert(tmp);
}   

unordered_set<int> Q[2];

void bfs() {
    Q[0].insert(0);
    int tt = 0;
    while (!Q[0].empty()) {
        tt++;
        map<int, int> tmp;
        for (auto s : Q[0]) {
            for (int i=0; i<n; ++i) {
                if (s & (1<<i)) continue;
                tmp[s | (1<<i)]++;
            }
        }
        for (auto se : tmp) {
            int s = se.first;
            if (se.second != tt) continue;
            int cnt = 0;
            for (int i=0; i<m; ++i) {
                if ((masks[i] & s) == s) {
                    cnt++;
                }
                if (5 * cnt >= m) break;
            }
            if (5 * cnt >= m) Q[1].insert(s);
        }
        for (auto s : Q[0]) {
            bool nxt = 0;
            for (int i=0; i<n; ++i) {
                if (s & (1<<i)) continue;
                if (Q[1].count(s | (1<<i))) {
                    nxt = 1;
                    break;
                }
            }
            if (!nxt) add(s);
        }
        swap(Q[0], Q[1]);
        Q[1].clear();
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    for (int tc=1; tc<=t; ++tc) {
        cin>>n>>m;
        masks.clear();
        res.clear();
        for (int i=0; i<m; ++i) {
            int k;
            cin>>k;
            int mask = 0;
            for (int j=0; j<k; ++j) {
                int id;
                cin>>id;
                mask |= (1<<id-1);
            }
            masks.push_back(mask);
        }
        bfs();
        cout<<"Case " << tc << ": ";
        cout<<res.size()<<'\n';
        for (auto s : res) {
            for (int i = 0; i<s.size(); ++i) {
                cout << s[i] << " \n"[i+1==s.size()];
            }
        }
        cout<<'\n';
    }
    return 0;
}