/**
 * @author Miguel Mini
 * @tag dp, brute_force
 * @idea:
 *      - we can fix the first and last choice and then 
 *      solve with a dp(position, need_choice_left_right ?, last_choice).
 *
 *      - need_choice_left_right? : do I need to choose the right or 
 *      left plate or does it really not matter?
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int a[maxn];
bitset<maxn> memo[3][2];
bitset<maxn> tr[3][2];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a+i);
        a[i] <<= 1;
    }
    bool found = 0;
    for (int d : {0, 1}) {
        for (int e : {0, 1}) {
            if (found) break;
            //k = 0 (no tomar izquierda), 1 (no tomar derecha), 2 (no importa)
            for (int i = n; i >= 0; --i) {
                for (int k = 0; k < 3; ++k) {
                    for (int last = 0; last < 2; ++last) {
                        if (i == n) memo[k][last][i] = 1;
                        else {
                            bool ans = 0;
                            int left = a[i] >> last;
                            if (i < n-1) {
                                if (k != 0 && left >= a[i+1]/2) {
                                    if (memo[2 - (left < a[i+1])][0][i+1]) {
                                        tr[k][last][i] = 0;
                                        ans = 1;
                                    }
                                }
                                if (k != 1 && left <= a[i+1]) {
                                    if (memo[2 * (left <= a[i+1]/2)][1][i+1]) {
                                        tr[k][last][i] = 1;
                                        ans = 1;
                                    }
                                }
                            } else {
                                if (k != e) {
                                    tr[k][last][i] = e;
                                    int right = a[0]>>(1-d);
                                    if (e == 0) {
                                        if (left >= right) ans |= memo[2][e][i+1];
                                    } else {
                                        if (left <= right) ans |= memo[2][e][i+1];
                                    }
                                }
                            }
                            memo[k][last][i] = ans;
                        }
                    }
                }
            }
            bool ans = memo[1-d][e][0];
            if (ans) {
                found = 1;
                int k = 1 - d, last = e;
                for (int pos = 0; pos < n; ++pos) {
                    int temp = tr[k][last][pos];
                    printf("%d ", (pos + temp != n ? pos + temp : 0) + 1);
                    if (temp == 0) {
                        if ((a[pos]>>last) < a[pos+1]) k = 1;
                        else k = 2;
                    } else {
                        if ((a[pos]>>last) > a[pos+1]/2) k = 0;
                        else k = 2;
                    }
                    last = temp;
                }
            }
        }
    }
    if (!found) puts("NIE");
    return 0;
}
