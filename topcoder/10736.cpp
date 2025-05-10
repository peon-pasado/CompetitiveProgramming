#include <bits/stdc++.h>
using namespace std;

class NetworkSecurity {
public:
	int secureNetwork(vector<string> A, vector<string> B) {
		int n = B.size();
		int m = B[0].size();
		long long mask[n]; 
		memset(mask, 0, sizeof mask);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				if (B[i][j] == 'Y')
					mask[i] |= 1LL << j;
		bool conn[n][n];
		for (int i = 0; i < n; ++i) 
			for (int j = 0; j < n; ++j)
				conn[i][j] = A[j][i] == 'Y';
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i) 
				for (int j = 0; j < n; ++j)		
					conn[i][j] |= conn[i][k] and conn[k][j];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (conn[i][j])
					mask[j] &= ~mask[i];
		int ans = 0;
		for (int i = 0; i < n; ++i) 
			ans += __builtin_popcountll(mask[i]);
		return ans;
	}
};