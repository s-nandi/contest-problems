// lucas thm (n choose k is odd iff n is supermask of k), sum over subsets dp
// https://codeforces.com/group/ZFgXbZSjvp/contest/274852 (problem B)
// 2020 NAPC 4

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
const int K = 20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--) {
      int n;
      cin >> n;
      vi a(n);
      trav(i, a) cin >> i;

      vi d(1 << K);
      trav(i, a) d[i]++;
      
      rep(b, 0, K)  // thanks kactl
        rep(i, 0, (1 << K))
          if (i & (1 << b))
            d[i] += d[i ^ (1 << b)];

      auto acc = 0LL;
      trav(i, a)
        acc += d[i];
      cout << acc << '\n';
    }
}
