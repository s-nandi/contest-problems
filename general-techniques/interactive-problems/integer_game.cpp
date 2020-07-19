// interactive, constructive, solving backwards (second to last state must be arithmetic progression, 2c-a-b forces this to happen eventually)
// https://codeforces.com/contest/1375/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)size(x)
#define PB push_back

auto delta(auto a) {
  sort(all(a));
  return 2LL * a[2] - a[1] - a[0];
}

auto ap_delta(auto a) {
  sort(all(a));
  if (a[2] - a[1] == a[1] - a[0])
    return a[2] - a[1];
  else
    return -1LL;
}

int send(auto stones) {
  cout << stones << endl;
  int pile;
  cin >> pile;
  if (pile == 0 or pile == -1) exit(0);
  return pile;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  array<ll, 3> a;
  trav(i, a) cin >> i;
  
  cout << "First" << endl;
  rep(it, 0, 2) {
    auto stones = delta(a);
    int pile = send(stones);
    a[--pile] += stones;
  }
  auto stones = ap_delta(a);
  assert(stones != -1);
  send(stones);
  assert(false);
}
