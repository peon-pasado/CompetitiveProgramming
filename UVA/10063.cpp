#include <bits/stdc++.h>
using namespace std;

string s;
int nxt[30];
char t[30];

void bt(int pos, int f) {
    if (pos == (int)s.size()) {
        int p = 0;
        for (int e = f; ~e; e = nxt[e]) {
            t[p++] = s[e];
        }
        t[pos] = 0;
        cout << t << '\n';
        return;
    }
    int r = f, last = -1;
    for (int i=0; i<=pos; ++i) {
        if (last >= 0) nxt[last] = pos;
        nxt[pos] = r;
        bt(pos+1, i == 0 ? pos : f);
        if (last >= 0) nxt[last] = r;
        last = r;
        if (r >= 0) r = nxt[r];
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    nxt[0] = -1;
    bool fst = 1;
    while (cin>>s) {
        if (!fst) cout << '\n';
        fst = 0;
        bt(0, -1);
    }
    return 0;
}