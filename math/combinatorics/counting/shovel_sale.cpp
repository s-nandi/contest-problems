//combinatorics
//http://codeforces.com/contest/899/problem/D

#include <iostream>

using namespace std;

#define ll long long

int mostNines(int n)
{
    int res = 0;
    ll curr = 5;
    while (n >= curr)
    {
        curr *= 10;
        res++;
    }
    return res;
}

ll numWays(ll target, int n)
{
    ll lb = target > n ? target - n : 1;
    ll ub = target % 2 != 0 ? target / 2 : target / 2 - 1;

    if (ub - lb + 1 < 0) return 0;

    return ub - lb + 1;
}

int main()
{
    int n;
    cin>>n;

    int iterations = mostNines(n);

    ll target = 0;
    ll pow10 = 1;
    for (int i = 0; i < iterations; i++)
    {
        target = 10 * target + 9;
        pow10 *= 10;
    }

    ll sol = 0;
    for (int i = 0; i < 9; i++)
    {
        sol += numWays(target, n);
        target += pow10;
    }

    cout<<sol<<'\n';

    return 0;
}
