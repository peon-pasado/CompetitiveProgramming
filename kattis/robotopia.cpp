#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int a[2][2];
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				scanf ("%d", a[j]+i);

		int b[2];
		for (int i = 0; i < 2; ++i)
			scanf ("%d", b+i);


		int xx, yy;
		int nc = 0;
		for (int x = 1; x <= 10000; ++x) {		
			int y_1 = b[0] - x * a[0][0];

			if (a[0][1] == 0) continue; 			
			if (abs(y_1) % abs(a[0][1]) != 0) continue;
			y_1 = y_1 / a[0][1];
				
			long long y = y_1;
	
			if (y < 1 or x < 1) continue; 
			else {
				if (a[0][0] * x + a[0][1] * y != b[0] or a[1][0] * x + a[1][1] * y != b[1]) continue;
				else xx=x, yy=y, nc++;
			}
		}

		if (nc == 1) printf("%d %d\n", xx, yy);
		else puts("?");
	}


	return 0;
}