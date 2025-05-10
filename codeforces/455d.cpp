#include <bits/stdc++.h>
using namespace std;

const int maxN = 4e5 + 5;
struct node_treap_1{
	int prior;
	int l, r, p, value, fake;
	int cnt;
} T[maxN];
int p[maxN];
int elements = 0;
random_device rd;
mt19937	gen(rd());
uniform_int_distribution<> dis(1, 1e9);

int cnt(int t){
	return t ? T[t].cnt : 0;
}

void upd(int t){
	if(t){
		T[t].cnt = cnt(T[t].l) + 1 + cnt(T[t].r);
		if(T[t].r) p[T[t].r] = t;
		if(T[t].l) p[T[t].l] = t; 	
	}
}

int order(int t){
	int sum = 0;	
	bool is_right = 1;
	while(t){
		if(is_right)
			sum += cnt(T[t].l) + 1;

		upd(p[t]);
		is_right = T[p[t]].r == t;
		t = p[t];
	}
	return sum-1;
}


void split(int t, int& l, int& r, int key, bool type, int add = 0){
	int cur_key = type ? cnt(T[t].l) + add : order(T[t].fake);
	if(t == 0) l = r = 0;
	else if(cur_key < key) 
		split(T[t].r, T[t].r, r, key, type, type ? cur_key + 1 : 0), l = t;
	else
		split(T[t].l, l, T[t].l, key, type, add), r = t;
	upd(t);
}

void merge(int& t, int l, int r){
	if(l == 0 or r == 0) t = l^r;
	else if(T[l].prior > T[r].prior)
		merge(T[l].r, T[l].r, r), t = l;
	else
		merge(T[r].l, l, T[r].l), t = r;
	upd(t);
}

int kth(int& t, int k){
	if(cnt(T[t].l) + 1 == k) return t;
	if(cnt(T[t].l) >= k) return kth(T[t].l, k);
	return kth(T[t].r, k - cnt(T[t].l) - 1);
}

void add(int& t1, int& t2, int pos, int val){
	T[++elements] = {dis(gen), 0, 0, 0, val, elements+1,  1};

	int r;
	split(t1, t1, r, pos, 1);
	merge(t1, t1, elements);	
	merge(t1, t1, r);
	T[++elements] = {dis(gen), 0, 0, 0, val, elements-1, 1};
	
	split(t2, t2, r, pos, 0);
	merge(t2, t2, elements);
	merge(t2, t2, r);
}

void rotate(int& t1, int& t2, int lo, int hi, int val){
	int mid, r;
	split(t2, t2, r, hi, 0);
	split(r, mid, r, hi+1, 0);
	merge(t2, t2, r);
	
	split(t1, t1, r, hi, 1);
	split(r, mid, r, 1, 1);
	merge(t1, t1, r);

	add(t1, t2, lo, val);
}

int Count(int& t, int lo, int hi){
	int mid, r;
	split(t, t, r, lo, 0);
	split(r, mid, r, hi+1, 0);
	int ans = cnt(mid);
	merge(t, t, mid);
	merge(t, t, r);
	return ans;
}


int main(){

	int n, q;
	scanf("%d", &n);
	map<int, int> root;
	for(int i = 0; i < n; ++i){
		int k;
		scanf("%d", &k);
		add(root[0], root[k], i, k);
	}

	scanf("%d", &q);
	int ans = 0;
	while(q--){
		
		int type, l, r, k;
		scanf("%d %d %d", &type, &l, &r);
		l = (l + ans - 1)%n;
		r = (r + ans - 1)%n;
		if(l > r) swap(l, r);
	
		if(type == 1){
			if(l == r) continue;
			int node = kth(root[0], r+1);	
			rotate(root[0], root[T[node].value], l, r, T[node].value);
		}
		else{
			scanf("%d", &k); k = (k + ans - 1)%n + 1;
			printf("%d\n", ans = Count(root[k], l, r));
		}
	}
	

	return 0;
}