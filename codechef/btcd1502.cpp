#include <bits/stdc++.h>
using namespace std;

const int N = 152;
long long pb[N], pa[N], _pa[N];
int n, m, t;
string a, b;

bool same(){
	for(int i = 0; i < n; ++i)
		if(pb[i] != _pa[i]) return 0;
	return 1;
}

int sz(long long mask){
	int ans = 0;
	for(int i = 0; i < m; ++i)
		if(mask&(1LL<<i))
			ans += 1;
	return ans;
}

int main(){

	cin >> t;
	while(t--){
		cin >> n >> m;
	
		memset(pa, 0, sizeof pa);
		for(int i = 0; i < n; ++i){
			cin >> a;
			for(int j = 0; j < m; ++j)
				if(a[j] == '1') pa[i] |= (1LL<<j); 	
		}
		
		memset(pb, 0, sizeof pb);
		for(int i = 0; i < n; ++i){
			cin >> b;
			for(int j = 0; j < m; ++j)
				if(b[j] == '1') pb[i] |= (1LL<<j); 	
		}


		sort(pb, pb+n);

		int mini = 60;
		for(int i = 0; i < n; ++i){
			long long mask = pa[0] xor pb[i];		
				
			for(int j = 0; j < n; ++j)
				_pa[j] = pa[j] xor mask;

			sort(_pa, _pa+n);
			
			if(same())
				mini = min(mini, sz(mask));	
		}

		printf("%d\n", mini == 60 ? -1 : mini);
	}

	return 0;
}