#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
const ll mod = 1e18 + 3;
ll B = 1e5 + rand() % 100000;

vector<ll> pot = {1};

ll add(ll a, ll b) {
    return a+b<mod?a+b:a+b-mod;
}

ll mul(ull a, ull b, ull M=mod) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ull(ret + M * (ret < 0) - M * (ret >= (ll)M));
}

ll get_pot(int i) {
    while (pot.size() <= i) {
        pot.push_back(mul(pot.back(), B));
    }
    return pot[i];
}

struct MyHash {
    ll v;

    MyHash(ll x) {v = x;}

    MyHash(char c) {v = c;}

    MyHash operator+(MyHash x) {
        return MyHash(add(v, x.v));
    }

    MyHash operator-(MyHash x) {
        return MyHash(add(v, mod - x.v));
    }

    bool operator==(MyHash x) {
        return v == x.v;
    }

    MyHash shift(int d) {
        return mul(v, get_pot(d));
    }

};

template<class MyHash>
struct StringHash {
    vector<MyHash> hash;

    size_t size() {
        return hash.size();
    }

    MyHash get_hash(int l, int r) {
        if (l == 0) return hash[r];
        return hash[r] - hash[l-1].shift(r-l+1);
    }

    void append(char c) {
        if (hash.empty()) hash.push_back(MyHash(c));
        else hash.push_back(hash.back().shift(1) + MyHash(c));
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    StringHash<MyHash> rh;
    string ret;
    while (n--) {
        StringHash<MyHash> sh;
        string s;
        cin >> s;
        for (auto c : s) sh.append(c);
        int n = ret.size();
        int m = s.size();
        int j = -1;
        for (int i = 0; i < m && i < n; ++i) {
            if (sh.get_hash(0, i) == rh.get_hash(n-1-i, n-1)) {
                j = i;
            }
        }
        for (int i = j+1; i < m; ++i) {
            rh.append(s[i]);
            ret += s[i];
        }
    }  
    cout << ret << '\n';
    return 0;
}
