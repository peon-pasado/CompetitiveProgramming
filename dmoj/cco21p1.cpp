#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;

const int maxn = 1e5 + 10;
int query_index[maxn * 10];
int p[maxn], sz[maxn], bit[maxn];
int frecuency[maxn];
int n, k, q;
vector<pair<int, ll>> query_list[maxn];

int main() {
    scanf("%d%d%d", &n, &k, &q);
    vector<int> a(n);
    forn(i, n) scanf("%d", &a[i]);
    forn(i, n) sz[a[i]]++;
    forn(i, q) {
        scanf("%d", query_index+i);
        query_index[i] -= 1;
    }
    iota(p, p+k, 1);
    auto save_query = [&](int x, int y) {
        if (sz[x] > sz[y]) swap(x, y);
        query_list[x].emplace_back(y, 0ll);
    };
    forn(i, q) {
        int p_idx = query_index[i];
        save_query(p[p_idx], p[p_idx+1]);
        swap(p[p_idx], p[p_idx+1]);
    }
    auto compress_list = [](auto& arr) {
        sort(all(arr));
        arr.erase(unique(all(arr)), arr.end());
    };
    forn(i, k) compress_list(query_list[i+1]);
    forn(i, n) {
        for (auto& [other, inv] : query_list[a[i]]) {
            inv += frecuency[other];
        }
        frecuency[a[i]]++;
    }
    auto update_bit = [&](int pos, int delta) {
        while (pos <= k) {
            bit[pos] += delta;
            pos += pos&-pos;
        }
    };
    auto query_bit = [&](int pos) {
        int sum = 0;
        while (pos > 0) {
            sum += bit[pos];
            pos -= pos&-pos;
        }
        return sum;
    };
    auto calc_inv = [&](const vector<int>& arr) {
        ll inv = 0;
        forn(i, (int)arr.size()) {
            update_bit(arr[i], 1);
            inv += i - query_bit(arr[i]) + 1;
        }
        return inv;
    };
    ll invertions = calc_inv(a);
    iota(p, p+k, 1);
    function<ll(int, int)> inv = [&](int x, int y)->ll {
        int lo = 0, hi = (int)query_list[x].size() - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1)/2;
            if (query_list[x][mid].first <= y) lo = mid;
            else hi = mid-1;
        }        
        auto& qlist = query_list[x];
        if (!qlist.empty() && qlist[lo].first == y) {
            return qlist[lo].second;
        }
        return (ll)sz[x]*sz[y] - inv(y, x);
    };
    auto calc_diff = [&](int x, int y) {
        return (ll)sz[x]*sz[y] - 2*inv(x, y);
    };
    forn(i, q) {
        int p_idx = query_index[i];
        invertions += calc_diff(p[p_idx], p[p_idx+1]);
        printf("%lld\n", invertions);
        swap(p[p_idx], p[p_idx+1]);
    }
    return 0;
}