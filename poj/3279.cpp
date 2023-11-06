#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int N = 20;
vector<int> solve, v;
int lmin, mini = INT_MAX;
int n, m;
int T[N];

int _builtin_popcount(int mask){
	int ans = 0;
	for(int i = 0; i < m; ++i)
		if(mask&(1<<i)) ans += 1;
	return ans;
}


void dfs(int pos, int mask_front, int mask_back){

	if(pos == n){
		if(mask_back == 0 and lmin < mini){
 			mini = lmin;
			solve = v;
		}
		return;
	}

	int new_mask_back = T[pos] xor mask_front;		
	int new_mask_front = mask_back;
	for(int j = 0; j < m; ++j)
		if(mask_back&(1<<j)){
			new_mask_back ^= (1<<j);
			if(j != 0) new_mask_back ^= (1<<j-1);		
			if(j != m-1) new_mask_back ^= (1<<j+1);
		}

	v.push_back(mask_back);
	lmin += _builtin_popcount(mask_back);
	dfs(pos+1, new_mask_front, new_mask_back);
	v.pop_back();	
	lmin -= _builtin_popcount(mask_back);
}

int main(){

	scanf("%d %d", &n, &m);

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j){
			int x;
			scanf("%d", &x);
			T[i] |= x*(1<<j);
		}
		
	for(int mask = 0; mask < (1<<m); ++mask){
		
		int mask_back = T[0];
		int mask_front = mask;
	
		for(int i = 0; i < m; ++i)
			if(mask&(1<<i)){	
				mask_back ^= (1<<i);
				if(i != 0) mask_back ^= (1<<i-1);		
				if(i != m-1) mask_back ^= (1<<i+1);
			}
	
		v.push_back(mask);
		lmin += _builtin_popcount(mask);
		dfs(1, mask_front, mask_back);
		lmin -= _builtin_popcount(mask);
		v.pop_back();
	}

	if(solve.empty()) puts("IMPOSSIBLE");
	else{
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				printf("%d%c", (solve[i]&(1<<j)) ? 1 : 0, (j+1==m) ? '\n' : ' ');
	}

	return 0;
}