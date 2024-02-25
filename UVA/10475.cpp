/**
 * @idea backtracking
 * 
 * - simule with backtracking (take / dont take)
 * - careful with the upper case
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 16;
int n, m, s;
int mat[maxn];
string name[maxn];

void dfs(int pos, int mask, int nmask, int t) {
    if (t > s) return;
    if (pos == n) {
        if (t < s) return;
        int r = 0;
        for (int i=0; i<n; ++i) {
            if (mask & (1<<i)) {
                cout << name[i] << " \n"[++r==s];
            }
        }
        return;
    } 
    if (~nmask & (1<<pos)) {
        dfs(pos+1, mask|(1<<pos), nmask|mat[pos], t+1); 
    }
    dfs(pos+1, mask, nmask, t);
}

int main() {
    int t;
    cin>>t;
    int tc=1;
    while (t--) {
        cin>>n>>m>>s;
        vector<string> ss;
        for (int i=0; i<n; ++i) {
            cin>>name[i];
            for (auto& c : name[i]) c = toupper(c);
            ss.push_back(name[i]);
        }
        sort(ss.begin(), ss.end(), [](string p, string q) {
            if (p.size() != q.size()) return p.size() > q.size();
            return p < q;
        });
        map<string, int> cnt;
        int r=0;
        for (auto s : ss) cnt[s] = r++;
        for (auto pp : cnt) {
            name[pp.second] = pp.first;
        }
        memset(mat, 0, sizeof mat);
        for (int i=0; i<m; ++i) {
            string u, v;
            cin>>u>>v;
            for (auto& c : u) c = toupper(c);
            for (auto& c : v) c = toupper(c);
            int x = cnt[u];
            int y = cnt[v];
            mat[x] |= 1<<y;
            mat[y] |= 1<<x;
        }
        cout << "Set " << tc++ << ":" << '\n'; 
        dfs(0, 0, 0, 0);
        cout << '\n';
    }
    return 0;
}