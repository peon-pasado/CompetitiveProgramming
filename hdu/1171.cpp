#include <bits/stdc++.h>
using namespace std;

const int maxN = 50*100*50 + 2;
bool Sum[maxN];
int v[55], m[55];
int n;

int main () {

	while (cin >> n, n > 0) {

		int sum = 0;
		for (int i = 0; i < n; ++i) {
			cin >> v[i] >> m[i];
			sum += v[i]*m[i];
		}			

		for (int i = 0; i <= sum/2; ++i)
			Sum[i] = 0;		

		Sum[0] = 1;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < v[i]; ++j) {

					int end = v[i] * ((sum/2 - j) / v[i]) + j;
					int nSet = 0;
					int last = end - v[i];
 
					for (int k = 0; k < m[i]; ++k){
						if (last < 0) break;			
						nSet += Sum[last];
						last -= v[i]; 
					}
						
					for (int k = end; k >= v[i]; k -= v[i]) {
						if (not Sum[k] and nSet > 0)
								Sum[k] = 1;							
							
						nSet -= Sum[k-v[i]];
						if (last >= 0){
							nSet += Sum[last];
							last -= v[i];
						}
					}
				}

		int b = 0;
		for (int i = sum/2; i >= 0; --i)
			if (Sum[i]){
				b = i;
				break;
			}

		printf("%d %d\n", sum - b, b);
	}	



	return 0;
}