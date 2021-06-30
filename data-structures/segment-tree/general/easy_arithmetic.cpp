// segment tree (arithmetic expr evaluation)
// https://open.kattis.com/problems/easyarithmetic
// 2020 Vietnam Regional

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

constexpr auto dbg = false;

const int MAXN = 2 * 100'000;
int pow10[MAXN + 5];

const int MOD = 998'244'353;
int add(ll a, ll b){return (a + b) % MOD;}
int sub(ll a, ll b){return (a - b + MOD) % MOD;}
int mult(ll a, ll b){return (a * b) % MOD;}

struct atom {
  int val;
  int len;
  char op;
  bool isop;
};

atom merge_num(const atom& a, const atom& b) {
  assert(!a.isop and !b.isop);
  assert(a.len > 0 and b.len > 0);
  auto res = add(mult(a.val, pow10[b.len]), b.val);
  return atom{res, a.len + b.len, '_', false};
}

int evaluate(const auto& a, int l, int r) {
  bool neg = false;
  if (a[l].isop) {
    if (a[l].op == '-') neg = true;
    l++;
  }
  auto res = !neg ? a[l].val : sub(0, a[l].val);
  for (int i = l + 1; i <= r; i += 2) {
    assert(a[i].isop);
    if (a[i].op == '-') res = sub(res, a[i + 1].val);
    else res = add(res, a[i + 1].val);
  }
  return res;
}

auto reduce(basic_string<atom> a) {
  {
    basic_string<atom> temp;
    trav(elem, a) {
      if (!empty(temp) and !temp.back().isop and !elem.isop)
        temp.back() = merge_num(temp.back(), elem);
      else temp.PB(elem);
    }
    a = move(temp);
  }

  int first_op = MAXN, last_op = -MAXN;
  rep(i, 0, sz(a)) if (a[i].isop) {first_op = i; break;}
  for (int i = sz(a) - 1; i >= 0; i--) if (a[i].isop) {last_op = i; break;}
  if (first_op < last_op) {
    assert(last_op - first_op >= 2);
    assert(!a[first_op + 1].isop);
    assert(!a[last_op - 1].isop);
    basic_string<atom> temp;
    rep(i, 0, first_op) temp.PB(a[i]);
    temp.push_back(atom{-1, 0, '+', true});
    temp.push_back(atom{evaluate(a, first_op, last_op - 1), 0, '_', false});
    rep(i, last_op, sz(a)) temp.PB(a[i]);
    a = move(temp);
  }
  return a;
}

struct node {
  basic_string<atom> v;

  node() = default;
  node(char c) {
    if (isdigit(c)) {
      int val = (int)(c - '0');
      v.PB(atom{val, 1, '_', false});
    } else {
      v.PB(atom{-1, 0, c, true});
    }
  }
  static node combine(const node& a, const node& b) {
    node c{};
    c.v = a.v;
    trav(elem, b.v) c.v.PB(elem);
    c.v = reduce(c.v);
    return c;
  }
  node combine(const auto& o) const {return node::combine(*this, o);}

  int value() const {
    return evaluate(v, 0, sz(v) - 1);
  }
};

int geq(int n){for(int res = 1;; res *= 2) if (res >= n) return res;}

struct ST {
  int s;
  vector<node> a;
  ST(const string& v) : s{sz(v)}, a(2 * s) {
    for (int i = s; i < 2 * s; i++) a[i] = node(v[i - s]);
    for (int i = s - 1; i >= 1; i--) a[i] = node::combine(a[2 * i], a[2 * i + 1]);
  }
  void update(int p, char c) {
    a[p += s] = node(c);
    for (p >>= 1; p; p >>= 1) {
      a[p] = a[2 * p].combine(a[2 * p + 1]);
    }
  }
  node query(int l, int r) {
    auto lacc = node{};
    auto racc = node{};
    for (l += s, r+= s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) lacc = node::combine(lacc, a[l]);
      if (~r & 1) racc = node::combine(a[r], racc);
    }
    return node::combine(lacc, racc);
  }
  
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  pow10[0] = 1;
  rep(i, 1, MAXN + 1) pow10[i] = mult(pow10[i - 1], 10);

  string s;
  cin >> s;
  int q;
  cin >> q;
  
  ST st(s);
  rep(it, 0, q) {
    char type;
    cin >> type;
    if (type == '?') {
      int l, r;
      cin >> l >> r;
      --l; --r;
      auto res = node('0').combine(st.query(l, r));
      auto val = res.value();
      cout << val << '\n';
    } else {
      int p; char c;
      cin >> p >> c;
      --p;
      s[p] = c;
      st.update(p, c);
    }
  }
}
