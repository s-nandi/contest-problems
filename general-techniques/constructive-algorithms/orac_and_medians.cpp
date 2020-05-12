// constructive (VERY proofy not-obvious), median
// https://codeforces.com/contest/1349/problem/B
// Note: Editorial solution is significantly simpler

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define sz(a) (int)size(a)
#define PB push_back

bool sum_in_range(const auto& a, int start, int end, int lo, int hi) {
  int delta = start < end ? 1 : -1;
  int acc = 0;
  for (int i = start; i != end + delta; i += delta)
    acc += a[i];
  return lo <= acc and acc <= hi;
}

bool hit_in_range(const auto& a, int start, int end, int lo, int hi) {
  int delta = start < end ? 1 : -1;
  int curr = 0;
  for (int i = start; i != end + delta; i += delta) {
    curr += a[i];
    if (lo <= curr and curr <= hi and i != start) return true;
  }
  return false;
}

int max_atleast_2(const auto& a) {
  int curr = a[0] + a[1];
  auto best = curr;
  rep(i, 2, sz(a)) {
    curr = max(curr, a[i - 1]) + a[i];
    best = max(best, curr);
  }
  return best;
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    vi a(n);
    trav(i, a) cin >> i;
    
    int cnt = 0;
    rep(i, 0, n) cnt += (a[i] == k);
    if (n == 1) {
      cout << (cnt ? "yes" : "no") << '\n';
    } else if (cnt == 0) {
      cout << "no" << '\n';
    } else {
      vi positions;
      rep(i, 0, n) if (a[i] == k)
        positions.PB(i);
      
      vi b(n);
      rep(i, 0, n)
        b[i] = (a[i] == k) ? 0 : (a[i] < k ? -1 : 1);

      bool feas = false;
      feas |= hit_in_range(b, positions[0], 0, 0, 1);
      feas |= hit_in_range(b, positions.back(), n - 1, 0, 1);
      rep(it, 1, sz(positions)) {
        feas |= hit_in_range(b, positions[it - 1], positions[it], 0, 1);
        feas |= hit_in_range(b, positions[it], positions[it - 1], 0, 1);
        feas |= sum_in_range(b, positions[it - 1], positions[it], -1, 2);
      }
      feas |= max_atleast_2(b) > 0;
      cout << (feas ? "yes" : "no") << '\n';
    }
  }
}
