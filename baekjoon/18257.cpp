/**
 * @idea inclusion-exclusion principle, bactracking (brute_force + bitmask), binary_search
 * 
 * if we denote A_i = {n <= N | n is multiple of v_i}, then we target set
 * if the numbers that appear exactly in one of the A_i and not in the others.
 * This problem can solve with generalize inclusion exclusion principle.
 * 
 * the answer is \sum_{k = r}^{m} (-1)^{k - r} \binom{k}{r} \sum_{|X| = k} A_X
 * 
 * where A_S = \vert A_{i_1} \cap A_{i_2} \cdots \cap A_{i_k} \vert and S = {i_1, ..., i_k}
 * 
 * the core idea is use binary search over N and calculate the first time such that the answer
 * is n, and generate every intersection with backtracking.
 * 
**/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 15;
const ll lim = 1e15;
ll v[maxn];
int k;
vector<pair<ll, int>> r;
void dfs(int pos, ll M, int t) {
    if (pos == k) {
        r.emplace_back(M, t);
        return;
    }   
    dfs(pos+1, M, t);
    ll g = __gcd(M, v[pos]);
    M /= g;
    if (M <= (lim + v[pos] - 1) / v[pos]) {
        dfs(pos+1, M * v[pos], t + 1);
    }
}   

ll count_p(ll x) {
    ll ans = 0;
    for (auto [w, c] : r) {
        ll temp = 0;
        if (c > 0) temp = x / w;
        if (c & 1) ans += c * temp;
        else ans -= c * temp; 
    }
    return ans;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while (t--) {
        ll n;
        cin>>k>>n;
        for (int i=0; i<k; ++i) {
            cin>>v[i];
        }
        r.clear();
        dfs(0, 1, 0);
        ll lo = 1, hi = lim;
        while (lo < hi) {
            ll mi = (lo + hi) / 2;
            if (count_p(mi) < n) lo = mi+1;
            else hi = mi;
        }
        cout << lo << '\n';
    }
    return 0;
}