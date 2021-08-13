#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using vll = vector<long long>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

struct Node {
  Node *l = 0, *r = 0;
  int val, y, c = 1;
  Node(int val) : val(val), y(rand()) {}
  void recalc();
};
using Node2 = pair<Node*, Node*>;
using Node3 = tuple<Node*, Node*, Node*>;

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

template<class F> void each(Node* n, F f) {
  if (n) { each(n->l, f); f(n); each(n->r, f); }
}

ostream& operator << (ostream& os, Node* n) {
  each(n, [&](Node* curr) {
            os << (curr -> val) << " ";
          });
  return os;
}


Node* merge(Node* l, Node* r) {
  if (!l) return r;
  if (!r) return l;
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    l->recalc();
    return l;
  } else {
    r->l = merge(l, r->l);
    r->recalc();
    return r;
  }
}

// Index Operations

Node2 split(Node* n, int k) { // ind < k (ie. first k), ind >= k
  if (!n) return {};
  if (cnt(n->l) >= k) {
    auto [a, b] = split(n->l, k);
    n->l = b;
    n->recalc();
    return {a, n};
  } else {
    auto [a, b] = split(n->r, k - cnt(n->l) - 1);
    n->r = a;
    n->recalc();
    return {n, b};
  }
}

Node3 split(Node* n, int k1, int k2) { // ind < k1, k1 <= ind <= k2, ind > k2
  auto [ab, c] = split(n, k2 + 1);
  auto [a, b] = split(ab, k1);
  return {a, b, c};
}

Node* insert(Node* t, Node* n, int pos) { // n will be at position 'pos' in t
  auto [a, b] = split(t, pos);
  return merge(merge(a, n), b);
}

Node2 erase(Node* t, int l, int r) { // erase [l, r] inclusive, returns (remaining, erased) pair
  auto [a, b, c] = split(t, l, r);
  return pair{merge(a, c), b};
}

// Value operations

Node2 splitval(Node* n, int k) { // val < k in left, val >= k in right
  if (!n) return {};
  if (n->val >= k) {
    auto [a, b] = splitval(n->l, k);
    n->l = b;
    n->recalc();
    return {a, n};
  } else {
    auto [a, b] = splitval(n->r, k);
    n->r = a;
    n->recalc();
    return {n, b};
  }
}

Node3 splitval(Node* n, int k1, int k2) { // val < k1, k1 <= val <= k2, val > k2
  auto [ab, c] = splitval(n, k2 + 1);
  auto [a, b] = splitval(ab, k1);
  return {a, b, c};
}

Node* insertval(Node* t, int val) { // insert val into t in sorted order
  auto [a, b] = splitval(t, val);
  return merge(merge(a, new Node(val)), b);
}

Node2 eraseval(Node* t, int val) { // erase val from t; assumes t is in sorted order
  auto [a, b, c] = splitval(t, val, val);
  auto [kept, removed] = erase(b, 0, 0);
  return {merge(a, merge(kept, c)), removed};
}

void shandom_ruffle(Node*& root, int a, int b, const int n) {
  int len = min(b - a, n - b);
  Node *second, *first;
  tie(root, second)= erase(root, b, b + len - 1);
  tie(root, first) = erase(root, a, a + len - 1);
  root = insert(root, second, a);
  root = insert(root, first, b);
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << setprecision(10) << fixed;

  int n;
  cin >> n;
  Node* root{};
  rep(i, 1, n + 1) {
    root = insert(root, new Node(i), i - 1);
  }
  rep(it, 0, n) {
    int a, b;
    cin >> a >> b;
    shandom_ruffle(root, --a, --b, n);
  }
  cout << root << '\n';
}
