// inclusion-exclusion (# of solutions to constrained linear equation), nCk mod p where p is square-free non-prime (crt, lucas' theorem, extended euclid for modular inverse)
// https://open.kattis.com/problems/classicalcounting
// 2018 Singapore Preliminary

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int MOD = 1000007;
const int MAXN = 500000;

struct bezout_coefficients
{
    ll g, x, y; // x * a + y * b = gcd(a, b)
};

bezout_coefficients extended_gcd(ll a, ll b)
{
    array <ll, 3> A = {0, 1, a}, B = {1, 0, b};
    while (B[2] != 0)
    {
        ll q = A[2] / B[2];
        auto T = B;
        transform(A.begin(), A.end(), B.begin(), B.begin(), [q](ll x, ll y){return x - q * y;});
        A = T;
    }
    return {A[2], A[1], A[0]};
}

struct congruence
{
     ll residue, mod; // mod = -1 used to denote invalid/no solution
};

congruence chinese_remainder_theorem(congruence a, congruence b)
{
    bezout_coefficients c = extended_gcd(a.mod, b.mod);

    if (a.mod == -1 or b.mod == -1 or (a.residue - b.residue) % c.g != 0)
        return {-1, -1};

    ll mod = a.mod / c.g * b.mod; // new mod = lcm(a.mod, b.mod)
    ll res = (a.residue - (c.x * (a.residue - b.residue) / c.g % (b.mod / c.g)) * a.mod) % mod;
    return {res < 0 ? res + mod : res, mod};
}

congruence chinese_remainder_theorem(vector <congruence> &v)
{
    congruence res = v[0];
    for (int i = 1; i < v.size(); i++)
        res = chinese_remainder_theorem(res, v[i]);
    return res;
}

int mult(ll a, ll b, int mod)
{
    return a * b % mod;
}

vector <int> factorial;
void precompute_factorial(int n, int mod)
{
    factorial.resize(n + 1);
    factorial[0] = 1;
    for (int i = 1; i <= n; i++)
        factorial[i] = mult(factorial[i - 1], i, mod);
}

vector <ll> pf;
void precompute_factors(int n)
{
    for (ll i = 2; i <= n; i++) if (n % i == 0)
    {
        pf.push_back(i);
        while (n % i == 0)
            n /= i;
    }
}

// assumes a is relatively prime to mod
int modularInverse(int a, int mod)
{
    bezout_coefficients c = extended_gcd(a, mod);
    return c.x < 0 ? c.x + mod : c.x;
}

// only use with prime mod and if n, k < p
ll choose(ll n, ll k, ll mod)
{
    if (k < 0 or k > n)
        return 0;
    ll num = factorial[n];
    ll denom = mult(modularInverse(factorial[k], mod), modularInverse(factorial[n - k], mod), mod);
    return num * denom % mod;
}

// use with prime mod
ll lucas_choose(ll n, ll k, ll p)
{
    int res = 1;
    for(; n; n /= p, k /= p)
        res = mult(res, choose(n % p, k % p, p), p);
    return res;
}

// use with square-free mod, vector must contain all prime factors of mod
ll crt_choose(ll n, ll k, const vector <ll> &mod_factors)
{
    vector <congruence> congruences;
    for (ll p: mod_factors)
        congruences.push_back({lucas_choose(n, k, p), p});
    congruence sol = chinese_remainder_theorem(congruences);
    return sol.residue;
}

int main()
{
    precompute_factorial(MAXN, MOD);
    precompute_factors(MOD);

    int n, m, k;
    cin>>n>>m>>k;

    int sol = 0;
    for (int i = 0; i <= n; i++)
    {
        int sign = i & 1 ? -1 : 1; // include even i's, exclude odd i's in summation

        int remaining = k - i * (m + 1);
        if (remaining < 0)
            break;

        int ways = crt_choose(n, i, pf);
        int partitions = crt_choose(remaining + n - 1, n - 1, pf);
        sol = (sol + sign * mult(partitions, ways, MOD) + MOD) % MOD;
    }
    cout<<sol<<'\n';
}
