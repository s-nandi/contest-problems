// backtracking, greedy (take smallest viable color at each step)
// https://open.kattis.com/contests/iitu7b/problems/paintings
// 2017 Mount Allison Programming Showdown (MAPS)

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

constexpr auto dbg = true;

vi smallest;
int recur(int n, cauto bad, auto& curr, auto& used) {
  if (sz(curr) == n) {
    if (empty(smallest)) smallest = curr;
    return 1;
  } else {
    auto acc = 0;
    rep(i, 0, n) if (!used[i] and (empty(curr) or !bad[curr.back()][i])) {
      used[i] = true;
      curr.PB(i);
      acc += recur(n, bad, curr, used);
      used[i] = false;
      curr.pop_back();
    }
    return acc;
  }
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    map<string, int> mapping;
    vector<string> names;
    rep(i, 0, n) {
      string s;
      cin >> s;
      mapping[s] = i;
      names.PB(s);
    }
    int m;
    cin >> m;
    auto bad = vector(n, vi(n));
    rep(it, 0, m) {
      string sa, sb;
      cin >> sa >> sb;
      auto a = mapping[sa], b = mapping[sb];
      bad[a][b] = bad[b][a] = true;
    }

    vi curr;
    vi used(n);
    smallest.clear();
    auto cnt = recur(n, bad, curr, used);

    cout << cnt << '\n';
    trav(i, smallest)
      cout << names[i] << " ";
    cout << '\n';
  }
}
