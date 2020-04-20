// interactive, greedy, dfs, good to prove
// https://codeforces.com/contest/1075/problem/D

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)

struct edge{int to;};
using graph = vector<vector<edge>>;

int ask(bool want_others_label, int i) {
  cout << (want_others_label ? 'A' : 'B') << " " << i + 1 << endl;
  int res;
  cin >> res;
  if (res == -1) exit(0);
  return res - 1;
}

void answer(int i) {
  cout << 'C' << " " << (i == -1 ? i : i + 1) << endl;
}
 
int first_hit(graph &g, auto& labels, int i, int p = -1) {
  if (binary_search(all(labels), i)) return i;
  int possible = -1;
  trav(e, g[i]) if (e.to != p)
    possible = max(possible, first_hit(g, labels, e.to, i));
  return possible;
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
 
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
 
    graph g(n);
    for (int i = 0; i < n - 1; i++) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      g[a].push_back({b});
      g[b].push_back({a});
    }
    int k1;
    cin >> k1;
    vi mine(k1);
    trav(i, mine) {
      cin >> i;
      --i;
    }
    sort(all(mine));
    int k2;
    cin >> k2;
    vi others(k2);
    trav(i, others) {
      cin >> i;
      --i;
    }
    sort(all(others));
    auto my_label_for_others = ask(false, others[0]);
    if (binary_search(all(mine), my_label_for_others)) answer(my_label_for_others);
    else {
      int first_in_mine = first_hit(g, mine, my_label_for_others);
      if (first_in_mine == -1) answer(-1);
      else {
        int others_label_for_mine = ask(true, first_in_mine);
        if (binary_search(all(others), others_label_for_mine))
          answer(first_in_mine);
        else
          answer(-1);
      }
    }
  }
}
