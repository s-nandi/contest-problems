// constructive, invariant maintenance (cnt(elem) <= # partitions + 1), proofy (induction)
// https://codeforces.com/contest/1450/problem/F

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
    trav(i, a) cin >> i;

    /*
     * Consider splitting up 'a' into segments s.t. each segment is good (we MUST add a split between identical elements)
     * Such a split can yield a solution (from permutating and maybe flipping some of these segments) iff cnt(elem) <= (# segments) + 1 for all elems
     * and (# segments == # splits + 1)
     * This is identical to checking that cnt(elem) - 2 is not a strict majority for all elems; the (-2) comes from having elem be the front and end
     * of the first and last segments respectively
     *
     * Inductive Proof Sketch:
     *
     * Take a segment N with a non-majority endpoint B. 
     * There must be a different segment M with an endpoint of A because otherwise the only segment 
     * with an A endpoint is ( A, B ), but we also know there are >= 2 segments (otherwise we were already done)
     * so there must be another segment with either an endpoint of A (so we can use it as M) 
     * or another non-majority endpoint (so we can use it as N). 
     * 
     * Now just merge N and M and now you have 1 fewer segment and you've maintained the cnt(majority) <= (# segments) + 1 invariant
     */

    int splits = 0;
    vi endpoints;
    endpoints.PB(0);
    vector<pii> candidates;
    rep(i, 0, n - 1) {
      if (a[i] == a[i + 1]) {
        endpoints.PB(i);
        endpoints.PB(i + 1);
        splits++;
      } else {
        candidates.PB({i, i + 1});
      }
    }
    endpoints.PB(n - 1);

    map<int, int> freq;
    trav(i, endpoints) freq[a[i]]++;
    pii freq_val{0, -1};
    for (cauto& [val, cnt]: freq)
      freq_val = max(freq_val, pii{cnt, val});
    
    auto [majority_cnt, majority] = freq_val;
    auto rem = sz(endpoints) - majority_cnt;

    vector<tuple<int, int, int>> bydelta;
    for (cauto& [i, j]: candidates) { // could avoid sorting deltas; only candidates [i, j] s.t. i != majority and j != majority are actually useful
      auto delta = 0;
      delta += (a[i] != majority);
      delta += (a[j] != majority);
      bydelta.PB({delta, i, j});
    }

    auto isbad = [&](){return majority_cnt - 2 > rem;};

    int it = 0;
    sort(all(bydelta), greater<>{});
    while (it < sz(bydelta) and isbad()) {
      cauto& [delta, i, j] = bydelta[it];
      for (auto ind: {i, j}) { // could avoid simulating; we know each useful candidate always moves the solution 1 closer to optimal
                               // since we will only get rem += 2 from useful candidates
        if (a[ind] == majority) majority_cnt++;
        else rem++;
      }
      splits++;
      it++;
    }
    if (isbad()) {
      cout << -1 << '\n';
    } else {
      cout << splits << '\n';
    }
  }
}
