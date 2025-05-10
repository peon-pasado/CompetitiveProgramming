#include "bits/stdc++.h"
using namespace std;

//query = O(6^3)
const int maxN = 6, OFF_SET = 1;
short m[maxN + OFF_SET];
bool Sum[maxN * maxN + OFF_SET];
int nc = 1;

int main() {

	while (1) {

		bool is_query = 0;
		for (int i = 0; i < 6; ++i) {
			cin >> m[i];
			is_query |= m[i];
		}

		if (not is_query) break;
		
		int sum = 0;
		for (int i = 0; i < 6; ++i){
			if (m[i] > 5)
				m[i] = 6 - (m[i]&1);		
			sum += m[i]*(i + 1);
		}

		printf("Collection #%d:\n", nc++);
		bool div = 1;
		if(sum&1) div = 0;
		else {
			memset(Sum, 0, sizeof Sum);
			Sum[0] = 1;
			for (int i = 1; i <= 6; ++i)
				if (m[i-1]){
					for (int j = 0; j < i; ++j) {

						int end = i * ((sum/2 - j)/i) + j;
						int nSet = 0;
						int last = end - i; 
						for (int k = 0; k < m[i-1]; ++k){
							if (last < 0) break;			
							nSet += Sum[last];
							last -= i; 
						}
						
						for (int k = end; k >= i; k -= i) {
							if (not Sum[k] and nSet > 0)
								Sum[k] = 1;							
							
							nSet -= Sum[k-i];
							if (last >= 0){
								nSet += Sum[last];
								last -= i;
							}
						}
					}
				}
			div = Sum[sum/2];	
		}

		puts(div ? "Can be divided." : "Can't be divided.");
                 puts("");
	}	

	return 0;
}

