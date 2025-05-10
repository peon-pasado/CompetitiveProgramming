#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 10;
struct node{
    int value, prior, l, r, cnt;
	bool reverse;
} treap[maxN];      

namespace NT{
	const int MOD = 1e7 + 9;
	typedef unsigned int ui;
	ui state;

	void init(){state = time(0);} 

	int rand(ui length){
	    state = 1234567891u * state + 999119999u; 
	    return (1ull * state * length) >> 32;
	}
}

namespace NODE{
    int T = 1;
    int create(){
		return T++;
    }

    int init_node(int value){
		int t = create();
		treap[t] = {value, NT::rand(1e8), 0, 0, 1, 0};
		return t;
    }
}

int cnt(int t){
    return t ? treap[t].cnt : 0;
}

void upd_cnt(int t){
    if(t)
		treap[t].cnt = 1 + cnt(treap[t].l) + cnt(treap[t].r);
}

void upd_node(int t){
	if(not t) return;
	treap[t].reverse ^= 1;
}

void push(int t){
	if(not t) return;
	if(treap[t].reverse){
		swap(treap[t].l, treap[t].r);
		upd_node(treap[t].l);
		upd_node(treap[t].r);
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

void query(int& t, int a, int b){
	int t1 = 0, t2 = 0, t3 = 0;
	split(t, a, t1, t2);
	split(t2, b-a+1, t2, t3);
	upd_node(t2);
	merge(t, t1, t2);
	merge(t, t, t3);
}

int find(int t, int pos, int add = 0){
	if(not t) return -1;
	push(t);
	int cur_key = add + cnt(treap[t].l);
	if(cur_key == pos) return treap[t].value;
	if(cur_key > pos) return find(treap[t].l, pos, add);
	return find(treap[t].r, pos, add + cnt(treap[t].l) + 1); 
}


char s[maxN], ans[maxN];

int main(){

    NT::init();
    int root = 0;

	int N, L, R;

	scanf("%d %d %d", &N, &L, &R);
	scanf("%s", s);

	for(int i = 0; i < N; ++i)
		insert(root, i, s[i]);

	int Q;
	scanf("%d\n", &Q);
	
	while(Q--){
		char c = getchar(); getchar();
		if(c == 'Q'){ 
			char d = getchar(); getchar();
			printf("%c", (char)find(root, d == 'L' ? L - 1 : R - 1));
		}
		else if(c == 'R')
			query(root, L-1, R-1);
		else{
			char d = getchar(); getchar(); 
			char e = getchar(); getchar();			
			
			d == 'L' ? (e == 'L' ? L-- : L++) : (e == 'L' ? R-- : R++);
		}
	}
	
	puts("");

    return 0;
}