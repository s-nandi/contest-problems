// inclusion-exclusion (finding # of solutions to linear equation w/ constraints), stars & bars, prime modular inverse (calculating nCk w/ large n and small k)
// http://codeforces.com/contest/451/problem/E

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MOD = 1000000007;

int mult(int a, int b, int mod)
{
    return 1LL * a * b % mod;
}

int binaryPower(int n, int p, int mod)
{
    int acc = 1;
    for (; p; p >>= 1)
    {
        if (p & 1) acc = mult(acc, n, mod);
        n = mult(n, n, mod);
    }
    return acc;
}

int pmodularInverse(int n, int pmod)
{
    return binaryPower(n, pmod - 2, pmod);
}

// fast enough because guaranteed small k (<=20)
int choose(ll n, ll k)
{
    if (k < 0 or k > n)
        return 0;
    int num = 1, denom = 1;
    for (ll i = n, j = 1; i >= n - k + 1; i--, j++)
    {
        num = mult(num, i % MOD, MOD);
        denom = mult(denom, j, MOD);
    }
    return mult(num, pmodularInverse(denom, MOD), MOD);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; ll s;
    cin>>n>>s;

    vector <ll> a(n);
    for (int i = 0; i < n; i++)
        cin>>a[i];

    int sol = 0;
    for (int bm = 0; bm < (1 << n); bm++)
    {
        ll remaining = s;
        int numBits = 0;
        for (int i = 0; i < n; i++)
        {
            if ((1 << i) & bm)
            {
                remaining -= (a[i] + 1); // i-th on bit -> object i violates constraints
                numBits++;
            }
        }
        bool exclude = numBits & 1; // inclusion-exclusion: include if even # of boxes violate constraint, exclude otherwise
        int numPartitions = choose(remaining + n - 1, n - 1); // stars&bars
        if (exclude)
            sol = (sol - numPartitions + MOD) % MOD;
        else
            sol = (sol + numPartitions) % MOD;
    }
    cout<<sol<<'\n';
}
