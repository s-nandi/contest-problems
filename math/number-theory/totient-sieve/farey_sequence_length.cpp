// totient sieve, prefix sums
// https://open.kattis.com/problems/farey
// 2015 Greater NY Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 10000;

vector <int> primes, phi;
vector <bool> prm;
void totientSieve(int n)
{
    prm.resize(n + 1, true);
    phi.resize(n + 1);
    for (int i = 2; i <= n; i++)
    {
        if (prm[i])
        {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int prime: primes)
        {
            if ((ll) i * prime > n)
                break;

            prm[i * prime] = false;
            if (i % prime == 0)
            {
                phi[i * prime] = phi[i] * prime;
                break;
            }
            else
                phi[i * prime] = phi[i] * phi[prime];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    totientSieve(MAXN);

    int T;
    cin >> T;

    vector <int> ps(MAXN + 1);
    ps[0] = 2; // (0 / n) and (n / n) always contained in a n-length farey sequence
    for (int i = 1; i <= MAXN; i++)
        ps[i] = ps[i - 1] + phi[i];

    while (T--)
    {
        int test, n;
        cin >> test >> n;
        cout << test << " " << ps[n] << '\n';
    }
}
