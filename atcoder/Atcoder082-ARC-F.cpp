/**
 * @author Miguel Mini
 * @tag slope_function, sweep_line
 * @idea
 *      - we can maintain the function
 *      for every initial position a.
 * 
 *      - we can update function in 
 *      O(1).
 * 
 *      - notice that function is monotone
 *      with 3 slopes.
 * 
 * @complexity O(k + q)
 */ 

#include <bits/stdc++.h>
using namespace std;

int X, k;

struct F {
    int l, m, r;
    int a, b, c;

    void sub(int x) {
        if (c <= x) {
            l = l + m + r;
            m = r = 0;
            a = b = c = 0;
        } else if (x <= a) {
            a -= x;
            b -= x;
            c -= x;
        } else {
            int d = x-a;
            a = 0;
            b -= x;
            c -= x;
            l += d;
            m -= d;
        }
    }

    void add(int x) {
        if (a + x >= X) {
            r = l + m + r;
            m = r = 0;
            a = b = c = X;
        } else if (c + x <= X) {
            a += x;
            b += x;
            c += x;
        } else {
            int d = c+x-X;
            a += x;
            b += x;
            c = X;
            r += d;
            m -= d;
        }
    }

    int get(int x) {
        if (x <= l-1) return a;
        if (x <= m+l-1) return x+b;
        return c;
    }
};

int main() {
    cin >> X >> k;
    vector<int> r(k + 1);
    for (int i = 1; i <= k; ++i) {
        cin >> r[i];
    }
    F func = {0, X+1, 0, 0, 0, X};
    int q;
    cin >> q;
    int i = 1;
    bool op = 1;
    while (q--) {
        int t, a;
        cin >> t >> a;
        while (i <= k && r[i] <= t) {
            if (op) func.sub(r[i]-r[i-1]);
            else func.add(r[i]-r[i-1]);
            op ^= 1;
            i++;
        }
        int q = func.get(a);
        int p = t - r[i-1];
        if (op) q = max(0, q-p);
        else q = min(X, q+p);
        cout << q << '\n';
    }
    return 0;
}