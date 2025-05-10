#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
	int x1, y1, x2, y2;
	
	Rectangle intercept(Rectangle p) {
		return {max(x1, p.x1), max(y1, p.y1), min(x2, p.x2), min(y2, p.y2)};
	}
	
	friend istream& operator>>(istream& is, Rectangle& r) {
		return is >> r.x1 >> r.y1 >> r.x2 >> r.y2;
	}
	
	friend ostream& operator<<(ostream& os, Rectangle r) {
      return os << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2;
	}
};

int main() {
	int t;
	cin >> t;
	while (t--) {
		Rectangle p, q;
		cin >> p >> q;
		Rectangle in = p.intercept(q);
		if (in.x1 >= in.x2 || in.y1 >= in.y2) cout << "No Overlap\n";
		else cout << in << '\n';
		if (t) cout << '\n';
	}
	return 0;
}