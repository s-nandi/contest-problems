// prime factorization
// http://codeforces.com/contest/1025/problem/B

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

const int MAXN = 2000000005;

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
            prm[j] = false;
    }
}

vector <int> primeFactors(int n)
{
    vector <int> factors;
    for (int p: primes)
    {
        if (n % p == 0) factors.push_back(p);
        while (n % p == 0)
            n /= p;
    }
    if (n != 1) factors.push_back(n);
    return factors;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve(MAXN);

    int n;
    cin>>n;

    vector <pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i].first>>a[i].second;
    }

    vector <int> possible;
    for (int i: primeFactors(a[0].first))
    {
        possible.push_back(i);
    }
    for (int i: primeFactors(a[0].second))
    {
        possible.push_back(i);
    }
    sort(possible.begin(), possible.end());
    possible.erase(unique(possible.begin(), possible.end()), possible.end());

    int sol = -1;
    for (int fac: possible)
    {
        bool feasible = true;
        for (int i = 0; i < n; i++)
        {
            if (a[i].first % fac != 0 and a[i].second % fac != 0)
            {
                feasible = false;
                break;
            }
        }
        if (feasible)
        {
            sol = fac;
            break;
        }
    }
    cout<<sol<<'\n';

    return 0;
}
