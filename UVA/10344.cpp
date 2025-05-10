#include <bits/stdc++.h>
using namespace std;


int a[6];
int cal(int x, int y, int op) {
    if (op == 0) return x + y;
    if (op == 1) return x - y;
    if (op == 2) return x * y;
    abort();
}


bool gen(int mask, int pos, int val, int op) {
    if (pos == 9) return val == 23;
    bool ans = 0;
    if (pos & 1) {
        for (int i=0; i<3; ++i) {
            ans |= gen(mask, pos+1, val, i);
            if (ans) break;
        }
    } else {
        for (int i=0; i<5; ++i) {
            if (mask & (1<<i)) {
                ans |= gen(mask ^ (1<<i), pos+1, cal(val, a[i], op), -1);
                if (ans) break;
            }
        }
    }
    return ans;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (1) {
        for (int i=0; i<5; ++i) cin>>a[i];
        bool final_case = 1;
        for (int i=0; i < 5; ++i) final_case &= (a[i] == 0);
        if (final_case) break;
        if (gen(31, 0, 0, 0)) cout << "Possible" << '\n';
        else cout << "Impossible" << '\n';
    }
    return 0;
}