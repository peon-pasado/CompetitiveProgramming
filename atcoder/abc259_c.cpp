#include <bits/stdc++.h>
using namespace std;

bool verify(string& s, string& t, int ls, int lt) {
    if (ls == s.size() && lt == t.size()) return 1;
    if (ls == s.size()) return 0;
    if (lt == t.size()) return 0;
    if (s[ls] != t[lt]) return 0;

    //cout << s[ls] << ' ' << t[lt] << endl;

    int cs = 1, ct = 1;
    while (ls + 1 < s.size() && s[ls] == s[ls + 1]) ls++, cs++;
    while (lt + 1 < t.size() && t[lt] == t[lt + 1]) lt++, ct++;

    if (cs > ct) return 0;
    if (cs == ct) return verify(s, t, ls+1, lt+1);
    if (cs < ct) {
        if (cs == 1) return 0;
    }
    return verify(s, t, ls+1, lt+1);
}

int main() {
    string s, t;
    cin>>s>>t;
    if (s.size() > t.size()) {
        cout << "No\n";
        return 0;
    }
    if (verify(s, t, 0, 0)) cout << "Yes\n";
    else cout << "No\n";

    return 0;
}