#include <bits/stdc++.h>
using namespace std;

string min_n, max_n;
string res;
bool ok = 0;
void get_max(string& n, int pos, int k) {
    if (ok) return;
    if (n == max_n) {
        res = max_n;
        ok = 1;
        return;
    }
    if (pos+1 == n.size() || k == 0) {
        res = max(res, n);
        return;
    } 
    char mx = n[pos];
    for (int i=pos+1; i<n.size(); ++i)
        if (mx < n[i]) 
            mx = n[i];
    if (n[pos] == mx) {
        get_max(n, pos+1, k);
    } else {
        for (int i=pos+1; i<n.size(); ++i) {
            if (n[i] == mx) {
                swap(n[i], n[pos]);
                get_max(n, pos+1, k-1);
                swap(n[i], n[pos]);
            }
        }
    }
}

void get_min(string& n, int pos, int k) {
    if (ok) return;
    if (n == min_n) {
        res = min_n;
        ok = 1;
        return;
    }
    if (pos+1 == n.size() || k == 0) {
        res = min(res, n);
        return;
    } 
    char mx = n[pos];
    for (int i=pos+1; i<n.size(); ++i) {
        if (pos == 0 && n[i] == '0') continue;
        if (mx > n[i])  
            mx = n[i];
    }
    if (n[pos] == mx) {
        get_min(n, pos+1, k);
    } else {
        for (int i=pos+1; i<n.size(); ++i) {
            if (n[i] == mx) {
                swap(n[i], n[pos]);
                get_min(n, pos+1, k-1);
                swap(n[i], n[pos]);
            }
        }
    }
}


int main() {
    int t;
    cin>>t;
    while (t--) {
        string n;
        int k;
        cin>>n>>k;
        min_n = "";
        for (auto c : n) if (c != '0') min_n += c;
        sort(min_n.begin(), min_n.end());
        min_n.insert(min_n.begin() + 1, n.size() - min_n.size(), '0');
        max_n = n;
        sort(max_n.rbegin(), max_n.rend());
        if (k+1 >= n.size()) {
            cout << min_n << ' ' << max_n << '\n';
        } else {
            ok = 0;
            res = n;
            get_min(n, 0, k);
            cout << res << ' ';
            ok = 0;
            res = n;
            get_max(n, 0, k);
            cout << res << '\n';
        }
    }
    return 0;
}