#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> sol;
void backtrack(int row, int r[8], set<int>& col, set<int>& d1, set<int>& d2) {
	if (row == 8) {
		vector<int> d(8);
		for (int i = 0; i < 8; ++i) d[i] = r[i];
		sol.push_back(d);
		//cout << "***" << endl;
		//for (int i = 0; i < 8; ++i) {
		//	for (int j = 0; j < 8; ++j) {
		//		if (r[i] == j) {
		//			cout << "Q";
		//		} else {
		//			cout << "_";
		//		}
		//	}
		//	cout << endl;
		//}
		return;
	}
	for (int c = 0; c < 8; ++c) {
		if (col.count(c)) continue;
		if (d1.count(row + c)) continue;
		if (d2.count(row - c)) continue;
		col.insert(c);
		d1.insert(row + c);
		d2.insert(row - c);
		r[row] = c;
		backtrack(row+1, r, col, d1, d2);
		col.erase(c);
		d1.erase(row + c);
		d2.erase(row - c);
		r[row] = -1;
	}
}


int main() {
	int r[8]; 
	set<int> c, d1, d2;
	backtrack(0, r, c, d1, d2);
	int m;
	cin >> m;
	while (m--) {
		int x, y;
		cin >> x >> y;
		x -= 1; y -= 1;
		cout << "SOLN       COLUMN" << endl;
		cout << " #      1 2 3 4 5 6 7 8" << endl;
		cout << endl;
		int t = 1;
		for (auto v : sol) {
			if (v[y] == x) {
				printf("%2d      ", t);
				t += 1;
				for (int i = 0; i < 8; ++i) {
					cout << v[i] + 1 << " \n"[i==7];
				}
			}
		}
		if (m) cout << endl;
	}
	return 0;
}