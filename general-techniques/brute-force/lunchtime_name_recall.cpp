// brute force (memoized states), heuristics (hashing, early termination, symmetry)
// https://open.kattis.com/problems/lunchtimenamerecall
// 2020 North American Championships

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)size(x)

const int MAXN = 30;
const int MAXM = 10;
int n, m;
int a[MAXM + 5];

const int NUM_HASHES = 2; 
using hashT = array<ll, NUM_HASHES>;
const ll alpha = 257;
const auto MOD = vector{1000000007, 1000000009};
struct hasher {
  hashT h{};
  void push(auto v) {rep(t, 0, NUM_HASHES) h[t] = (alpha * h[t] + v) % MOD[t];}
};

using vec = basic_string<short>; // for SSO and concatenation
using state = tuple<vec, vec, int, int>;
auto state_hash(const vec& a, const vec& b, int c, int d) {
  hasher h;
  auto sentinel = 256;
  trav(e, a) h.push(e);
  h.push(sentinel); // to differentiate a={1, 2}, b={3} from a={1}, b={2, 3} 
  trav(e, b) h.push(e);
  h.push(sentinel);
  h.push(c);
  h.push(d);
  return h.h;
}

void insert_sorted(vec& res, int elem) {
  auto it = begin(res);
  while (it != end(res) and *it < elem) ++it;
  res.insert(it, elem);
}

bool empty_or_ones(const vec& v) {
  return v.empty() or count(all(v), 1) == sz(v);
}

map<hashT, int> memo;
int recurse(const vec& todiff, const vec& fixed, int rem, int day) {
  auto hh = state_hash(todiff, fixed, rem, day); // ~ 1.5x speedup
  if (memo.count(hh)) return memo[hh];
  int best = -1;
  if (rem > accumulate(all(todiff), 0LL)) { // ? speedup
    best = -1;
  } else if (empty_or_ones(todiff) and empty_or_ones(fixed)) { // large speedup??
    cout << n << '\n';
    exit(0); 
  } else if (day == m) {
    best = count(all(todiff), 1);
  } else if (rem == 0 or todiff.empty()) {
    if (rem > 0) {
      best = -1;
    } else {
      auto newstate = todiff + fixed;
      sort(all(newstate));
      best = recurse(newstate, {}, a[day + 1], day + 1);
    }
  } else {
    auto newdiff = todiff;
    int curr = newdiff.back();
    newdiff.pop_back();
    rep(k, 0, min(rem, curr) + 1) {
      int p1 = curr - k, p2 = k;
      auto newfixed = fixed;
      if (p1) insert_sorted(newfixed, p1);
      if (p2) insert_sorted(newfixed, p2);
      auto possible = recurse(newdiff, newfixed, rem - k, day);
      best = max(best, possible);
    }
  }
  memo[hh] = best;
  return best;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  rep(i, 0, m) {
    cin >> a[i];
    a[i] = min(a[i], n - a[i]); // 2x speedup
  }
  vec init(1, n);
  auto sol = recurse(init, {}, a[0], 0);
  cout << sol << '\n';
}
