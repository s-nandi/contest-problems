// permutation cycles (functional graph), dp on bitmasks (enumerating submasks, reconstructing solution), fix element to be moved out and follow ripple effect (must be cycle)
// https://codeforces.com/contest/1243/problem/E

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

using assign = tuple<int, int, int>; // old box, value, new box

auto maxx(auto& a, auto b){return a < b ? a = b, true : false;}

int dfs(auto& boxes, auto& diffs, const auto& location, int i, int j, int si, int sj, auto& assignments, int mask = 0) {
  if (mask & (1 << i)) {
    if (i == si and j == sj) return mask;
    else return -1;
  } else {
    int nmask = mask | (1 << i);
    auto val = boxes[i][j];
    auto need = diffs[i] + val;
    if (!location.count(need)) return -1;
    const auto& [ni, nj] = location.at(need);
    assignments.PB({ni, need, i}); // box i needs 'need' from box ni
    return dfs(boxes, diffs, location, ni, nj, si, sj, assignments, nmask);
  }
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vector<vi> boxes(n);
  rep(i, 0, n) {
    int k;
    cin >> k;
    boxes[i].resize(k);
    trav(j, boxes[i]) cin >> j;
  }
  vector<ll> sums(n);
  map<ll, pii> location;
  rep(i, 0, n) {
    sums[i] = accumulate(all(boxes[i]), 0LL);
    rep(j, 0, sz(boxes[i]))
      location[boxes[i][j]] = {i, j};
  }
  auto total = accumulate(all(sums), 0LL);
  if (total % n != 0) {
    cout << "No" << '\n';
    exit(0);
  }
  auto target = total / n;
  vector<ll> diffs(n);
  rep(i, 0, n) diffs[i] = target - sums[i];
  
  vi feas(1 << n);
  vector<vector<assign>> assignments(1 << n);
  rep(i, 0, n) {
    rep(j, 0, sz(boxes[i])) {
      vector<assign> curr;
      auto mask = dfs(boxes, diffs, location, i, j, i, j, curr);
      if (mask < 0) continue;
      feas[mask] = true;
      assignments[mask] = move(curr);
    }
  }
  
  vi dp(1 << n), prv(1 << n);
  dp[0] = true;
  rep(bm, 0, 1 << n) {
    for (int sm = bm; sm; sm = (sm - 1) & bm)
      if (maxx(dp[bm], dp[bm - sm] and feas[sm]))
        prv[bm] = bm - sm;
  }
  
  int FULL = (1 << n) - 1;
  if (!dp[FULL]) cout << "No" << '\n';
  else {
    cout << "Yes" << '\n';
    vector<pii> sol(n);
    for (auto mask = FULL; mask; mask = prv[mask]) {
      auto sm = mask - prv[mask];
      for (const auto& [ind, val, to]: assignments[sm])
        sol[ind] = {val, to};
    }
    for (const auto& [val, to]: sol)
      cout << val << " " << (to + 1) << '\n';
  }
}
