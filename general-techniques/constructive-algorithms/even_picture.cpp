// constructive, staircase of loops (there are other constructions too)
// https://codeforces.com/contest/1368/problem/C

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
 
using ii = pair<int, int>;
void generate_down(int x, int y, set<ii>& points) {
  points.insert({x, y + 1});
  points.insert({x, y + 2});
  points.insert({x + 1, y + 2});
  points.insert({x + 2, y + 2});
  points.insert({x + 2, y + 1});
  points.insert({x + 2, y});
  points.insert({x + 1, y});
  points.insert({x, y});
}
 
void generate_up(int x, int y, set<ii>& points) {
  points.insert({x, y - 1});
  points.insert({x, y - 2});
  points.insert({x - 1, y - 2});
  points.insert({x - 2, y - 2});
  points.insert({x - 2, y - 1});
  points.insert({x - 2, y});
  points.insert({x - 1, y});
  points.insert({x, y});
}
 
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  
  int x = 0, y = 0;
  set<ii> sol;
  generate_up(x, y, sol);
  rep(i, 0, n) {
    generate_down(x, y, sol);
    x += 2;
    y += 2;
  }
 
  cout << sz(sol) << '\n';
  for (const auto& [x, y]: sol)
    cout << x << " " << y << '\n';
}
