#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

const long double eps = 1e-8;

struct Rect {
	double x_1, y_1, x_2, y_2;
	Rect(double _x_1 = 0., double _y_1 = 0., double _x_2 = 0., double _y_2 = 0.) {
 		x_1 = _x_1;
		y_1 = _y_1;
		x_2 = _x_2; 
		y_2 = _y_2;
	}
};

const int MAXN = 205;
double lx[MAXN], ly[MAXN];
bool vis[MAXN][MAXN];

int main() {

	int n, nc=1;
	while (cin >> n, n) {
		vector<Rect> rectangles;
		map<double, int> X, Y;
		for (int i = 1; i <= n; ++i) {
			double x_1, y_1, x_2, y_2;
			cin >> x_1 >> y_1 >> x_2 >> y_2;
			rectangles.push_back(Rect(x_1, y_1, x_2, y_2));
		
			X[x_1]; X[x_2];
			Y[y_1]; Y[y_2];
		}
		
		int idx = 0;
		for (map<double, int>::iterator s = X.begin(); s != X.end(); ++s) {
			lx[idx] = -s->first;
			if (idx > 0) lx[idx-1] += s->first; 
			s->second = idx++;
		}
		int idy = 0;
		for (map<double, int>::iterator s = Y.begin(); s != Y.end(); ++s) {
			ly[idy] = -s->first;			
			if (idy > 0) ly[idy-1] += s->first;
			s->second = idy++;
		}
		
		lx[idx-1] = ly[idy-1] = 0.;
		
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < rectangles.size(); ++i) {
			Rect r = rectangles[i];
			int a_1 = X[r.x_1], a_2 = X[r.x_2];
			int b_1 = Y[r.y_1], b_2 = Y[r.y_2];
			
			for (int a = a_1; a < a_2; ++a) {
				for (int b = b_1; b < b_2; ++b) {
					vis[a][b] = 1;
				}
			}
		}
		
		double ans = 0;
		for (int i = 0; i < idx; ++i)
			for (int j = 0; j < idy; ++j) 
				if (vis[i][j])
					ans += lx[i] * ly[j];

		printf("Test case #%d\n", nc++);
		printf("Total explored area: %.2lf\n\n", ans);
	}

	return 0;
}