//storing all powers (odd p > 3) up to 10^18, binary search, perfect square test
//https://codeforces.com/contest/955/problem/C

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef long long ll;

vector <ll> powers;
const ll threshold = 1000000000000000000;

bool isSquare(ll n)
{
    ll sq = sqrt(n);
    return sq * sq == n;
}

void precompute()
{
    powers.push_back(1);
    for (ll i = 2; i <= 1000000; i++)
    {
        if (isSquare(i)) continue;

        ll v = i, curr_threshold = threshold / i;
        bool evenPower = false;

        while (v <= curr_threshold)
        {
            v *= i;
            evenPower ^= 1;
            if (!evenPower)
            {
                powers.push_back(v);
            }
        }
    }
    sort(powers.begin(), powers.end());
    powers.erase(unique(powers.begin(), powers.end()), powers.end());
}

int solve(ll n)
{
    if (n == 0) return 0;

    int numOdd = upper_bound(powers.begin(), powers.end(), n) - powers.begin();

    ll l = 0, r = 1000000001;
    while (l < r)
    {
        ll m = (l + r + 1) / 2;
        if (m * m <= n)
        {
            l = m;
        }
        else
        {
            r = m - 1;
        }
    }

    int numEven = l - 1;
    return numOdd + numEven;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precompute();

    int q;
    cin>>q;

    for (int i = 0; i < q; i++)
    {
        ll l, r;
        cin>>l>>r;
        cout<<solve(r) - solve(l - 1)<<'\n';
    }

    return 0;
}
