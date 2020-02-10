// fenwick tree, counting # of distinct operations performed in time interval
// https://codeforces.com/gym/100729/attachments (problem C)
// 2011 Northwestern European Regional

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
 
struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {
    ll res = 0;
    for (pos++; pos > 0; pos &= pos - 1) res += s[pos-1];
    return res;
  }
  ll query(int a, int b) {
    return query(b) - query(a - 1);
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;

    vi last(n);
    iota(rbegin(last), rend(last), 0); // last element was at the top at time 0
    FT ft(m + n);
    rep(i, 0, n) ft.update(i, 1);
    
    rep(i, n, n + m) {
      int q;
      cin >> q;
      --q;
      
      auto res = ft.query(last[q] + 1, i);
      cout << res << " ";
 
      ft.update(last[q], -1);
      ft.update(i, 1);
      last[q] = i;
    }
    cout << '\n';
  }
}
