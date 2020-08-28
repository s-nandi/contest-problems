// non-trivial modulo at least halves number, binary search
// https://codeforces.com/gym/292741/problem/E

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
using ll = long long;
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n;
  cin >> n;
  vector<ll> a(n);
  trav(i, a) cin >> i;
  rep(i, 0, n - 1) {
    auto it = next(begin(a), i + 1);
    while (it != end(a)) {
      if (it = partition_point(it, end(a), [&](auto val){return val > a[i];}); it == end(a)) break;
      a[i] %= *it;
    }
  }
  cout << accumulate(all(a) - 1, 0LL) << '\n';
}
