#include <bits/stdc++.h>
using namespace std;

struct Point {
    int t1, t2;
    char d1, d2;
    Point(int t1, int t2, char d1, char d2):
        t1(t1), t2(t2), d1(d1), d2(d2) {}
    bool operator<(Point other) const {
        return t1 < other.t1 || (t1 == other.t1 && t2 > other.t2);
    };
};

const int maxn = 1e5 + 10;
int ft[maxn];
int m;

void upd(int pos, int v) {
    while (pos < m) {
        ft[pos] = max(ft[pos], v);
        pos += pos&-pos;
    }
}

int qry(int pos) {
    int ans = 0;
    while (pos > 0) {
        ans = max(ans, ft[pos]);
        pos -= pos&-pos;
    }
    return ans;
}   

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<Point> p;
        map<int, int> X;
        for (int i = 0; i < n; ++i) {
            int t1, t2;
            char d1, d2;
            scanf("%d%c%d%c\n", &t1, &d1, &t2, &d2);
            //cout << t1 << " " << d1 << " " << t2 << " " << d2 << endl;
            X[t1]; X[t2];
            p.push_back({t1, t2, d1, d2});
        }
        m = X.size();
        int id = 0; 
        for (auto& x : X) x.second = id++;
        for (int i = 0; i < n; ++i) {
            if (p[i].d1 == 'W') p[i].t1 = m - 1 - X[p[i].t1] + 1;
            else p[i].t1 = m + X[p[i].t1] + 1;

            if (p[i].d2 == 'W') p[i].t2 = X[p[i].t2] + 1;
            else p[i].t2 = m + m - 1 - X[p[i].t2] + 1; 
        }
        m = 2 * m + 10;
        for (int i = 0; i < m; ++i) ft[i] = 0;
        sort(p.begin(), p.end());
        reverse(p.begin(), p.end());
        int len = 0;
        for (int i = 0; i < p.size(); ++i) {
            //cout << p[i].t1 << " " << p[i].t2 << endl;
            int temp = qry(p[i].t2) + 1;
            len = max(len, temp);
            upd(p[i].t2, temp);
        }
        cout << len << '\n';
    }
    return 0;
}