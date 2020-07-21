// constructive (operate on 1 element prefix if needed then operate on k-len prefix to fix element k - 1), greedy (go in dec. len of prefix)
// https://codeforces.com/contest/1381/problem/A2

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

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    string ss, tt;
    cin >> ss >> tt;
    vi s(n), t(n);
    rep(i, 0, n) s[i] = ss[i] - '0', t[i] = tt[i] - '0';

    vi res;
    bool flipped = false;
    bool front = true;
    pii range = {0, n - 1};
    auto head = [&]() {
                  auto c = front ? s[range.first] : s[range.second];
                  return c ^ flipped;
                };
    auto pop_and_flip = [&]() {
                          if (front) range.first++;
                          else range.second--;
                          flipped = !flipped;
                          front = !front;
                        };
    for (int i = sz(t) - 1; i >= 0; i--) {
      if (i == 0) {
        if (head() != t[i]) res.PB(1);
      } else {
        if (head() == t[i]) res.PB(1);
        res.PB(i + 1);
        pop_and_flip();
      }
    }
    cout << sz(res) << " ";
    trav(i, res) cout << i << " "; cout << '\n';
  }
}
