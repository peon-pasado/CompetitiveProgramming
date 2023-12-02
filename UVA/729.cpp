/**
 * @idea use backtracking to generate secuence.
 * 
**/

#include <bits/stdc++.h>
using namespace std;

char s[20];
int n;
void gen(int pos, int k) {
    if (pos == n) {
        if (k == 0) {
            s[n] = 0;
            cout << s << '\n';
        }
        return;
    } 
    s[pos] = '0';
    gen(pos+1, k);
    if (k > 0) {
        s[pos] = '1';
        gen(pos+1, k-1);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while (t--) {
        int k;
        cin>>n>>k;
        gen(0, k);
        if (t) cout<<'\n';
    }
    return 0;
}