/**
 * @author Miguel Mini
 * @tag linear_algebra, greedy, bitset
 * @idea
 * 
 *      - if vectors are finite 
 *      we can find a basis in 
 *      O(n * M^3 / 32) where 
 *      M = maximum power of two.
 * 
 *      - then we can count number
 *      of elements <= x in span(Basis) 
 *      with O(M * Basis) complexity 
 *      using greedy approach.
 * 
 *      - we can prove (but I could not)
 *      that we only need elements
 *      with 2^d * a_i <= 4^ceil(log(x)).
 * 
 * @complexity O(n * M^3 / 32) 
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 8005;
const int mod = 998244353;
using row = bitset<maxn>;
row basis[maxn];
int pot[maxn];
bool vis[maxn];
int sz = 0;

void insert_vector(row& mask) {
    for (int i = maxn-1; i >= 0; --i) {
        if (!mask[i]) continue;
        if (!vis[i]) {
            basis[i] = mask;
            vis[i] = 1;
            sz++;
            return;
        }
        mask ^= basis[i];
    }
}

int main() {
    pot[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        pot[i] = 2*pot[i-1]%mod;
    }
    int n;
    string s;
    cin >> n >> s;
    row x(s);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        row t(s);
        for (int j = (int)s.size(); j < maxn; ++j) {
            insert_vector(t);
            t <<= 1;
        }
    }
    long long ans = 0;
    row r;
    for (int i = maxn-1; i >= 0; --i) {
        ans += x[i] * (!r[i] || vis[i]) * pot[sz -= vis[i]];
        if (x[i] ^ r[i]) {
            if (vis[i]) r ^= basis[i];
            else break;
        }
        ans += !i;
    }
    ans %= mod;
    cout << ans << endl;
    return 0;
}