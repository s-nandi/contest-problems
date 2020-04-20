// interactive, binary search, figuring out lying pattern with first half queries
// https://codeforces.com/contest/1011/problem/D

#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)

auto ilog2(auto x){return sizeof(x) * 8 - is_signed_v<decltype(x)> - __builtin_clz(x);}

auto ask(int i) {
  cout << i << endl;
  int res;
  cin >> res;
  if (res == 0) exit(0);
  return res;
}

int main() {
  int n, m;
  cin >> n >> m;
  vi p(m);
  rep(i, 0, m) {
    p[i] = (ask(1) == 1) ? 1 : -1;
  }
  int lo = 2, hi = n;
  rep(i, 0, ilog2(n) + 1) {
    int mid = (lo + hi) / 2;
    auto res = p[i % m] * ask(mid);
    if (res == 1) lo = mid + 1;
    else hi = mid - 1;
  }
  ask(lo);
}
