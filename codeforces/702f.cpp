#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 10;

namespace NT{
	const int MOD = 1e7 + 9;
	typedef unsigned int ui;
	ui seed=0x12F81AC;
	inline int rand(){
		seed^=seed<<13;
		seed^=seed>>17;
		seed^=seed<<5;
		return seed;
	}
}
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) f=ch=='-'?-1:f,ch=getchar();
	while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*f;
}

int buf[30];
inline void write(int x){
	if (x<0) putchar('-'),x=-x;
	for (;x;x/=10) buf[++buf[0]]=x%10;
	if (!buf[0]) buf[++buf[0]]=0;
	for (;buf[0];putchar('0'+buf[buf[0]--]));
}

namespace NODE{
    int T = 1;
	struct node{
    	int key, prior, l, r, cnt, items, id, c, cost;
		bool lazy;
	} Tr[maxN];     

    int create(){
		return T++;
    }

    int init_node(int key, int id){
		int t = create();
		Tr[t] = {key, NT::rand(), 0, 0, 1, 0, id, 0, 0, 0};
		return t;
    }
}

using namespace NODE;

void upd_node(int t, int val, int ct){
	if(not t) return;
	Tr[t].lazy = 1;
	Tr[t].c += ct;
	Tr[t].cost += val;
	Tr[t].items += ct;
	Tr[t].key -= val;
}

void push(int t){
	if(not t) return;
	if(Tr[t].lazy){
		upd_node(Tr[t].l, Tr[t].cost, Tr[t].c);
		upd_node(Tr[t].r, Tr[t].cost, Tr[t].c);
		Tr[t].c = 0;
		Tr[t].cost = 0;
		Tr[t].lazy = 0;
	}
}


void split(int t, int key, int& l, int& r){
    if(not t) return void(l = r = 0);    
	
	push(t);
	if(key <= Tr[t].key) 
		split(Tr[t].l, key, l, Tr[t].l), r = t;
    else
        split(Tr[t].r, key, Tr[t].r, r), l = t;

}

void merge(int& t, int l, int r){
	push(l);
	push(r);    

    if(not l or not r) t = max(l, r);
	else if(Tr[l].prior > Tr[r].prior)
		merge(Tr[l].r, Tr[l].r, r), t = l;
    else
        merge(Tr[r].l, l, Tr[r].l), t = r;
}

void insert(int& t, int it){
	if(not t){
		t = it;
		return;
	}
	int t1 = 0, t2 = 0;	
	split(t, Tr[it].key, t1, t2);
	merge(t1, t1, it);
	merge(t, t1, t2);
}

void Union(int& l, int r){
	if(not r) return;
	//if(Tr[l].prior < Tr[r].prior) swap(l, r);
	push(r);
	int lt = Tr[r].l, rt = Tr[r].r;

	Tr[r].l = Tr[r].r = 0;
	insert(l, r);
	Union(l, lt);
	Union(l, rt);
}

int ans[maxN];
void find(int t){
	if(not t) return;
	ans[Tr[t].id] = Tr[t].items;
	push(t);
	find(Tr[t].l);
	find(Tr[t].r);
}


struct data{
	int q, c;
	bool operator<(const data& p){
		return q > p.q  or q == p.q and c < p.c;
	}
} shirt[maxN];

int K, N;

int main(){

    int root = 0;

	N = read();
	for(int i = 0; i < N; ++i){
		int c, q;
		c = read();
		q = read();
		shirt[i] = {q, c};
	}

	K = read();
	for(int i = 0; i < K; ++i){
		int b = read();
		insert(root, NODE::init_node(b, i));
	}

	sort(shirt, shirt+N);
	
	for(int i = 0; i < N; ++i){
		int t1, t2;
		split(root, shirt[i].c, root, t1);
		upd_node(t1, shirt[i].c, 1);		
		split(t1, shirt[i].c, t2, t1);
		Union(root, t2);
		merge(root, root, t1);
	}

	find(root);
	for(int i = 0; i < K; ++i)
		write(ans[i]), putchar(' ');

    return 0;
}