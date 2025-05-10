#include <bits/stdc++.h>
using namespace std;

namespace NT{
	
	typedef unsigned int ui;
	ui state;

	void init(){state = time(0);} 

	ui rand(ui length){
		state = 1234567891u * state + 999119999u; 
		return (1ull * state * length) >> 32;
	}
}


namespace TREAP{

	struct item{
		int prior, key, cnt;
		item *l, *r;
		item(int _prior = 0, int _key = 0) : 
		prior(_prior), key(_key), cnt(0),		
		l(NULL), r(NULL) {}
	};
	
	typedef item* pitem;

	int cnt(pitem t){
		return t ? t->cnt : 0;
	}

	void upd_cnt(pitem t){
		if(t)
			t->cnt = 1 + cnt(t->l) + cnt(t->r);
	}

	void split(pitem t, int key, pitem& l, pitem& r){
		if(not t) l = r = NULL;
		else if(key < t->key)
			split(t->l, key, l, t->l), r = t;
		else
			split(t->r, key, t->r, r), l = t;
		upd_cnt(t);
	}

	void insert(pitem& t, pitem it){
		if(not t) t = it;
		else if(it->prior > t->prior)
			split(t, it->key, it->l, it->r), t = it;
		else
			insert(it->key < t->key ? t->l : t->r, it);
		upd_cnt(t);
	}

	
	void merge(pitem & t, pitem l, pitem r){
 		if(not l or not r) t = l ? l : r;
    	else if(l->prior > r->prior)
        	merge(l->r, l->r, r),  t = l;
    	else
        	merge(r->l, l, r->l),  t = r;
		upd_cnt(t);
	}

	void erase(pitem & t, int key){
    	if (t->key == key)
        	merge (t, t->l, t->r);
    	else
        	erase (key < t->key ? t->l : t->r, key);
		upd_cnt(t);
	}

	pitem unite (pitem l, pitem r) {
    	if (!l || !r)  return l ? l : r;
    	if (l->prior < r->prior)  swap (l, r);
   		pitem lt, rt;
   		split (r, l->key, lt, rt);
    	l->l = unite(l->l, lt);
    	l->r = unite(l->r, rt);
    	return l;
	}	

	bool find(pitem t, int x){
		if(not t) return 0;
		if(t->key == x) return 1;
		if(t->key < x) return find(t->r, x);
		return find(t->l, x);
	}

	int k_th(pitem t, int k){
		if(not t) return INT_MIN;
		if(cnt(t->l) + 1 == k) return t->key;  
		if(cnt(t->l) >= k) return k_th(t->l, k);
		return k_th(t->r, k - cnt(t->l) - 1);
	}

	int count(pitem t, int x){
		if(not t) return 0;
		if(t->key < x) return cnt(t->l) + 1 + count(t->r, x);		
		return count(t->l, x);
	}
}


int main(){

	TREAP::pitem root = NULL;
	NT::init();

	int N, K;
	scanf("%d %d", &N, &K);
	
	for(int i = 1; i <= N; ++i){
		TREAP::pitem q = new TREAP::item(NT::rand(1e8), i);
		TREAP::insert(root, q);
	}

	int pos = K;
	for(int i = 1; i <= N; ++i){
		int ans;
		printf("%d ", ans = TREAP::k_th(root, pos));

		pos += K-1;
		if(N != i) pos %= (N - i);
		if(pos == 0) pos = N - i;

		TREAP::erase(root, ans);
	} puts("");


	return 0;
}