#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int op[N];
string s[N];
int x, y, n;

bool sim(int pos, int px, int py, int dx, int dy) {
	if (pos == n) return px == x and py == y;
	if (op[pos] == 1) 
		return sim(pos+1, px+dx, py+dy, dx, dy);
	if (op[pos] == 2) 
		return sim(pos+1, px, py, dy, -dx);
	if (op[pos] == 3) 
		return sim(pos+1, px, py, -dy, dx);
}

int main() {

	cin >> x >> y >> n;
	for (int i = 0; i < n; ++i) {
		cin >> s[i];

		if(s[i][0] == 'F') op[i] = 1;
		if(s[i][0] == 'R') op[i] = 2;
		if(s[i][0] == 'L') op[i] = 3;
	}
	
	int pos, ne;
	for (int i = 0; i < n; ++i) {

		int t = op[i];
		bool ok = 1;
		for (int j = 1; j <= 3; ++j) {
			op[i] = j;
		
			if (sim(0, 0, 0, 0, 1)) {
				pos = i;
				ne = op[i];
				ok = 0;
				break;
			}
		}
		if (not ok) break;

		op[i] = t;
	}

	printf("%d ", pos+1);

	if (ne == 1) puts("Forward");
	if (ne == 2) puts("Right");
	if (ne == 3) puts("Left");


	return 0;
}