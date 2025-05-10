#include<bits/stdc++.h>
using namespace::std;

const long long inf = 3000000000000000000LL + 10;

const int N = 100000 + 5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

long long random(long long l, long long r){
	return uniform_int_distribution<long long>(l, r)(rng);
}

struct node{
	int cnt;
	int frec;
	long long val;
	long long priority;
	node* left;
	node* right;
	node(long long val, int frec = 1) : val(val), frec(frec) {
		cnt = frec;
		priority = random(0, 1000000000000000000LL);
		left = right = nullptr;
	}
};

int n;
long long x[N];
long long y[N];

int cnt(node* t){
	return t ? t -> cnt : 0;
}

void update(node* t){
	if(t) t -> cnt = cnt(t -> left) + cnt(t -> right) + t -> frec;
}

node* merge(node* l, node* r){
	if(l == nullptr) return r;
	if(r == nullptr) return l;
	if(l -> priority > r -> priority){
		l -> right = merge(l -> right, r);
		update(l);
		return l;
	}
	else{
		r -> left = merge(l, r -> left);
		update(r);
		return r;
	}
}

pair<node*, node*> split(node* t, long long x){
	if(t == nullptr){
		return {nullptr, nullptr};
	}
	if(t -> val <= x){
		pair<node*, node*> p = split(t -> right, x);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else{
		pair<node*, node*> p = split(t -> left, x);
		t -> left = p.second;
		update(t);
		return {p.first, t};
	}
}

node* insert(node* u, long long x){
	pair<node*, node*> p1 = split(u, x);
	pair<node*, node*> p2 = split(p1.first, x - 1);
	int new_frec = cnt(p2.second) + 1;
	u = merge(p2.first, new node(x, new_frec));
	u = merge(u, p1.second);
	return u;
}

node* remove(node*u, long long x){
	pair<node*, node*> p1 = split(u, x);
	pair<node*, node*> p2 = split(p1.first, x - 1);
	int new_frec = cnt(p2.second) - 1;
	if(new_frec > 0){
		u = merge(p2.first, new node(x, new_frec));
	}
	else{
		u = p2.first;
	}
	u = merge(u, p1.second);
	return u;
}

long long getMax(node* t){
	if(t == nullptr) return -inf;
	if(t -> right) return getMax(t -> right);
	return t -> val;
}

long long getMin(node* t){
	if(t == nullptr) return inf;
	if(t -> left) return getMin(t -> left);
	return t -> val;
}

node* getClosest(node* t, long long x, long long &res){
	pair<node*, node*> p = split(t, x - 1);
	long long L = getMax(p.first);
	long long R = getMin(p.second);
	res = inf;
	if(L < x) res = min(res, x - L);
	if(R >= x) res = min(res, R - x);
	t = merge(p.first, p.second);
	return t;
}

node* getBestDist(node* t, long long lower, long long x, long long &res){
	pair<node*, node*> p = split(t, lower - 1);
	p.second = getClosest(p.second, x, res);
	t = merge(p.first, p.second);
	return t;
}

long long solveOnce(){
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return x[i] > x[j];
	});
	vector<long long> maxB(n);
	node* T = nullptr;
	maxB[0] = y[p[0]];
	for(int i = 1; i < n; i++){
		int at = p[i];
		maxB[i] = max(maxB[i - 1], y[at]);
	}
	for(int i = 0; i < n; i++){
		int at = p[i];
		T = insert(T, y[at]);
	}
	long long res = inf;
	for(int i = 0; i < n; i++){
		int at = p[i];
		long long maxA = x[at];
		long long maxb = i == 0 ? -inf : maxB[i - 1];
		T = remove(T, y[at]);
		if(maxb >= maxA){
			res = min(res, maxb - maxA);
		}
		else{
			long long act;
			if(maxb != -inf){
				res = min(res, maxA - maxb);
			}
			T = getBestDist(T, maxb, maxA, act);
			res = min(res, act);
		}
	}
	return res;
}

long long solve(){
	long long res = solveOnce();
	for(int i = 1; i <= n; i++) swap(x[i], y[i]);
	res = min(res, solveOnce());
	for(int i = 1; i <= n; i++) swap(x[i], y[i]);
	return res;
}

long long brute(){
	long long res = inf;
	for(int mask = 1; mask + 1 < (1 << n); mask++){
		long long maxA = -1, maxB = -1;
		for(int i = 0; i < n; i++){
			if((mask >> i) & 1){
				maxA = max(maxA, x[i + 1]);
			}
			else{
				maxB = max(maxB, y[i + 1]);
			}
		}
		res = min(res, abs(maxA - maxB));
	}
	return res;
}

bool test(long long &jans, long long &pans){
	n = random(2, 20);
	for(int i = 1; i <= n; i++){
		x[i] = random(0, 1000000000000000000LL);
		y[i] = random(0, 1000000000000000000LL);
	}
	jans = brute();
	pans = solve();
	return jans == pans;
}

void printData(){
	cout << n << endl;
	for(int i = 1; i <= n; i++) cout << x[i] << " " << y[i] << endl;
}


void stress(){
	for(int i = 1; i <= 300; i++){
		long long opt, ans;
		cout << "Running on test " << i << endl;
		if(!test(opt, ans)){
			cout << "Wrong answer on test " << i << endl;
			printData();
			cout << "Optimal: " << opt << endl;
			cout << "Output: " << ans << endl;
			return;
		}
		cout << endl << endl;
	}
	puts("Accepted");
}

int main(){
//	stress();
	int t;
	scanf("%d", &t);
	while(t--){
		long long maxA = -inf, max2A = -inf, maxB = -inf, max2B = -inf;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%lld %lld", &x[i], &y[i]);
		}
		printf("%lld\n", solve());
	}
	return 0;
}