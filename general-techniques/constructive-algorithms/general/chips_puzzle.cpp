// constructive (simulation), convert 'from' to 'to' via symmetry (use intermediate canonical form), amortized analysis (each digit moves at most twice in each half of process)
// https://codeforces.com/contest/1054/problem/E

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

using op = array<int, 4>;

auto convert_to_canonical(auto& state) { // all 0's in top left, all 1's in bottom right
  int n = sz(state);
  int m = sz(state[0]);
  vector<op> res;
  vector<pii> corners = {{0, 0}, {n - 1, m - 1}};
  auto addop = [&](int i1, int j1, int i2, int j2) {
                 assert(!empty(state[i1][j1]));
                 res.PB({i1 + 1, j1 + 1, i2 + 1, j2 + 1});
                 state[i2][j2].push_front(state[i1][j1].back());
                 state[i1][j1].pop_back();
               };
  for (const auto& [i, j]: corners) {
    auto other_i = i == 0 ? i + 1 : i - 1; // move corner digits into adjacent cell before they get buried by other 1's/0's to avoid unnecessary ops
    trav(c, state[i][j]) addop(i, j, other_i, j);
  }
  set<pii> unused;
  rep(i, 0, n) rep(j, 0, m) unused.insert({i, j});
  while (!empty(unused)) {
    auto [i, j] = *begin(unused);
    unused.erase(begin(unused));
    if (count(all(corners), pii{i, j})) continue;
    auto rev = string(rbegin(state[i][j]), rend(state[i][j]));
    trav(c, rev) {
      auto goal_i = corners[c].first;
      auto goal_j = corners[c].second;
      if (i != goal_i) { // make progress either horizontally or vertically (if already same horizontal)
        addop(i, j, goal_i, j);
        unused.insert({goal_i, j});
      } else {
        addop(i, j, i, goal_j);
        unused.insert({i, goal_j});
      }
    }
  }
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  auto start = vector(n, vector<deque<int>>(m));
  auto finish = vector(n, vector<deque<int>>(m));
  rep(i, 0, n) rep(j, 0, m) {
    string s;
    cin >> s;
    trav(c, s) start[i][j].PB(c - '0');
  }
  rep(i, 0, n) rep(j, 0, m) {
    string s;
    cin >> s;
    trav(c, s) finish[i][j].push_front(c - '0'); // reverse string since the steps to go from "finish" to canonical form must be reversed
                                                 // if we naively reverse the steps, we'd end up popping from front and adding to back -- this is same
                                                 // as reversing the string up front and doing the original operations (pop back, push front)
  }

  auto flip_operation = [](const op& o){ // swap 'from' and 'to' cells
                          op res{};
                          rep(i, 0, sz(res)) res[i] = o[i ^ 2];
                          return res;
                        };

  auto steps_first = convert_to_canonical(start);
  auto steps_second = convert_to_canonical(finish);
  reverse(all(steps_second)); // mirror the steps taken
  transform(all(steps_second), begin(steps_second), flip_operation);
  
  cout << sz(steps_first) + sz(steps_second) << '\n';
  trav(elem, steps_first) {
    trav(i, elem) cout << i << " "; cout << '\n';
  }
  trav(elem, steps_second) {
    trav(i, elem) cout << i << " "; cout << '\n';
  }
}
