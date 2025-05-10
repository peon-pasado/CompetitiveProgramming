#include <bits/stdc++.h>
using namespace std;

const int maxn = 2502;
const int mod = 998244353;
int p[maxn];
int h[maxn];
int k, cr, cb;
int add(int a, int b) {
    return a+b>=mod?a+b-mod:a+b;
}

int mul(int64_t a, int64_t b) {
    return a*b%mod;
}

struct Node {
    int at[4];

    Node down() {
        return (*this) * Node(1,1,1,1);
    }

    Node(int x=0, int y=0, int z=0, int w=0) {
        at[0] = x;
        at[1] = y;
        at[2] = z;
        at[3] = w;
    }

    Node operator+(Node other) {
        Node r;
        for (int i=0; i<4; ++i) r.at[i] = add(at[i], other.at[i]);
        return r; 
    }

    Node operator*(Node other) {
        Node r;
        for (int i=0; i<4; ++i) r.at[i] = 0;    
        r.at[0] = mul(at[0], other.at[0]);
        
        r.at[1] = add(mul(at[0], other.at[1]), mul(at[1], other.at[0]));

        r.at[2] = add(mul(at[2], other.at[0]), mul(at[0], other.at[2]));
        r.at[2] = add(r.at[2], mul(2, mul(at[1], other.at[1])));        
        
        r.at[3] = add(mul(at[3], other.at[0]), mul(at[0], other.at[3]));
        r.at[3] = add(r.at[3], mul(3, mul(at[1], other.at[2]))); 
        r.at[3] = add(r.at[3], mul(3, mul(at[2], other.at[1]))); 
        
        return r;
    }
} dp[maxn][maxn];

int main() {
    cin >> k >> cr >> cb;
    stack<int> ss;
    ss.push(0);
    int no = 0;
    for (int i = 0; i < 2 * k; ++i) {
        string s;
        cin >> s;
        if (s[1] == 'u') {
            p[++no] = ss.top();
            ss.push(no);
        }
        else{
            ss.pop();
        }
    }
    for (int i = 1; i <= k; ++i) {
        h[i] = h[p[i]] + 1;
    }
    for (int i=0; i<=k; ++i) {
        // 0 <= b <= cb
        // hi-cr <= b <= hi
        for (int j=max(0, h[i]-cr); j <= min(h[i], cb); ++j) {
            dp[i][j].at[0] = 1;            
        }
    }
    for (int u = k; u >= 1; --u) {
        int v = p[u];
        for (int j=0; j<=h[u]; ++j) {
            dp[v][j] = dp[v][j] * (dp[u][j] + dp[u][j + 1].down());
        }
    }
    //(k - b) * b^2 = k * b^2 - b^3
    cout << add(mul(k, dp[0][0].at[2]), mod - dp[0][0].at[3]) << '\n'; 
    return 0;
}