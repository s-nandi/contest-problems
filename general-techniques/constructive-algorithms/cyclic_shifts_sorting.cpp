// constructive (proofy), greedy (move smallest element to front ASAP), inversion parity => 1 shift operation maintains parity => odd inv parity is impossible to sort
// https://codeforces.com/contest/1374/problem/F

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

auto to_permutation(const auto& a) {
  auto sorted = a;
  sort(all(sorted));
  vi b(sz(a)), res(sz(a));
  rep(i, 0, sz(a))
    b[i] = lower_bound(begin(sorted), end(sorted), a[i]) - begin(sorted);
  map<int, int> seen;
  rep(i, 0, sz(a))
    res[i] = b[i] + (seen[b[i]]++);
  return res;
}
 
optional<vi> solve(auto a) {
  int n = sz(a);
  auto expected = a;
  sort(all(expected));
  vi sol;
  auto op = [&](int i) {
              sol.PB(i);
              rotate(begin(a) + i, begin(a) + i + 2, begin(a) + i + 3);
            };
  rep(i, 0, n - 2) {
    if (a[i] == expected[i]) continue;
    int loc = find(begin(a) + i, end(a), expected[i]) - begin(a);
    assert(loc != n);
    while (loc > i) {
      if (loc - i >= 2) {
        op(loc - 2);
        loc -= 2;
      }
      else {
        op(loc - 1);
        op(loc - 1);
        loc -= 1;
      }
    }
  }
  if (expected == a) return sol;
  else return nullopt;
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;
    auto b = to_permutation(a);
    
    const pii NIL = {0, 0};
    auto swappable = NIL;
    rep(i, 0, n) {
      rep(j, i + 1, n) {
        if (a[i] == a[j]) {
          swappable = {i, j};
          break;
        }
      }
      if (swappable != NIL) break;
    }
    
    auto possible1 = solve(b);
    swap(b[swappable.first], b[swappable.second]);
    auto possible2 = solve(b);
    
    if (!possible1 and !possible2) {cout << -1 << '\n'; continue;}
    auto res = possible1 ? *possible1 : *possible2;
    cout << sz(res) << '\n';
    trav(i, res) cout << (i + 1) << " "; cout << '\n';
  }
}
