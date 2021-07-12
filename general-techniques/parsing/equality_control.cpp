// recursive descent parser, canonical repr., uniform probability, shuffle == flag + sort
// https://open.kattis.com/problems/equality
// 2018 Northwestern Europe Regional

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

enum ExprType { CONSTRUCTOR, CONCAT, SHUFFLE, SORTED };
struct Expr {
  ExprType type;
  Expr* l;
  Expr* r;
  vi vals;
};

char consume(const string& s, int& it) { return s[it++]; }
void consume(const string& s, int& it, char c) {
  assert(consume(s, it) == c);
}
void consume(const string& s, int& it, const string& exp) {
  trav(c, exp) consume(s, it, c);
}

int parsenum(const string& s, int& it) {
  int val = 0;
  while (it < sz(s) and isdigit(s[it]))
    val = val * 10 + (consume(s, it) - '0');
  return val;
}

Expr* parse(const string& s, int& it) {
  Expr* res = new Expr{};
  if (s[it] == '[') {
    res -> type = CONSTRUCTOR;
    consume(s, it, '[');
    while (true) {
      int val = parsenum(s, it);
      (res -> vals).PB(val);
      if (s[it] == ']') break;
      consume(s, it, ',');
    }
    consume(s, it, ']');
  } else if (s[it] == 'c') {
    res -> type = CONCAT;
    consume(s, it, "concat(");
    res -> l = parse(s, it);
    consume(s, it, ',');
    res -> r = parse(s, it);
    consume(s, it, ')');
  } else if (s[it] == 's' and s[it + 1] == 'o') {
    res -> type = SORTED;
    consume(s, it, "sorted(");
    res -> l = parse(s, it);
    consume(s, it, ')');
  } else if (s[it] == 's' and s[it + 1] == 'h') {
    res -> type = SHUFFLE;
    consume(s, it, "shuffle(");
    res -> l = parse(s, it);
    consume(s, it, ')');
  } else assert(false);
  return res;
}

void getvals(Expr* e, vi& curr) {
  if (!e) return;
  if (e -> type == CONSTRUCTOR)
    trav(elem, e -> vals) curr.PB(elem);
  else {
    getvals(e -> l, curr);
    getvals(e -> r, curr);
  }
}

using Canonical = vector<pair<vi, bool>>;
void to_canonical(Expr* e, Canonical& res) {
  if (e -> type == CONCAT) {
    to_canonical(e -> l, res);
    to_canonical(e -> r, res);
  } else {
    auto& [curr, shuffled] = res.emplace_back();
    if (e -> type == CONSTRUCTOR) {
      getvals(e, curr);
      shuffled = false;
    } else if (e -> type == SHUFFLE) {
      getvals(e, curr);
      sort(all(curr));
      shuffled = curr[0] != curr.back();
    } else if (e -> type == SORTED) {
      getvals(e, curr);
      sort(all(curr));
      shuffled = false;
    } else assert(false);
  }
}

Canonical merge_unshuffled(const Canonical& vals) {
  Canonical res;
  for (const auto& [row, shuffled]: vals) {
    if (empty(res) or res.back().second or shuffled)
      res.emplace_back();
    move(all(row), back_inserter(res.back().first));
    res.back().second = shuffled;
  }
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  array<Canonical, 2> res;
  rep(i, 0, 2) {
    string s;
    cin >> s;
    
    int iter = 0;
    Expr* e = parse(s, iter);
    
    to_canonical(e, res[i]);
    res[i] = merge_unshuffled(res[i]);
  }
  cout << (res[0] == res[1] ? "equal" : "not equal") << '\n';
}
