/**
 * @author Miguel Mini
 * @tag math, symmetry
 * @idea
 *      - we can top and bottom face
 *
 *      - rotate only bottom face
 *
 *      - lateral face are fixed,
 *      but we can rotation with
 *      same corner configuration (count these).
 *
 */

#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < n; ++i)
#define reu(i, p, n) for (int i = p; i < n; ++i)
using namespace std;

using ll = long long;
using ii = pair<ll, int>;
ii get(int a[]) {
    ii ans = {0, 1};
    rep(i, 4) ans.first = ans.first * 1000 + a[i];
    reu(i, 1, 4) {
        ll sum = 0;
        rep(j, 4) sum = sum * 1000 + a[(i+j)&3];
        if (sum < ans.first) ans = {sum, 1};
        else if (sum == ans.first) ans.second += 1;
    }
    return ans;
}

const int maxn = 410;
int a[maxn][5];
int b[5];
int n;
map<ll, int> cnt;

int main() {
    cin >> n;
    rep(i, n) {
        rep(j, 4) {
            cin >> a[i][j];
        }
    }
    ll ans = 0;
    rep(i, n) {
        rep(j, i) {
            cnt[get(a[j]).first] -= 1;
            rep(d, 4) {
                ll s = 1;
                vector<ll> t;
                rep(e, 4) {
                    b[0] = a[i][e];
                    b[1] = a[i][(e+3)&3];
                    b[2] = a[j][3 - ((d+e+3)&3)];
                    b[3] = a[j][3 - ((d+e)&3)];
                    auto q = get(b);
                    s *= cnt[q.first] * q.second;
                    cnt[q.first] -= 1;
                    t.push_back(q.first);
                }
                for (auto e : t) cnt[e] += 1;
                ans += s;
            }
            cnt[get(a[j]).first] += 1;
        }
        cnt[get(a[i]).first] += 1;
    }
    cout << ans << endl;
    return 0;
}