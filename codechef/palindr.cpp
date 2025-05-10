#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 10;
struct node{
    int value, prior, l, r, cnt;
	bool reverse;
	int mask;
	int v[26];
	
	node() {}
	node(int _value, int _prior): 
	value(_value), prior(_prior),
	l(0), r(0), cnt(1), reverse(0), mask(0){
		memset(v, 0, sizeof v);
		v[value-'a'] = 1;
		mask |= (1<<value-'a');
	}

} treap[maxN];      
int f[maxN], r[maxN], inv[maxN];

namespace NT{
	const int mod = 1e9 + 7;
	typedef unsigned int ui;
	ui state;

	void init(){state = time(0);} 

	int rand(ui length){
	    state = 1234567891u * state + 999119999u; 
	    return (1ull * state * length) >> 32;
	}

	int add(int a, int b){
		return (a+b)%mod;
	}

	int mul(long long a, long long b){
		return a*b%mod;
	}
}

namespace NODE{
    int T = 1;
    int create(){
		return T++;
    }

    int init_node(int value){
		int t = create();
		treap[t] = node(value, NT::rand(1e8));

		return t;
    }
}

int cnt(int t){
    return t ? treap[t].cnt : 0;
}

int mask(int t){
	return t ? treap[t].mask : 0;
}

void upd_cnt(int t){
    if(t){
		treap[t].mask = mask(treap[t].l) ^ mask(treap[t].r) ^ (1 << treap[t].value - 'a');
		for(int i = 0; i < 26; ++i)
			treap[t].v[i] = treap[treap[t].l].v[i] + treap[treap[t].r].v[i];
		treap[t].v[treap[t].value - 'a'] += 1;		

		treap[t].cnt = 1 + cnt(treap[t].l) + cnt(treap[t].r);
	}
}


void push(int t){
	if(not t) return;
	if(treap[t].reverse){
		swap(treap[t].l, treap[t].r);
		treap[treap[t].l].reverse ^= 1;
		treap[treap[t].r].reverse ^= 1;
		treap[t].reverse = 0;
	}
}


void split(int t, int key, int& l, int& r, int add = 0){
    if(not t) return void(l = r = 0);

	push(t);
	
    int cur_key = add + cnt(treap[t].l);    
	if(key <= cur_key) 
		split(treap[t].l, key, l, treap[t].l, add), r = t;
    else
        split(treap[t].r, key, treap[t].r, r, add + 1 + cnt(treap[t].l)), l = t;

    upd_cnt(t);
}

void merge(int& t, int l, int r){
	push(l);
	push(r);

    if(not l or not r) t = max(l, r);
    else if(treap[l].prior > treap[r].prior)
		merge(treap[l].r, treap[l].r, r), t = l;
    else
        merge(treap[r].l, l, treap[r].l), t = r;
    
	upd_cnt(t);
}

void insert(int& t, int pos, int val){
    int item = NODE::init_node(val);
    int t1 = 0, t2 = 0;
    
	split(t, pos, t1, t2);    
    merge(t1, t1, item);
    merge(t, t1, t2);
}

void erase(int& t, int key, int add = 0){
    if(not t) return; 

	push(t);
    int cur_key = cnt(treap[t].l) + add;
    if(cur_key == key)
		merge(t, treap[t].l, treap[t].r);
    else if(key < cur_key)
		erase(treap[t].l, key, add);
    else
		erase(treap[t].r, key, add + 1 + cnt(treap[t].l));
    
	upd_cnt(t);
}

void update(int& t, int a, int b){
	int t1 = 0, t2 = 0, t3 = 0;
	split(t, a, t1, t2);
	split(t2, b-a+1, t2, t3);
	treap[t2].reverse ^= 1;
	merge(t, t1, t2);
	merge(t, t, t3);
}

int query(int& t, int a, int b){
	int t1 = 0, t2 = 0, t3 = 0;
	split(t, a, t1, t2);	
	split(t2, b-a+1, t2, t3);

	int ans = f[cnt(t2)/2];

	if(__builtin_popcount(mask(t2)) <= 1)
		for(int i = 0; i < 26; ++i){
			ans = NT::mul(ans, inv[treap[t2].v[i]/2]);
		}
	else
		ans = 0;

	merge(t, t1, t2);
	merge(t, t, t3);

	return ans;
}



char s[maxN];

int main(){

	f[0] = 1;
	for(int i = 1; i < maxN; ++i)
		f[i] = NT::mul(f[i-1], i);

	r[1] = 1;
	for(int i = 2; i < maxN; ++i)
		r[i] = NT::mod - NT::mul(NT::mod/i, r[NT::mod%i]);

	inv[0] = 1;
	for(int i = 1; i < maxN; ++i)
		inv[i] = NT::mul(inv[i-1], r[i]);

    NT::init();
    int root = 0;

	int N, Q;

	scanf("%d %d", &N, &Q);
	scanf("%s", s);

	for(int i = 0; i < N; ++i)
		insert(root, i, s[i]);

	while(Q--){	
		int type, l, r;
		scanf("%d %d %d", &type, &l, &r);		

		if(type == 1) update(root, l-1, r-1);
		else printf("%d\n", query(root, l-1, r-1));
	}
	

    return 0;
}