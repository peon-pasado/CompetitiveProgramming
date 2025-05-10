#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin>>n;
    vector<int> h(n);
    for (int i=0; i<n; ++i) {
        cin>>h[i];
    }
    vector<int> r(n);
    stack<int> st;
    r[n-1] = 0;
    for (int i=n-1; i>0; --i) {
        while (!st.empty() && h[st.top()] < h[i]) st.pop(); 
        st.push(i);
        r[i - 1] = st.size();
    }
    long long ans = 0;
    for (int i=0; i<n; ++i) {
        cout << r[i] << " \n"[i+1==n];
    }
    return 0;
}