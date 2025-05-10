#include <bits/stdc++.h>
using namespace std;

int main() {
    string t;
    int n;
    cin>>n >> t;
    vector<int> res;
    for (int j=1; j<=n; ++j) {
        string s;
        cin>>s;
        if (abs((int)t.size() - (int)s.size()) > 1) {
            continue;
        }
        string tt = t;
        if (s == t) {
            res.push_back(j);
        } else {
            if (s.size() == t.size()) {
                int d = 0;
                for (int i=0; i<s.size(); ++i) {
                    d += s[i] == t[i];
                }
                if (d + 1 == s.size()) {
                    res.push_back(j);
                }
            } else {
                if (s.size() == t.size() + 1) {
                    swap(s, t);
                }
                int m = s.size();
                vector<int> l(m + 2), r(m + 2);
                for (int i=1; i<=m; ++i) {
                    l[i] = l[i-1] + (s[i-1] == t[i-1]);
                }
                for (int i=m; i >= 1; --i) {
                    r[i] = r[i+1] + (s[i-1] == t[i]);
                }
                for (int i=1; i<=m+1; ++i) {
                    //cout << l[i-1] + r[i] << ' '; 
                    if (l[i - 1] + r[i] == m) {
                        res.push_back(j);
                        break;
                    }
                }
            }
        }
        t = tt;
    }
    cout << res.size() << '\n';
    for (int v : res) {
        cout << v << ' ';
    }
    cout << '\n';
    return 0;
}