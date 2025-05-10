#include <bits/stdc++.h>
using namespace std;

bool sq[10000 + 1];
multiset<int> r;
int n;
set<multiset<int>> s; 

int ans = 0;
void bt(int m) {
    if (s.count(r)) return;
    bool ok = 0;
    if (!r.empty()) {
        vector<int> tmp;
        for (int v : r) {
            if (sq[v + m]) {
                ok = 1;
                tmp.push_back(v);
            }
        }
        for (int v : tmp) {
            r.erase(v);
            r.insert(m);
            bt(m + 1);
            r.erase(m);
            r.insert(v);
        }
     }
     if (ok) ans = max(ans, m);
     if (!ok && (int)r.size() < n) {
        ans = max(ans, m);
        r.insert(m);
        bt(m + 1);
        r.erase(m); 
    } 
}

int main() {
    for (int i=1; i*i <= 10000; ++i) {
        sq[i*i] = 1;
    }
    int t;
    cin>>t;
    while (t--) {
        cin>>n;
        r.clear();
        s.clear();
        ans = 0;
        bt(1);
        cout << ans << '\n';
    }
    return 0;
}