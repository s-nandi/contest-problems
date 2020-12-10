// closest left/right stack, prefix mins
// https://codeforces.com/contest/1450/problem/D
// Explanation of this solution: https://codeforces.com/blog/entry/85348?#comment-730542
// Note: Editorial solution differs a lot and uses different observations

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) {cin >> i; --i;}
 
    stack<int> stk;
    vi sleft(n, -1), sright(n, n);
    rep(i, 0, n) {
      while (!empty(stk) and a[i] < a[stk.top()]) {
        sright[stk.top()] = i;
        stk.pop();
      }
      if (!empty(stk)) sleft[i] = a[i] == a[stk.top()] ? sleft[stk.top()] : stk.top();
      stk.push(i);
    }
 
    vi maxwindow(n);
    rep(i, 0, n) {
      auto lgap = i - sleft[i] - 1;
      auto rgap = sright[i] - i - 1;
      auto livetill = lgap + rgap + 1;
      maxwindow[a[i]] = max(maxwindow[a[i]], livetill);
    }

    vi pmin(n);
    partial_sum(all(maxwindow), begin(pmin), [](auto acc, auto v){return min(acc, v);});

    vi res(n);
    rep(i, 0, n) {
      auto k = n - i;
      if (pmin[i] >= k) res[k - 1] = 1;
    }
    trav(i, res) cout << i; cout << '\n';
  }
}
