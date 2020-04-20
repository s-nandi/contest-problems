// interactive, factorization, pigeonhole-ish (if one factor is big, other must be small)
// https://codeforces.com/contest/679/problem/A

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i=(a); i<(b); ++i)
#define trav(a, x) for(auto& a: x)

const int MAXN = 100;

int ask(int factor) {
  cout << factor << endl;
  string res;
  cin >> res;
  return res == "yes";
}

int main() {
  vi primes;
  rep(i, 2, MAXN) {
    if (i > MAXN / 2) break;
    bool isprime = true;
    for (auto j = 2; j * j <= i; j++)
      isprime &= (i % j) != 0;
    if (isprime) primes.push_back(i);
  }
  int num_fac = 0;
  trav(p, primes)
    num_fac += ask(p) + (p * p <= MAXN ? ask(p * p) : 0);
  cout << (num_fac <= 1 ? "prime" : "composite") << endl;
}
