// NTT (multiplying polynomials with negative exponents), counting (nck w/ factorial precompute)
// https://www.codechef.com/RC122020/problems/RECNDSUB/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define sz(a) (int)size(a)

const ll mod = 163577857, root = 23;
ll mult(ll a, ll b){return a * b % mod;}

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}

typedef vector<ll> vl;
void ntt(vl& a, vl& rt, vl& rev, int n) {
  rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = (z > ai ? ai - z + mod : ai - z);
        ai += (ai + z >= mod ? z - mod : z);
      }
}

vl conv(const vl& a, const vl& b) {
  if (a.empty() || b.empty())
    return {};
  int s = sz(a)+sz(b)-1, B = 32 - __builtin_clz(s), n = 1 << B;
  vl L(a), R(b), out(n), rt(n, 1), rev(n);
  L.resize(n), R.resize(n);
  rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << B) / 2;
  ll curL = mod / 2, inv = modpow(n, mod - 2);
  for (int k = 2; k < n; k *= 2) {
    ll z[] = {1, modpow(root, curL /= 2)};
    rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  ntt(L, rt, rev, n); ntt(R, rt, rev, n);
  rep(i,0,n) out[-i & (n-1)] = L[i] * R[i] % mod * inv % mod;
  ntt(out, rt, rev, n);
  return {out.begin(), out.begin() + s};
}

const int MAXN = 200000;
ll factorial[MAXN + 5];
ll pow2[MAXN + 5];
ll nck(int n, int k) {
  ll denom = mult(factorial[k], factorial[n - k]);
  return mult(factorial[n], modpow(denom, mod - 2));
}
void solve() {
  int n;
  cin >> n;
  int pos = 0, neg = 0, zero = 0;
  rep(it, 0, n) {
    int i;
    cin >> i;
    if (i == 1) pos++; else if (i == -1) neg++; else zero++;
  }
  vl pa(pos + 1), pb(neg + 1);
  for (int i = 0; i <= pos; i++) pa[i] = nck(pos, i);
  for (int j = 0; j <= neg; j++) pb[j] = nck(neg, neg - j);
  auto pc = conv(pa, pb);

  vl res(2 * n + 1);
  int offset = n;
  auto multiplier = pow2[zero];
  rep(i, 0, sz(pc)) {
    auto ways = pc[i];
    auto exp = i - neg;
    ways = mult(ways, multiplier);
    if (exp == 0) ways = (ways - 1 + mod) % mod;
    res[exp + offset] = ways;
  }
  trav(elem, res) cout << elem << " "; cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  factorial[0] = pow2[0] = 1;
  rep(i, 1, MAXN + 1) {
    factorial[i] = mult(factorial[i - 1], i);
    pow2[i] = mult(2, pow2[i - 1]);
  }
  int T;
  cin >> T;
  while (T--) solve();
}
