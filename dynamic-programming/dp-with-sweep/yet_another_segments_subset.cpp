// dp + line sweep, process shortest to longest segment, fix outermost segment S and count # of non-intersecting segments contained within S
// https://codeforces.com/contest/1399/problem/F

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

const int MAXM = 6000;

vi sorted;
auto getindex(auto val) {
  return lower_bound(all(sorted), val) - begin(sorted);
}

auto maxx(auto& a, auto b){a = max(a, b);}

int non_overlapping(const auto& a, const auto& subset, const auto& dp) {
  int m = sz(sorted);
  vi bestby(m + 2);
  int it = 0;
  rep(i, 0, sz(sorted) + 1) {
    while (it < sz(subset) and a[subset[it]].first == i) {
      auto k = subset[it];
      maxx(bestby[a[k].second + 1], bestby[i] + dp[k]);
      it++;
    }
    maxx(bestby[i + 1], bestby[i]);
  }
  return bestby[m + 1];
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<pii> a(n);
    trav(i, a) cin >> i.first >> i.second;
    sorted.resize(2 * n);
    rep(i, 0, n) {
      sorted[2 * i] = a[i].first;
      sorted[2 * i + 1] = a[i].second;
    }
    sort(all(sorted));
    sorted.erase(unique(all(sorted)), end(sorted));
    trav(i, a) {
      i.first = getindex(i.first);
      i.second = getindex(i.second);
    }
    a.PB({0, sz(sorted)});
    sort(all(a), [&](const pii& i, const pii& j){
                   return i.second - i.first < j.second - j.first;
                 });
    vi indices_by_first(n + 1);
    iota(all(indices_by_first), 0);
    sort(all(indices_by_first), [&](int i, int j){return a[i].first < a[j].first;});
    
    vi dp(n + 1);
    rep(i, 0, n + 1) {
      vi subintervals;
      trav(j, indices_by_first) if (i != j) {
        if (a[i].first <= a[j].first and a[j].second <= a[i].second)
          subintervals.PB(j);
      }
      dp[i] = non_overlapping(a, subintervals, dp) + 1;
    }
    auto res = dp[n] - 1;
    cout << res << '\n';
  }
}
