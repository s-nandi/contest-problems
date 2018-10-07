// gcd (factorizing number by finding gcd w/ prime powers)
// http://codeforces.com/contest/1033/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

struct num
{
    int type; // square - 2, cube - 3, fourth - 4, other - 0
    ll f1, f2, val;
};

ll is_pth_root(ll n, int p)
{
    ll candidate = pow(n, 1.0 / p);
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
        ll v;
        cin >> v;

        bool primePower = false;
        for (int p = 4; p >= 2; p--)
        {
            ll root = is_pth_root(v, p);
            if (root)
            {
                nums[i] = {p, root, 0, v};
                primePower = true;
                break;
            }
        }
        if (!primePower)
            nums[i] = {0, it--, it--, v};
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (nums[i].type == 0)
            {
                ll g = gcd(nums[i].val, nums[j].val);
                if (g > 1 and g != nums[i].val)
                {
                    nums[i].f1 = g;
                    nums[i].f2 = nums[i].val / g;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (nums[i].val == nums[j].val)
                nums[j] = nums[i];
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
