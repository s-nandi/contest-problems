// permutation cycles, greedy
// https://codeforces.com/contest/1367/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
 
    map<char, int> freq;
    trav(c, s) freq[c]++;
 
    vi sizes;
    for (const auto& [c, cnt]: freq)
      sizes.PB(cnt);
    sort(all(sizes), greater<>{});
 
    int best = 1;
    rep(s, 2, n + 1) {
      bool feas = true;
 
      vi vis(s);
      int curr = 0;
      while (!vis[curr]) {
        vis[curr] = true;
        curr = (curr + k) % s;
      }
      int bsz = accumulate(all(vis), 0);
      assert(s % bsz == 0);
      int blocks = s / bsz;
 
      multiset<int, greater<>> avail(greater<>{});
      trav(i, sizes) avail.insert(i);
 
      rep(i, 0, blocks) {
        auto have = *avail.begin();
        if (have < bsz) {
          feas = false;
          break;
        }
        avail.erase(begin(avail));
        have -= bsz;
        avail.insert(have);
      }
      if (feas) best = s;
    }
    cout << best << '\n';
    
  }
}
