#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

ll f(ll x, ll y, vector<ll>& divisors) {
	if (y == 0) return 0;
	ll g = gcd(x, y);
	ll cost = y / g, to = 0;
	for (int i = 0; i < divisors.size(); ++i) {
		if (divisors[i] == g) continue;
		if (divisors[i] % g == 0) {
			ll temp_to = y / divisors[i] * divisors[i];
			ll temp_cost = (y - temp_to) / g;
			if (temp_cost < cost) {
				to = temp_to;
				cost = temp_cost;
			}
		}
	}
	return cost + f(x, to, divisors);
}

int main() {
	ll x, y;
	cin >> x >> y;
	vector<ll> divisors;
	for (ll i = 1; i * i <= x; ++i) {
		if (x % i == 0) {
			divisors.emplace_back(i);
			if (i * i != x) {
				divisors.emplace_back(x / i);
			}
		}
	}
	cout << f(x, y, divisors) << endl;
	return 0;
}