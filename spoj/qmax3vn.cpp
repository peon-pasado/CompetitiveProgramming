#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <climits>
#include <cstdlib>
using namespace std;


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

const int maxN = 1e5 + 5;
struct node_treap{
    int prior, l, r, cnt, h, max;
} T[maxN];

int elements = 0;

int cnt(int t){
    return t ? T[t].cnt : 0;
}

int Max(int t){
    return t ? T[t].max : INT_MIN;
}

void upd(int t){
    if(t){
	T[t].cnt = cnt(T[t].l) + 1 + cnt(T[t].r);
	T[t].max = max(T[t].h, max(Max(T[t].l), Max(T[t].r)));
    }
}

void split(int t, int& l, int& r, int key){
    if(t == 0) l = r = 0;
    else if(cnt(T[t].l) < key)
	split(T[t].r, T[t].r, r, key - cnt(T[t].l) - 1), l = t;
    else
        split(T[t].l, l, T[t].l, key), r = t;
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

void insert(int& t, int key, int prior, int h){
    T[++elements] = {prior, 0, 0, 1, h, h};

    if(t == 0) t = elements;
    else{
	int r;
	split(t, t, r, key);
	merge(t, t, elements);
	merge(t, t, r);
    }
}

int query(int& t, int l, int r){
    int L, M, R;
    split(t, L, M, l);
    split(M, M, R, r - l + 1);
    int ans = T[M].max;
    merge(R, M, R);
    merge(t, L, R);
    return ans;
}


int main(){

    NT::init();
    int root = 0, n;
    scanf("%d\n", &n);
    while(n--){
	char c;
        int a, b;
	scanf("%c %d %d\n", &c, &a, &b);

	if(c == 'A')
	    insert(root, b-1, NT::rand(1e9), a);
	else
            printf("%d\n", query(root, a-1, b-1));
    }

    

    return 0;
}

