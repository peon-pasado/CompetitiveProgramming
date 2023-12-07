/**
 * @idea backtracking
 * 
 * - simule sequence with backtracking
 * 
 * - verify in O(len^2), is enough.
 * 
 * - we can reduce complexity of check using z-algorithm.
 * in O(len) the check. 
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
char s[maxn], res[maxn];
int found;
int sz;
int n, l;

bool verify(int len) {
    //z algorithm is better
    for (int i = 1; i <= len / 2; ++i) {
        bool bad = 1;
        for (int j = 0; j < i; ++j) {
            if (s[len - 1 - j] != s[len - 1 - i - j]) {
                bad = 0; 
                break;
            }
        }
        if (bad) return 0;
    }
    return 1;
}

void bt(int pos) {
    found++;
    if (found == n + 1) {
        sz = pos;
        for (int i=0; i<sz; ++i) {
            res[i] = s[i];
        }
        return;
    }
    for (int i=0; i<l; ++i) {
        if (found == n + 1) return;
        s[pos] = 'A' + i;
        if (verify(pos + 1)) {
            bt(pos + 1);
        }
    }
}


int main() { 
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin>>n>>l, n+l) {
        found = 0;
        bt(0);
        for (int i=0; i<(sz+3)/4; ++i) {
            for (int j=0; j<4 && 4*i + j < sz; ++j) {
                cout << res[4*i+j];
            }
            if (i+1 == (sz+3)/4 || i % 16 == 15) cout << '\n';
            else cout << ' ';
        }
        cout << sz << '\n';
    }
    return 0;
}