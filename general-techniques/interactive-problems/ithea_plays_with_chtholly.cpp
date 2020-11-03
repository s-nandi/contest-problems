// interactive, greedy (place [1,c/2] ([c/2, c]) in first (second) half when possible), amortized (placed # can only be replaced ceil(c / 2) times; if would replace # in other half you're already done)
// https://codeforces.com/contest/896/problem/B

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const int sentinel = -1;

auto smaller(auto a, auto b){return a < b or b == sentinel;}
auto bigger(auto a, auto b){return a > b or b == sentinel;}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m, c;
  cin >> n >> m >> c;
  auto halfvalue = (c + 1) / 2;
  vi a(n, sentinel);
  while (any_of(all(a), [&](int val){return val == sentinel;}) or !is_sorted(all(a))) {
    int p;
    cin >> p;
    int pos;
    if (p <= halfvalue) {
      auto it = find_if(all(a), [&](int val){return smaller(p, val);});
      pos = it - begin(a);
    } else {
      auto it = find_if(rbegin(a), rend(a), [&](int val){return bigger(p, val);});
      pos = (n - 1) - (it - rbegin(a));
    }
    a[pos] = p;
    cout << (pos + 1) << endl;
    if constexpr (dbg) {trav(i, a) cout << i << " "; cout << endl;}
  }
}
