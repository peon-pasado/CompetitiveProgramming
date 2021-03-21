/**
 * @author Miguel Mini
 * @tag multicase
 * @idea
 *      - operations are reversible
 *      only if string does not become
 *      empty.
 *
 *          1. A -> BB -> AAAA -> A
 *
 *          2. ABBB -> A -> BB -> AAB -> ABBB
 *
 *          3. BBBB -> B -> AA -> BBA -> BBBB
 *
 *      - all permutation are same string
 *
 *          - AB -> AAA -> BA
 *
 *      - solution: let be x(u) number of
 *      x in string u, then:
 *
 *          s ~ t iff (a(s), b(s)) ~ (a(t), b(t))
 *
 *      - relation in pairs is a partition.
 *
 *      - (x, y) ~ (0, 3 - (x-y mod 3))
 *
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    vector<int> cs(s.size());
    vector<int> ct(t.size());
    for (int i = 0; i < s.size(); ++i) {
        cs[i] = s[i] == 'A';
    }
    for (int i = 0; i < t.size(); ++i) {
        ct[i] = t[i] == 'A';
    }
    for (int i = 1; i < cs.size(); ++i) {
        cs[i] += cs[i-1];
    }
    for (int i = 1; i < ct.size(); ++i) {
        ct[i] += ct[i-1];
    }
    int q;
    cin >> q;
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        int as = cs[b];
        if (a > 0) as -= cs[a-1];
        int bs = (b-a+1)-as;

        int at = ct[d];
        if (c > 0) at -= ct[c-1];
        int bt = (d-c+1)-at;
        auto f = [](int x, int y) {
            y = 3 - ((x - y)%3 + 3)%3;
            return y;
        };
        if (f(as, bs) == f(at, bt)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}