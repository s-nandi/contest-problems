// binary representation uniqueness
// https://codesprintla20-individual.kattis.com/problems/codesprintla20.dininghalldilemma

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k; ll d;
  cin >> n >> k >> d;
  vi a(k);
  ll tot = 0;
  trav(i, a) {cin >> i; --i; tot += (1LL << i);}
  sort(all(a));
  auto rem = d - tot;
  if (rem & 1) {
    cout << 0 << '\n';
    exit(0);
  } else {
    rem /= 2; 
  }
  rep(i, 0, 62) {
    if (rem & (1LL << i)) {
      if (binary_search(all(a), i)) {
        cout << 0 << '\n';
        exit(0);
      }
    }
  }
  cout << (1LL << k) << '\n';
}
