// pigeonhole (exploit small mod - any collisions in mod result in a 0 product)
// https://codeforces.com/contest/1305/problem/C

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vi a(n);
    trav(i, a) cin >> i;

    if (n > m) {puts("0"); exit(0);}
    auto acc = 1LL;
    rep(i, 0, n) {
      rep(j, i + 1, n) {
        acc *= abs(a[i] - a[j]) % m;
        acc %= m;
      }
    }
    cout << acc << '\n';
}
