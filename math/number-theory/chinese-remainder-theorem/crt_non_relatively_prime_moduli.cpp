// crt (direct application)
// https://open.kattis.com/problems/generalchineseremainder

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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

    ll mod = a.mod / c.g * b.mod; // lcm(a.mod, b.mod)
    ll res = (a.residue - (c.x * (a.residue - b.residue) / c.g % (b.mod / c.g)) * a.mod) % mod;
    return {res < 0 ? res + mod : res, mod};
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        ll a, n, b, m;
        cin >> a >> n >> b >> m;
        congruence c1 = {a, n}, c2 = {b, m};
        congruence res = chinese_remainder_theorem(c1, c2);
        if (res.mod != -1)
            cout << res.residue << " " << res.mod << '\n';
        else
            cout << "no solution" << '\n';
    }
}
