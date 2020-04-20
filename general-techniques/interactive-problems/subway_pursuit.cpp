// randomization (interactively finding position of object that can move small distance between queries), binary search
// https://codeforces.com/contest/1040/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool makeQuery(ll l, ll r)
{
    string res;
    cout<<l<<" "<<r<<endl;
    cin>>res;
    if (res[0] == 'B')
        exit(0);
    else if(res[0] == 'N')
        return false;
    else
    {
        if (l == r)
            exit(0);
        return true;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char* rng = new char;
    mt19937 mt((ll) rng);
    delete rng;

    ll n; int k;
    cin>>n>>k;

    ll l = 1, r = n;
    while (true)
    {
        ll sz = r - l + 1;
        if (sz <= 5 * k)
        {
            ll guess = l + mt() % sz;
            makeQuery(guess, guess);
        }
        else
        {
            ll m = l + (r - l) / 2;
            if(makeQuery(l, m))
                r = m;
            else
                l = m + 1;
        }
        l = max(1LL, l - k);
        r = min(n, r + k);
    }

    return 0;
}
