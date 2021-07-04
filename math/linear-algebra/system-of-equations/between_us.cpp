// Linear system (mod 2), partition into 2 sets while satisfying parity constraints
// https://codeforces.com/gym/102861/problem/K
// 2020 Brazil Subregional

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

const int MAXN = 100;

typedef bitset<MAXN> bs;

int solveLinear(vector<bs>& A, vi& b, bs& x, int m) {
  int n = sz(A), rank = 0, br;
  assert(m <= sz(x));
  vi col(m); iota(all(col), 0);
  rep(i,0,n) {
    for (br=i; br<n; ++br) if (A[br].any()) break;
    if (br == n) {
      rep(j,i,n) if(b[j]) return -1;
      break;
    }
    int bc = (int)A[br]._Find_next(i-1);
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j,0,n) if (A[j][i] != A[j][bc]) {
      A[j].flip(i); A[j].flip(bc);
    }
    rep(j,i+1,n) if (A[j][i]) {
      b[j] ^= b[i];
      A[j] ^= A[i];
    }
    rank++;
  }

  x = bs();
  for (int i = rank; i--;) {
    if (!b[i]) continue;
    x[col[i]] = 1;
    rep(j,0,i) b[j] ^= A[j][i];
  }
  return rank; // (multiple solutions if rank < m)
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }

  auto A = vector<bs>(n);
  vi b(n);
  /*
    Let A x = b, where x[i] = k iff student i is in partition k (0 or 1)

    if x[i] == 1:
    want sum{edge (i, j)} x[j] = 1
    if x[i] == 0:
    want sum{edge (i, j)} 1 - x[j] = 1

    To generalize, rewrite the expression inside the summation:
    sum_j (1 - x[i]) - x[j] = 1
    = sum_j (1 + x[i]) + x[j] = 1 since -/+/xor are the same mod 2
    = sum_j x[i] + x[j] = 1 + sum_j 1
    = (# j) * x[i] + sum_j x[j] = (# j) * 1 + 1
    = deg(i) * x[i] + sum_j x[j] = deg(i) + 1

    which is a linear system in F_2 once we take deg(i) modulo 2
  */
  rep(i, 0, n) {
    b[i] = 1;
    trav(e, g[i]) {
      A[i][e.to] = 1;
      A[i][i] = A[i][i] ^ 1;
      b[i] = b[i] ^ 1;
    }
  }
  bs x{};
  auto rank = solveLinear(A, b, x, n);
  cout << (rank != -1 ? "Y" : "N") << '\n';
}
