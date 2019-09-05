// chinese remainder theorem, interactive
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104f1a
// 2019 Google Code Jam - Round 1A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct bezout_coefficients {
  ll g, x, y;
};

bezout_coefficients extended_gcd(ll a, ll b) {
  array<ll, 3> A = {0, 1, a}, B = {1, 0, b};
  while (B[2] != 0) {
    ll q = A[2] / B[2];
    auto T = B;
    transform(begin(A), end(A), begin(B), begin(B), [q](ll x, ll y) { return x - q * y; });
    A = T;
  }
  return {A[2], A[1], A[0]};
}

struct congruence {
  ll residue, mod;  // mod = -1 used to denote invalid/no solution
};

congruence chinese_remainder_theorem(congruence a, congruence b) {
  bezout_coefficients c = extended_gcd(a.mod, b.mod);
  if (a.mod == -1 or b.mod == -1 or (a.residue - b.residue) % c.g != 0) return {-1, -1};
  ll mod = a.mod / c.g * b.mod;
  ll res = (a.residue - (c.x * (a.residue - b.residue) / c.g % (b.mod / c.g)) * a.mod) % mod;
  return {res < 0 ? res + mod : res, mod};
}

congruence chinese_remainder_theorem(vector<congruence>& v) {
  congruence res = v[0];
  for (int i = 1; i < v.size(); i++) res = chinese_remainder_theorem(res, v[i]);
  return res;
}

const int NUM_WINDMILL = 18;

void set_windmills(int num_blades) {
  for (int i = 0; i < NUM_WINDMILL; i++) {
    cout << num_blades << " ";
  }
  cout << endl;
}

auto check_windmills() {
  vector<int> blades(NUM_WINDMILL);
  for (auto& blade : blades) {
    cin >> blade;
    if (blade == -1) exit(0);
  }
  return blades;
}

void guess(int num_gophers) {
  cout << num_gophers << endl;
  int judge;
  cin >> judge;
  if (judge == -1) exit(0);
}

int main() {
  int T, n, m;
  cin >> T >> n >> m;
  for (int test = 1; test <= T; test++) {
    vector<congruence> congruences;
    for (auto prime : vector<int>{7, 11, 13, 15, 16, 17}) {
      set_windmills(prime);
      auto moved = check_windmills();
      int residue = accumulate(begin(moved), end(moved), 0) % prime;
      congruences.push_back({residue, prime});
    }
    auto sol = chinese_remainder_theorem(congruences);
    assert(sol.mod > m);
    guess(sol.residue);
  }
}
