// factorization, finding smallest factor of number greater than 3 (numbers are > 10^9)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=&problem=5403&mosmsg=Submission+received+with+ID+2430741
// 2015 Pacific Northwest Regional

#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1LL << 31) - 1;

vector <bool> prm;
vector <int> primes;
void sieve(int n)
{
    int sq = sqrt(n) + 5;
    prm.resize(sq, true);
    for (int i = 2; i < sq; i++)
    {
        if (!prm[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j < sq; j += i)
        {
            prm[j] = false;
        }
    }
}

vector <pair<int, int>> factorize(int n)
{
    vector <pair<int, int>> factors;
    for (int p: primes)
    {
        if (n % p == 0) factors.push_back({p, 0});
        while (n % p == 0)
            n /= p, factors.back().second++;
    }
    if (n != 1) factors.push_back({n, 1});
    return factors;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sieve(MAXN);

    int n;
    while (cin >> n)
    {
        int fac;
        if (n - 3 < 0)
            fac = -1;
        else if (n - 3 == 0)
            fac = 4;
        else if (n - 3 == 1)
            fac = -1;
        else
        {
            auto f = factorize(n - 3);
            fac = MAXN;
            if (f[0].first > 3)
                fac = min(fac, f[0].first);
            else if(f[0].second >= 2)
                fac = min(fac, f[0].first * f[0].first);
            else if(f.size() > 1)
            {
                if (f[1].first > 3)
                    fac = min(fac, f[1].first);
                else if(f[1].second >= 2)
                    fac = min(fac, f[1].first * f[1].first);
                fac = min(fac, f[0].first * f[1].first);
            }
            else
                fac = -1;
        }
        if (fac == -1)
            cout<<"No such base"<<'\n';
        else
            cout<<fac<<'\n';
    }

    return 0;
}
