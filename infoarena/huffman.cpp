/**
 * @author Miguel Mini
 * @tag bfs, huffman_code, fast_input
 * @idea
 *      - we must use fast input.
 * 
 *      - assume that v is sorted.
 * 
 *      - we can notice that created
 *      elements has weight non-decreasing. 
 *      
 *      - we can maintain two double queues
 *      and obtain best sum with first two
 *      elements of each of them.
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 10;
int H[maxn][2];
int e = 1;
long long val[maxn];
int dist[maxn];
long long w[maxn];

void bfs(int src) {
    val[src] = dist[src] = 0;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty()) {
        int q = Q.front(); Q.pop();
        for (int i = 0; i < 2; ++i) {
            if (!H[q][i]) continue;
            dist[H[q][i]] = dist[q] + 1;
            val[H[q][i]] = val[q] * 2 + i;
            Q.push(H[q][i]);
        }
    }
}

int build(long long w[], int n) {
    deque<int> a, b;
    for (int i = 1; i <= n; ++i) a.push_back(i);
    e = n + 1;
    while (a.size() + b.size() > 1) {
        pair<int, int> q = {0, 0}; 
        long long temp = 2e18; 
        if (a.size() >= 2 && temp > w[a[0]] + w[a[1]]) {
            q = {a[0], a[1]};
            temp = w[a[0]] + w[a[1]];
        }
        if (b.size() >= 2 && temp > w[b[0]] + w[b[1]]) {
            q = {b[0], b[1]};
            temp = w[b[0]] + w[b[1]];
        }
        if (a.size() >= 1 && b.size() >= 1 && temp > w[a[0]] + w[b[0]]) {
            q = {a[0], b[0]};
            temp = w[a[0]] + w[b[0]];
        }
        w[e] = temp;
        H[e][0] = q.first;
        H[e][1] = q.second;
        if (a.size() >= 1 && q.first == a[0]) a.pop_front();
        else b.pop_front();
        if (a.size() >= 1 && q.second == a[0]) a.pop_front();
        else b.pop_front();
        b.push_back(e++);
        if (a.empty()) swap(a, b);
    }   
    return a[0];
} 

void read(int& x) {
    int c = getchar();
    while (c < '0') c = getchar();
    x = 0;
    while (c >= '0') {
        x = (x<<3) + (x<<1) + c - '0';
        c = getchar();
    }
}

int main() {
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
    int n;
    read(n);
    for (int i = 1; i <= n; ++i) {
        int x;
        read(x);
        w[i] = x;
    }
    bfs(build(w, n));
    long long ans = 0;
    for (int i = 1; i <= n; ++i) ans += dist[i] *1ll * w[i];
    printf("%lld\n", ans);
    for (int i = 1; i <= n; ++i) {
        printf("%d %lld\n", dist[i], val[i]);
    }
    return 0;
}