//dp on probability space (reverse dp), geometric distribution (expected value), prime modular inverse, binary exponentiation
//http://codeforces.com/contest/908/problem/D

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define MOD 1000000007

int mult(int a, int b)
{
    return ((ll) a * b) % MOD;
}

int binaryPow(int n, int p)
{
    int acc = 1;
    while (p)
    {
        if (p & 1) acc = mult(acc, n);
        n = mult(n, n);
        p >>= 1;
    }
    return acc;
}

int modularInv(int n)
{
    return binaryPow(n, MOD - 2);
}

int main()
{
    int k, a, b;
    cin>>k>>a>>b;

    int pa = mult(a, modularInv(a + b));
    int pb = mult(b, modularInv(a + b));
    int modPB = modularInv(pb);

    int dp[k + 1][k + 1];

    for (int i = k; i >= 1; i--)
    {
        for (int j = k; j >= 0; j--)
        {
            if (i + j < k)
            {
                dp[i][j] = (mult(pa, dp[i + 1][j]) + mult(pb, dp[i][i + j])) % MOD;
            }
            else
            {
                dp[i][j] = (i + j + mult(pa, modPB)) % MOD;
            }
        }
    }

    cout<<dp[1][0]<<'\n';

    return 0;
}
