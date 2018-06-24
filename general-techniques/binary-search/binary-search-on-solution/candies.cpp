//binary search on answer
//http://codeforces.com/contest/991/problem/C

#include <iostream>

using namespace std;

typedef long long ll;

ll numeaten(ll n, ll k)
{
    ll res = 0;
    while (n > 0)
    {
        ll eat = min(k, n);
        n -= eat;
        res += eat;

        ll rem = n / 10;
        n -= rem;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin>>n;

    ll threshold = (n / 2) + (n & 1);

    ll l = 1, r = n;
    while (l < r)
    {
        ll m = (l + r) / 2;

        ll eaten = numeaten(n, m);
        if (eaten >= threshold)
        {
            r = m;
        }
        else
        {
            l = m + 1;
        }
    }
    cout << l << '\n';

    return 0;
}
