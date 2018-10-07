// gcd (factorizing number by finding gcd w/ prime powers)
// http://codeforces.com/contest/1033/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

struct num
{
    int type; // square - 2, cube - 3, fourth - 4, other - 0
    ll f1, f2;
    ll val;
};

ll rt(ll n, int p)
{
    ll candidate = pow(n, 1.0 / (long double) p);
    ll range = 10;
    for (ll i = max(0LL, candidate - range); i <= candidate + range; i++)
    {
        ll res = 1;
        for (int k = 0; k < p; k++)
            res *= i;
        if (res == n)
            return i;
    }
    return 0;
}

ll gcd(ll a, ll b)
{
    while (b != 0)
        tie(a, b) = make_tuple(b, a % b);
    return a;
}

void setEqual(num &n1, num &n2)
{
    set <ll> facs = {n1.f1, n1.f2, n2.f1, n2.f2};

    auto it = --facs.end();
    n1.f1 = *it;
    n2.f1 = *it;

    --it;
    n1.f2 = *it;
    n2.f2 = *it;
}

void setFactor(num &n, ll fac)
{
    if (n.type != 0)
        return;

    if (n.f1 != fac and n.f2 != fac)
    {
        if (n.f1 < 0)
            n.f1 = fac;
        else
            n.f2 = fac;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector <num> nums(n);
    int it = -1;
    for (int i = 0; i < n; i++)
    {
        ll v, temp;
        cin >> v;

        if ((temp = rt(v, 4)) != 0)
            nums[i] = {4, temp, 0, v};
        else if ((temp = rt(v, 3)) != 0)
            nums[i] = {3, temp, 0, v};
        else if ((temp = rt(v, 2)) != 0)
            nums[i] = {2, temp, 0, v};
        else
        {
            nums[i] = {0, it, it - 1, v};
            it -= 2;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) if (i != j)
        {
            if (nums[i].type == 0 or nums[j].type == 0)
            {
                if (nums[i].val == nums[j].val)
                    setEqual(nums[i], nums[j]);
                else
                {
                    ll g = gcd(nums[i].val, nums[j].val);
                    if (g > 1)
                    {
                        setFactor(nums[i], g);
                        setFactor(nums[j], g);
                    }
                }
            }
        }
    }

    map <ll, int> cnts;
    for (auto &elem: nums)
    {
        if (elem.type == 0)
            cnts[elem.f1]++, cnts[elem.f2]++;
        else
            cnts[elem.f1] += elem.type;
    }

    ll sol = 1;
    for (auto elem: cnts)
    {
        sol *= (elem.second + 1);
        sol %= MOD;
    }
    cout << sol << '\n';
}
