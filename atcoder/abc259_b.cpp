#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << setprecision(10) << fixed;
    double a, b, d;
    cin>>a>>b>>d;
    d *= acos(-1.) / 180.;
    //cos -sin 
    //sin  cos
    double sn = sin(d);
    double cs = cos(d);
    cout << a * cs - b * sn << ' ' << a * sn + b * cs << '\n';
    return 0;
}