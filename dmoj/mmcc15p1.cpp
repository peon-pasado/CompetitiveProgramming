#include "inaho.h"
#include <bits/stdc++.h>
#define sz(v) static_cast<int>(v.size())
#define clear_fit(v) v.clear(), v.shrink_to_fit()
#define all(v) v.begin(), v.end()
#define unique(v) v.erase(unique(all(v)), v.end())
#define fast_io cin.tie(nullptr)->sync_with_stdio(false)

using namespace std;

struct dsu_rollback {

    vector<int> pi;
    vector<size_t> size_tree;
    stack<int> changes;

    dsu_rollback() {}

    dsu_rollback(int n) {
        pi.resize(n);
        iota(all(pi), 0);
        size_tree.resize(n, 1);
    }

    void add() {
        pi.push_back(sz(pi));
        size_tree.push_back(1);
    }

    int get_root(int x) {
        return pi[x] != x ? get_root(pi[x]) : x;
    }

    void merge(int u, int v) {
        u = get_root(u);
        v = get_root(v);

        if (u == v) {
            changes.push(-1);
            return;
        }
        if (size_tree[u] < size_tree[v]) swap(u, v);
        
        size_tree[u] += size_tree[v];
        pi[v] = u;
        changes.push(v);
    } 

    bool same(int u, int v) {
        return get_root(u) == get_root(v);
    }

    void undo() {
        if (changes.empty()) return;
        if (changes.top() >= 0) {
            int v = changes.top();
            size_tree[pi[v]] -= size_tree[v];
            pi[v] = v;          
        }
        changes.pop();
    }
} dsu;


void Init(int N) {
    dsu = dsu_rollback(N);
}

void AddEdge(int U, int V) {
    U--; V--;
    dsu.merge(U, V);
}

void RemoveLastEdge() {
    dsu.undo();
}

int GetSize(int U) {
    U--;
    return dsu.size_tree[dsu.get_root(U)];
}