/**
 * @author Miguel Mini
 * @tag dp, math, monotone_stack
 * @idea
 *      - We can solve this problem row a row.
 *
 *      - In a row, we consider an array of 
 *      height of white cells.
 *
 *      - If a position is lower right corner,
 *      interesting positions are bounded by 
 *      elements in a monotone stack view
 *
 *      - if columns are a[1], a[2], a[3], ..., a[k]
 *      the answer for a position is 
 *        binom(a[1], 2) * binom(k, 2) + (binom(a[2], 2) - binom(a[1], 2)) * binom(k-1, 2) + -  
 *        ... (binom(a[i], 2) - binom(a[i-1], 2)) * binom(k - i + 1, 2)
 *
 *      - we can modify these values from column 
 *      to column, at the same time we update the 
 *      monotone stack.
 *
 * @complexity O(n^2)
**/


#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 2010;
char mat[maxn][maxn];
int n, m;
int arr[maxn], ta[maxn];
using ll = long long;
ll ans[maxn];
 
ll calc(ll x)  {
    return x * (x + 1) / 2;
}
 
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> mat[i];
    }
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            arr[j + 1] = mat[i][j] != '#' ? arr[j + 1] + 1 : 0;
            ta[j + 1] = arr[j + 1];
        }
        stack<int> s;
        s.push(0); 
        ll sum = 0;
        for (int j = 1; j <= m; ++j) {
            ll delta = 0;
            int temp = j;
            while (!s.empty() && ta[s.top()] > ta[j]) {
                temp = s.top(); s.pop();
                delta += (calc(ta[temp]) - calc(ta[s.top()])) * calc(j - temp);
                sum -= (calc(ta[temp]) - calc(ta[s.top()])) * (j - temp);
            }
            delta -= (calc(ta[j]) - calc(ta[s.top()])) * calc(j - temp);
            sum += (calc(ta[j]) - calc(ta[s.top()])) * (j - temp);
            sum += calc(ta[j]);
            ans[j] = ans[j-1] + sum - delta;
            ta[temp] = ta[j];
            if (ta[j] > ta[s.top()]) {
                s.push(temp);
            }
        }
        for (int j = 1; j <= m; ++j) {
            res += ans[j];
        }
    }
    cout << res << endl;
    return 0;
}
