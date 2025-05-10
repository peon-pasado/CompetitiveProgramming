#include <bits/stdc++.h>
using namespace std;

vector<int> r;
void bt(int M) {
    if (M == 0) {
        cout<<r.size()<<'\n';
        reverse(r.begin(), r.end());
        for (auto v : r) cout << v << ' ';
        cout << '\n';
        exit(0);
        return;
    }
    int t = 1;
    int s = 0;
    while (3 * t <= M) {
        t *= 3;
        s++;
    }
    r.push_back(s);
    bt(M - t);
}

int main() {
    int n, q;
    cin>>n>>q;
    string s;
    cin>>s;
    int res = 0;
    for (int i=0; i+2<n; ++i) {
        if (s[i] == 'A' && s[i+1]=='B' && s[i+2]=='C') {
            res++;
        }
    }
    for (int i=0; i<q; ++i) {
        int x;
        char c;
        cin>>x>>c;
        x--;
        for (int j = max(x-2, 0); j <= x; ++j) {
            if (s[j] == 'A' && s[j+1]=='B' && s[j+2]=='C') {
                res--;
            }
        }
        s[x] = c;
        for (int j = max(x-2, 0); j <= x; ++j) {
            if (s[j] == 'A' && s[j+1]=='B' && s[j+2]=='C') {
                res++;
            }
        }
        cout <<res<<'\n';
    }   
    return 0;
}