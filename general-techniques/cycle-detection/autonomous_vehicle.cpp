// cycle detection (phase = 0 guaranteed), process will always generate a closed loop, implicit graph, coordinate compression
// 2020 Seoul ICPC Regional
// https://drive.google.com/file/d/1hzsh45nykISwxT9SjLuwcZyQcw9pPLyi/view?usp=sharing (problem G)
// Submit at: https://official.contest.yandex.com/mw2020fall/contest/23193/*

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

constexpr auto sentinel = pii{-1, -1};

void trimsort(auto& a) {
  sort(all(a));
  a.erase(unique(all(a)), end(a));
}

auto indexof(cauto& a, auto val) {
  return lower_bound(all(a), val) - begin(a);
}

ll getdist(const pii& a, const pii& b) {
  auto dx = a.first - b.first;
  auto dy = a.second - b.second;
  return abs(dx) + abs(dy);
}

pii in_direction(pii a, int dir, ll len) {
  pii delta;
  if (dir == 0) delta = {-1, 0};
  else if (dir == 1) delta = {0, 1};
  else if (dir == 2) delta = {1, 0};
  else delta = {0, -1};

  return {a.first + delta.first * len, a.second + delta.second * len};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, t;
  cin >> n >> t;

  vi xs, ys;
  vector<tuple<int, int, int>> hor, vert; // (fixed, lo, hi)
  pii start;
  rep(it, 0, n) {
    int bx, by, ex, ey;
    cin >> bx >> by >> ex >> ey;
    if (it == 0) start = pii{bx, by};

    if (bx == ex) { // vert
      vert.PB({bx, min(by, ey), max(by, ey)});
    } else { assert(by == ey);
      hor.PB({by, min(bx, ex), max(bx, ex)});
    }
    xs.PB(bx), xs.PB(ex);
    ys.PB(by), ys.PB(ey);
  }
  trimsort(xs);
  trimsort(ys);

  vector<pii> byind;
  map<pii, int> indices;
  int nn = 0;
  trav(x, xs) trav(y, ys) {
    byind.PB({x, y});
    indices[{x, y}] = nn++;
  }

  vector neighbors(nn, array<int, 4>{});
  trav(row, neighbors) trav(elem, row) elem = -1;

  auto joinhorizontal = [&](int x, int loy, int hiy) {
                          auto ind1 = indices[{x, loy}];
                          auto ind2 = indices[{x, hiy}];
                          neighbors[ind1][1] = ind2;
                          neighbors[ind2][3] = ind1;
                        };

  auto joinvertical = [&](int y, int lox, int hix) {
                        auto ind1 = indices[{lox, y}];
                        auto ind2 = indices[{hix, y}];
                        neighbors[ind1][2] = ind2;
                        neighbors[ind2][0] = ind1;
                      };

  for (cauto& [x, loy, hiy]: vert) {
    auto lo_ind = indexof(ys, loy);
    auto hi_ind = indexof(ys, hiy);
    rep(i, lo_ind, hi_ind) // merge [lo_ind, hi_ind]
      joinhorizontal(x, ys[i], ys[i + 1]);
  }
  for (cauto& [y, lox, hix]: hor) {
    auto lo_ind = indexof(xs, lox);
    auto hi_ind = indexof(xs, hix);
    rep(i, lo_ind, hi_ind) // merge [lo_ind, hi_ind]
      joinvertical(y, xs[i], xs[i + 1]);
  }

  int startind = indices[start];
  int startdir = find_if_not(all(neighbors[startind]),
                             [](auto to){return to == -1;}) - begin(neighbors[startind]);

  auto simulate = [&](int i, int dir) {
                    auto leftdir = (dir + 3) % 4;
                    auto oppdir = (dir + 2) % 4;
                    if (auto left = neighbors[i][leftdir]; left != -1) {
                      return pair{left, leftdir};
                    } else if (auto same = neighbors[i][dir]; same != -1) {
                      return pair{same, dir};
                    } else {
                      return pair{i, oppdir};
                    }
                  };
  
  auto step = [&simulate, &byind](int& curr, int& currdir) {
                auto [newpos, newdir] = simulate(curr, currdir);                
                auto dist = getdist(byind[curr], byind[newpos]);
                curr = newpos;
                currdir = newdir;                
                return dist;
              };
  
  int cycle = -1;
  ll cyclelength = 0;
  {
    int curr = startind;
    int currdir = startdir;
    vector vis(nn, vi(4));
    vis[curr][currdir] = true;
    for (int timer = 0; ; timer++) {
      auto len = step(curr, currdir);
      cyclelength += len;
      
      if (vis[curr][currdir]) {
        cycle = timer;
        break;
      } else {
        vis[curr][currdir] = true;
      }
    }
  }
  assert(cycle >= 0);

  auto curr = startind;
  auto currdir = startdir;
  auto rem = t % cyclelength;
  auto stopifend = [&](int& curr, int& currdir, auto& rem) {
                     auto old = curr;
                     auto len = step(curr, currdir);
                     if (rem > len) {
                       rem -= len;
                       return sentinel;
                     } else {
                       return in_direction(byind[old], currdir, rem);
                     }
                   };
  
  rep(it, 0, cycle) {
    auto got = stopifend(curr, currdir, rem);
    if (got != sentinel) {
      cout << got.first << " " << got.second << '\n';
      exit(0);
    }
  }
  assert(false);
}
