#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e4;
const int maxQ = 2e5;
const int OFFSET = 2;
int st[4*maxN + 30*maxQ + OFFSET];
int version[maxN + OFFSET];
int Left[4*maxN + 30*maxQ + OFFSET], Right[4*maxN + 30*maxQ + OFFSET];
int T, n, m;
int a[maxN  + OFFSET];

int create(){
	return T++;
}

void build0(int nx, int l, int r){
	if(l == r) return;
	int mid = (l+r)>>1;
	Left[nx] = create(); build0(Left[nx], l, mid);
	Right[nx] = create(); build0(Right[nx], mid+1, r);
}

void copy(int last, int now){
	Left[now] = Left[last];
	Right[now] = Right[last];
}

int merge(int L, int R){
	return L+R;
}

void update(int p1, int p2, int last_nx, int nx, int l, int r){
	if(r < p1 or l > p2) return;
	if(p1 < l and r < p2) return;
	if(l == r){
		st[nx] = 1 - st[last_nx];
		return;
	}
	copy(last_nx, nx);
	int mid = (l+r)>>1;
	if((l <= p1 and p1 <= mid) or (l <= p2 and p2 <= mid)){
		Left[nx] = create();
		update(p1, p2, Left[last_nx], Left[nx], l, mid);
	}
	if((r >= p2 and p2 > mid) or (r >= p1 and p1 > mid)){
		Right[nx] = create();
		update(p1, p2, Right[last_nx], Right[nx], mid+1, r);
	}

	st[nx] = merge(st[Left[nx]], st[Right[nx]]);
}

int query(int a, int b, int nx, int l, int r){
	if(b < l or r < a) return 0;
	if(a <= l and r <= b) return st[nx];
	int mid = (l+r)>>1;	
	return merge(query(a, b, Left[nx], l, mid), query(a, b, Right[nx], mid+1, r));
}

int main(){

	scanf("%d", &n);

	for(int i = 0; i < n; ++i)
		scanf("%d", a+i);	

	version[0] = create();
	build0(version[0], 0, n-1);

	map<int, int> Last; 
	for(int i = 0; i < n; ++i){
		version[i+1] = create();
		
		if(not Last.count(a[i]))
			update(i, i, version[i], version[i+1], 0, n-1);
		else
			update(Last[a[i]], i, version[i], version[i+1], 0, n-1);
		
		Last[a[i]] = i;
	}	

	scanf("%d", &m);	

	for(int i = 0; i < m; ++i){
		int a, b;	
		scanf("%d %d", &a, &b);
		printf("%d\n", query(a-1, b-1, version[b], 0, n-1));
	}

	return 0;
}	