// heavy implementation, bool logic ('and' within fixed start time interval, 'or' across start times)
// https://codeforces.com/gym/101242/problem/D
// 2016 World Finals

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

constexpr int N = 7;
constexpr int M = 21;

constexpr int MAXTIME = 24 * 60;
constexpr int NSEGMENTS = 7;
constexpr int NVALS = 10;

constexpr int BURNTOUT = 1 << 0;
constexpr int BURNTIN = 1 << 1;
constexpr int WORKING = 1 << 2;

using Matrix = array<array<int, M>, N>;

vector<pii> pixelsfor[NSEGMENTS];
vi segmentsfor[NVALS];
Matrix times[24][60];

void write_num(auto& buffer, int col, int num) {
  for (const auto& seg: segmentsfor[num])
    for (const auto& [dx, dy]: pixelsfor[seg])
      buffer[dx][col + dy] = 1;
}

Matrix to_time(int h, int m) {
  Matrix res{};
  vi digits = {h / 10, h % 10, m / 10, m % 10};
  int col = 0;
  rep(i, 0, sz(digits)) {
    if (i > 0 or digits[i] != 0)
      write_num(res, col, digits[i]);

    col += 4 + 1;
    if (i == 1) {
      res[2][col] = res[4][col] = 1;
      col += 1 + 1;
    }
  }
  return res;
}

void precompute() {
  // pixelsfor[i] = { {# down, # right}, ... for segment i}
  pixelsfor[0] = {{0, 1}, {0, 2}};
  pixelsfor[1] = {{1, 0}, {2, 0}};
  pixelsfor[2] = {{1, 3}, {2, 3}};
  pixelsfor[3] = {{3, 1}, {3, 2}};
  pixelsfor[4] = {{4, 0}, {5, 0}};
  pixelsfor[5] = {{4, 3}, {5, 3}};
  pixelsfor[6] = {{6, 1}, {6, 2}};

  // segmentsfor[i] = {segment used for value i}
  segmentsfor[0] = {0, 1, 2, 4, 5, 6};
  segmentsfor[1] = {2, 5};
  segmentsfor[2] = {0, 2, 3, 4, 6};
  segmentsfor[3] = {0, 2, 3, 5, 6};
  segmentsfor[4] = {1, 2, 3, 5};
  segmentsfor[5] = {0, 1, 3, 5, 6};
  segmentsfor[6] = {0, 1, 3, 4, 5, 6};
  segmentsfor[7] = {0, 2, 5};
  segmentsfor[8] = {0, 1, 2, 3, 4, 5, 6};
  segmentsfor[9] = {0, 1, 2, 3, 5, 6};

  rep(h, 0, 24) rep(m, 0, 60) times[h][m] = to_time(h, m);
}

void fill(Matrix& m, int val){
  rep(i, 0, N) rep(j, 0, M) m[i][j] = val;
}

pii fromindex(int i) {return {i / 60, i % 60};}
int toindex(int h, int m) {return h * 60 + m;}

optional<Matrix> check(const auto& have, const auto& exp, const auto& alwayson, const auto& alwaysoff) {
  Matrix status{};
  rep(i, 0, N) rep(j, 0, M) {
    if (alwayson[i][j]) status[i][j] |= BURNTIN;
    if (alwaysoff[i][j]) status[i][j] |= BURNTOUT;
    
    auto badon = have[i][j] and !exp[i][j];
    auto badoff = !have[i][j] and exp[i][j];
    if (badon and !alwayson[i][j]) {
      return nullopt;
    } else if (badoff and !alwaysoff[i][j]) {
      return nullopt;
    } else if (have[i][j] == exp[i][j]) { 
      status[i][j] |= WORKING;
    }
  }
  return status;
}

optional<Matrix> checkinterval(const auto& seq, int start, const auto& alwayson, const auto& alwaysoff) {
  Matrix status_and{};
  fill(status_and, BURNTOUT | BURNTIN | WORKING);
  rep(it, 0, sz(seq)) {
    auto tm = (start + it) % MAXTIME;
    auto [h, m] = fromindex(tm);
    auto status = check(seq[it], times[h][m], alwayson, alwaysoff);
    if (!status) return nullopt;
    rep(i, 0, N) rep(j, 0, M) status_and[i][j] &= (*status)[i][j];
  }
  rep(i, 0, N) rep(j, 0, M) if (!status_and[i][j]) return nullopt;
  return status_and;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  precompute();
  
  int n;
  cin >> n;
  vector<Matrix> a(n);
  trav(i, a) {
    trav(row, i) {
      string s;
      cin >> s;
      rep(it, 0, sz(s)) row[it] = s[it] == 'X';
    }
  }

  Matrix alwayson{}, alwaysoff{};
  fill(alwayson, true);
  fill(alwaysoff, true);
  rep(it, 0, n) rep(i, 0, N) rep(j, 0, M) {
    alwayson[i][j] &= a[it][i][j];
    alwaysoff[i][j] &= !a[it][i][j];
  }

  Matrix status_or{};
  rep(start, 0, MAXTIME) {
    auto status = checkinterval(a, start, alwayson, alwaysoff);
    if (!status) continue;
    rep(i, 0, N) rep(j, 0, M) status_or[i][j] |= (*status)[i][j];
  }

  auto feasible = true;
  rep(i, 0, N) rep(j, 0, M) feasible &= !!(status_or[i][j]);

  if (!feasible) cout << "impossible" << '\n';
  else {
    const auto saturated = to_time(88, 88);

    vector res(N, vector<char>(M));
    rep(i, 0, N) rep(j, 0, M) {
      if (saturated[i][j] == 0) res[i][j] = '.';
      else {
        if (__builtin_popcount(status_or[i][j]) > 1) res[i][j] = '?';
        else if (status_or[i][j] == WORKING) res[i][j] = 'W';
        else if (status_or[i][j] == BURNTIN) res[i][j] = '1';
        else if (status_or[i][j] == BURNTOUT) res[i][j] = '0';
        else assert(false);
      }
    }
    
    trav(row, res) {
      trav(elem, row) cout << elem;
      cout << '\n';
    }
  }
}
