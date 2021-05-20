/**
 * @author Miguel Mini
 * @tag dp, amortized
 * @idea
 *      - we can see that
 *      number of distinct states
 *      for fixed position is small.
 * 
 *      - use dp over configurations.
 * 
 * @complexity O(n k) where k is maximum number 
 * of configurations for fixed position.
 */ 

#include <bits/stdc++.h>
using namespace std;

int mapper[300];
const int maxn = 1e4 + 10;
string s;
int n;
map<vector<int>, int> mp; 

int get(vector<int>& arr) {
	int mn = *min_element(arr.begin(), arr.end());
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		if (arr[i] == mn) {
			ans |= 1<<i;
		}
	}
	return ans;
}

int dp(int pos, vector<int>& arr) {
	if (pos == n) return get(arr);
	if (mp.count(arr)) return mp[arr];
	int ans = 0;
	if (s[pos] != '?') {
		arr[mapper[s[pos]]] += 1;
		ans = dp(pos+1, arr);
		arr[mapper[s[pos]]] -= 1;
	} else {
		int t = get(arr);
		for (int i = 0; i < 4; ++i) {
			if (t & (1<<i)) {
				arr[i] += 1;
				ans |= dp(pos+1, arr);
				arr[i] -= 1;
			}
		}
	}
	return mp[arr] = ans;
}


int main() {
	mapper['G'] = 0;
	mapper['H'] = 1;
	mapper['R'] = 2;
	mapper['S'] = 3;
	string id[4];
	id[0] = "Gryffindor";
	id[1] = "Hufflepuff";
	id[2] = "Ravenclaw";
	id[3] = "Slytherin";
	cin >> n >> s;
	vector<int> v(4);
	int ans = dp(0, v);
	for (int i = 0; i < 4; ++i) {
		if (ans & (1<<i)) {
			cout << id[i] << endl;
		}
	}
	return 0;
}