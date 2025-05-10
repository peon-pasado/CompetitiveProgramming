#include <bits/stdc++.h>
using namespace std;

const int N = 100002;
int sq, n, q;
int a[N];
vector<int> block[2000];


void build(){
	sq = sqrt(n / (log2(n) + 1)) + 2;
	int nb = n / sq + 1;
	for(int i = 1; i <= n; ++i)	
		block[i/sq].push_back(a[i]);

	for(int i = 0; i < nb; ++i)
		sort(block[i].begin(), block[i].end());
}

int query(int l, int r, int x){

	int nbl = l / sq;
	int nbr = r / sq;
	int ans = 0;

	if(nbl == nbr)
		for(int i = l; i <= r; ++i)	
			ans += (a[i] <= x);
	else{
		for(int i = l; i < (nbl + 1) * sq; ++i)
			ans += (a[i] <= x);

		for(int i = nbl + 1; i < nbr; ++i)
			ans += upper_bound(block[i].begin(), block[i].end(), x) - block[i].begin();
 
		for(int i = nbr*sq; i <= r; ++i)
			ans += (a[i] <= x);
	}

	return ans;
}


int main(){

	scanf("%d %d", &n, &q);

	for(int i = 1; i <= n; ++i)
		scanf("%d", a+i);
	
	build();

	while(q--){

		getchar();		

		char C;
		C = getchar();
		
		if(C == 'M'){

			int pos, x;	
			scanf("%d %d", &pos, &x);			

			int nbpos = pos / sq;
			a[pos] = x;

			block[nbpos].clear();

			for(int i = nbpos * sq; i < min((nbpos + 1)*sq, n+1); ++i)
				block[nbpos].push_back(a[i]);

			sort(block[nbpos].begin(), block[nbpos].end());
		}
		else{		
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);			

			printf("%d\n", query(l, r, x));
		}
	}



	return 0;
}