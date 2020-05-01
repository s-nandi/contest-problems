// segtree, counting inversions (sum of inversions across all contiguous ranges), fix right endpoint
// https://utipc19.kattis.com/problems/utipc19.permutationsontheroadalice
// 2019 Spring UT Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)

struct ST {
  int s;
  vector<ll> v;
  ST(int s) : s{s}, v(2 * s) {}
  void update(int p, ll d) {
    v[p += s] = d;
    for (p >>= 1; p >= 1; p >>= 1)
      v[p] = v[2 * p] + v[2 * p + 1];
  }
  ll query(int l, int r) {
    ll acc = 0;
    for (l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) acc += v[l];
      if (~r & 1) acc += v[r];
    }
    return acc;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) {
      cin >> i; 
      --i;
  }

  ST st(n);
  ll sol = 0;
  ll acc = 0;
  rep(i, 0, n) {
    auto delta = st.query(a[i], n - 1);
    acc += delta; // acc contains # of inversions with i as right endpoint
                  // i can extend all inversions ending at (i - 1), and creates delta units of new inversions
    sol += acc;
    st.update(a[i], i + 1); // since element at position i, with smaller element at j > i, creates 
                            // i + 1 ranges with 1 inversion with element j: [i, j], [i - 1, j], ..., [0, j]
  }
  cout << sol << '\n';
}
