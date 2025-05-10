#include <bits/stdc++.h>
using namespace std;

const int N = 100002;
int n, m;
int a[N];
int sq;
int block[N][2];

void build(){

	sq = sqrt(n) + 2;
	
	for(int i = n; i >= 1; --i){
		int pos = i + a[i];

		int nbi = i / sq;
		int nbpos = pos / sq;

		if(pos > n){
			block[i][0] = i;
			block[i][1] = 0;
		}		
		else{
			if(nbpos == nbi){ 
				block[i][0] = block[pos][0];
				block[i][1] = block[pos][1] + 1;
			}
			else{
				block[i][0] = pos;
				block[i][1] = 1;
			}
		}
	}
}

pair<int, int> query(int pos){

	int jumps = 1;

	while(block[pos][0] != pos){
		jumps += block[pos][1];
		pos = block[pos][0];
	}

	return make_pair(pos, jumps);
}

void update(int idx, int x){

	int nbx = idx / sq;

	a[idx] = x;

	for(int i = idx; i >= nbx*sq; --i){
		int pos = i + a[i];

		int nbpos = pos / sq;

		if(pos > n){
			block[i][0] = i;
			block[i][1] = 0;
		}		
		else{
			if(nbpos == nbx){ 
				block[i][0] = block[pos][0];
				block[i][1] = block[pos][1] + 1;
			}
			else{
				block[i][0] = pos;
				block[i][1] = 1;
			}
		}
	}
}


int main(){

	scanf("%d %d", &n, &m);

	for(int i = 1; i <= n; ++i)
		scanf("%d", a+i);

	build();

	while(m--){

		int type;
		scanf("%d", &type);

		if(not type){
			int pos, x;
			scanf("%d %d", &pos, &x);
		
			update(pos, x);
		} 	
		else{
			int pos;
			scanf("%d", &pos);

			pair<int, int> q = query(pos);		
	
			printf("%d %d\n", q.first, q.second);
		}
	}

	return 0;
}