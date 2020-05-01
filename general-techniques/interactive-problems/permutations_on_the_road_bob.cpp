// interactive, prefix sums, inversions
// https://utipc19.kattis.com/problems/utipc19.permutationsontheroadbob
// 2019 Spring UT Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int ask(int l, int r) {
  cout << "? " << l << " " << r << endl;
  int res;
  cin >> res;
  return res;
}

void answer(const vi& perm) {
  cout << "! "; trav(i, perm) cout << i << " "; cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi res(n);
  set<int> nums;
  vi queries(n);
  rep(i, 1, n + 1) nums.insert(i);
  rep(i, 0, n) {
    queries[i] = ask(1, i + 1);
  }
  
  for (int i = n - 1; i >= 0; i--) {
    int greater_left = i ? queries[i] - queries[i - 1] : 0;
    auto it = rbegin(nums);
    rep(j, 0, greater_left) {
      ++it;
    }
    res[i] = *it;
    nums.erase(*it);
  }
  answer(res);
}
