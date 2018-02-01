//fermat's little theorem, prime modular inverse, binary exponentiation
//http://codeforces.com/problemset/problem/919/E

#include <iostream>
#include <cmath>

using namespace std;

#define ll long long

int mult(int a, int b, int mod)
{
    return ((ll) a * b) % mod;
}

int binaryPower(int n, int p, int mod)
{
    int acc = 1;
    while (p)
    {
        if (p & 1) acc = mult(acc, n, mod);
        n = mult(n, n, mod);
        p >>= 1;
    }
    return acc;
}

int modularInverse(int n, int pmod)
{
    return binaryPower(n, pmod - 2, pmod);
}

int main()
{
    int a, b, p;
    ll x;
    cin>>a>>b>>p>>x;
    ll sol = 0;
    for (int rem = 0; rem < p - 1; rem++)
    {
        int z = (mult(b, modularInverse(binaryPower(a, rem, p), p), p));

        ll lb = ceil((double(1 - rem) / (p - 1) - (rem - z)) / p);
        ll ub = floor((double(x - rem) / (p - 1) - (rem - z)) / p);

        sol += ub >= lb ? ub - lb + 1 : 0;
    }
    cout<<sol<<'\n';
}
